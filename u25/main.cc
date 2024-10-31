#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "humandata.h"
#include "human.h"

#include <fstream>
using std::ifstream;

char fpt[250];

int main(int argc, char *argv[]) 
{	
	if (argc < 11 || argc > 12) {
        printf("\nArgumentos... Por ejemplo:\n");
        printf("./exe 9.999 9.999 6.292 4.790 6.292 6.635 2.60 1000 100 5000 0 \n");
        printf("./exe [pKc] [pRc] [pKo] [pRo] [pKi] [pRi] [pD] [CL] [N] [P] [Save]\n\n");
        printf("P: indica el periodo de grabacion, e.d. cada cuantos ms se debe guardar un pulso.\n");
		printf("P=0 indica que solo se guarda el ultimo pulso (¡OJO! Obligatoriamente las simulaciones deben ser superiores a 1 pulso)\n\n");
		printf("Save = 0 indica que la simulacion parte de cero            y NO guarda los valores finales\n");
		printf("Save = 1 indica que la simulacion parte de cero            y SI guarda los valores finales\n");
		printf("Save = 2 indica que la simulacion parte de valores previos y NO guarda los valores finales\n");
		printf("Save = 3 indica que la simulacion parte de valores previos y SI guarda (sobreescribe) los valores finales\n\n");																   
		return -1;
	}

	human cell(argv[1], argv[2],argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10]);

	int savemode = atoi(argv[11]);
        printf("kC_Drug    = %.04g\n",cell.kC_D);
        printf("rC_Drug    = %.04g\n",cell.rC_D);
        printf("kO_Drug    = %.04g\n",cell.kO_D);
        printf("rO_Drug    = %.04g\n",cell.rO_D);
        printf("kI_Drug    = %.04g\n",cell.kI_D);
        printf("rI_Drug    = %.04g\n",cell.rI_D);
        printf("dofetilide = %.04g nM\n",cell.Dofetilide);
		printf("BCL = %d ms\n",  (int)cell.CL);	
		printf("N pulsos = %d\n",cell.beats);	
		if(cell.beatssave!=0)	printf("Graba cada= %d ms\n",cell.beatssave);	
		if( savemode > 3){ 		printf("Parametro Save ¡Incorrecto!\n\n"); return -1;}

	/*
	 * CELL STRAND DECLARATION
	 */
	humandata *stranddata;
	stranddata = new humandata[cell.strandlength];

	strncpy(fpt, cell.fpth, sizeof(cell.fpth));
	

	/*
	 * CELL STRAND INITIALISATION
	 */
	for (int i = 0; i < cell.strandlength; i++) 
	{
		strncpy(stranddata[i].fcell_save_path, cell.fpth, sizeof(cell.fpth));  //JULIO
		
		if((savemode == 2)||(savemode == 3))
				stranddata[i].load(i + 1);
		else
				stranddata[i].init(i + 1, cell.CL, cell.endo, cell.M); //JORDI
	}

	cell.save_heading(cell.strandlength);  //JULIO
	cell.ecg_heading();

	if (cell.stim_here > (cell.strandlength - 1)) {
		perror("stim_here is greater than strandlength");
	}

	int i = 1;

	/****************************************************************************************************************
	 *
	 *                                                  MAIN LOOP
	 *
	 ****************************************************************************************************************/

	while (cell.t <= cell.ft) {

		for (int x = 0; x < cell.strandlength; x++) {
			cell.p = &(stranddata[x]);
			if (x == 0) {
				cell.p->vwest = cell.p->v;
			} else {
				cell.l = &(stranddata[x - 1]);
				cell.p->vwest = cell.l->v;
			}
			if (x == (cell.strandlength - 1)) {
				cell.p->veast = cell.p->v;
			} else {
				cell.r = &(stranddata[x + 1]);
				cell.p->veast = cell.r->v;
			}

			cell.update(x);

			if (i % cell.skip == 0 && cell.t > cell.CL
					&& fmod(cell.t + cell.CL, cell.tsave) >= 0
					&& fmod(cell.t + cell.CL, cell.tsave) <= cell.CL) { //cell.t>=cell.tsave) //JORDI
				cell.save(x, cell.strandlength);
			}
		}

		/*
		 * Sí, es muy redundante pero asegura que la condición se cumpla cada vez que se inicia un pulso a guardar.
		 */
		if (fmod(cell.t, cell.tsave) <= 1) {
			cell.QTint = cell.CL;
		}

		if ( /*i%cell.skip==0 && */cell.t > cell.CL
				&& fmod(cell.t + cell.CL, cell.tsave) >= 0
				&& fmod(cell.t + cell.CL, cell.tsave) <= cell.CL) { //cell.t>=cell.tsave) //JORDI
			cell.ecg_save(i); //JORDI
		}

		if (i % (500000 / cell.strandlength) == 0) {
			printf(" %5.01f %%\n",0.1*(int)(cell.t / cell.ft * 1000));

		}

		if (isnan(cell.p->v) && cell.t > (cell.ft - cell.CL)) {
			std::cout << "t = " << cell.t << std::endl;
			perror("v is nan");
			break;
		}

		//Shouldn't this happen BEFORE saving all data? //JORDI
		cell.t = cell.t + cell.dt;
		i++;
	}

	/****************************************************************************************************************
	 *
	 *                                               END OF MAIN LOOP
	 *
	 ****************************************************************************************************************/

	//guarda el estado de todas las células //JORDI
	if((savemode == 1)||(savemode == 3))
	{
		for (int i = 0; i < cell.strandlength; i++)
			stranddata[i].saveCell();		
	}

	cell.apd_heading();
	for (int x = 0; x < cell.strandlength; x++) {
		cell.p = &(stranddata[x]);
		cell.apd_save(x);
	}
	return (0);
}
