#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "humandata.h"
#include "human.h"
 
#include <fstream>
using std::ifstream;

//#define sv_ECG 1
//#define sv_APD 2
//#define sv_12345 3
//#define sv_voltages 4
 
char fpt[250];
int t_extra;
int x;
int condicion=1;

int Minimo;
int Maximo;
int Ensayo;
 
int main(int argc, char *argv[]) 
{	int i,n;
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
 
 
        FILE *TR_MX;
        int savemode = atoi(argv[11]);

    /****************************************************************************************************************/
    /* Primera vez, solo para obtener el momento final del Potencial de accion                                      */
    /****************************************************************************************************************/
        human cell(argv[1], argv[2],argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], t_extra);

        humandata *stranddata;
        stranddata = new humandata[cell.strandlength];
 
        for (i = 0; i < cell.strandlength; i++) 
        {
                cell.extra_flag = 0;

                strncpy(stranddata[i].fcell_save_path, cell.fpth, sizeof(cell.fpth));  
 
                if((savemode == 2)||(savemode == 3))
                                stranddata[i].load(i + 1);
                else
                                stranddata[i].init(i + 1, cell.CL, cell.endo, cell.M); 
        }
        i = 1;
        while (cell.t <= cell.ft) 
        {
                for (x = 0; x < cell.strandlength; x++) 
                {
                        cell.p = &(stranddata[x]);
                        if (x == 0) 
                        {
                                cell.p->vwest = cell.p->v;
                        } 
                        else 
                        {
                                cell.l = &(stranddata[x - 1]);
                                cell.p->vwest = cell.l->v;
                        }
                        if (x == (cell.strandlength - 1)) 
                        {
                                cell.p->veast = cell.p->v; 
                        } 
                        else 
                        {
                                cell.r = &(stranddata[x + 1]);
                                cell.p->veast = cell.r->v;
                        }
 
                        cell.update(x);
 
                        cell.TR_max = (cell.TR_max < cell.p->TR) ? (cell.p->TR) : (cell.TR_max);
                        
                        if (       i % cell.skip == 0 
                                        && cell.t > cell.CL
                                        && fmod(cell.t + cell.CL, cell.tsave) >= 0
                                        && fmod(cell.t + cell.CL, cell.tsave) <= cell.CL) 
                        { 
                                  cell.save(x, cell.strandlength); 
                        }
                }
 
                if (isnan(cell.p->v) && cell.t > (cell.ft - cell.CL))  break;

                cell.t = cell.t + cell.dt;
                i++;
          }//(cell.t <= cell.ft)

          // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
                TR_MX = fopen(cell.TR_mx_path,"a");

                fprintf(TR_MX,"\nTiempo repolarizacion:",cell.extra_start);
	        int xx = (int) (0.5 + ((float)cell.strandlength - 30.0	)/38.0);
                for (x = 15; x < cell.strandlength - 15; x = x + xx)
                {
                     cell.p = &(stranddata[x]);
                     if(x!=cell.extra_stim_here)
                       	fprintf(TR_MX," %3d  ",(int)fmod(cell.p->TR,cell.CL) );
		     else
			fprintf(TR_MX,"[%3d] ",(int)fmod(cell.p->TR,cell.CL) );               
		}
                fprintf(TR_MX,"\n");
 
                cell.p = &(stranddata[cell.extra_stim_here]);
                Minimo = (int)fmod(cell.p->TR,cell.CL) - 20; //Sugerencia de Lucia
                Maximo = Minimo + 200;
                Ensayo = (int)((Minimo+Maximo)/2);

                fclose(TR_MX);
         // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    /****************************************************************************************************************/
    /* Iteracion para buscar conduccUnidireccional_min                                                              */
    /****************************************************************************************************************/
	int periodoRefractario_max    = Minimo;
 	int conduccUnidireccional_max = Minimo;

	int conduccUnidireccional_min = Maximo;
	int conduccBidireccional_min  = Maximo;
	
	int VentanaVulnerable = conduccBidireccional_min - conduccUnidireccional_min;

	int inicioFibraDespolariza = 0;
	int final_FibraDespolariza = 0;
	delete stranddata;
    /*****************************************************************************************************************/
	condicion = 1;
	while(condicion)
	{
        TR_MX = fopen(cell.TR_mx_path,"a");
	fprintf(TR_MX,"{%d,%d} -> ",Minimo,Maximo);
	fclose(TR_MX);

        human cell(argv[1], argv[2],argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], t_extra);

        humandata *stranddata;
        stranddata = new humandata[cell.strandlength];
 
        for (i = 0; i < cell.strandlength; i++) 
        {
                cell.extra_flag = 1;
				cell.extra_start= (double) Ensayo;
				
                strncpy(stranddata[i].fcell_save_path, cell.fpth, sizeof(cell.fpth));  
 
                if((savemode == 2)||(savemode == 3))
                                stranddata[i].load(i + 1);
                else
                                stranddata[i].init(i + 1, cell.CL, cell.endo, cell.M); 
        }
        i = 1;
        while (cell.t <= cell.ft) 
        {
                for (x = 0; x < cell.strandlength; x++) 
                {
                        cell.p = &(stranddata[x]);
                        if (x == 0) 
                        {
                                cell.p->vwest = cell.p->v;
                        } 
                        else 
                        {
                                cell.l = &(stranddata[x - 1]);
                                cell.p->vwest = cell.l->v;
                        }
                        if (x == (cell.strandlength - 1)) 
                        {
                                cell.p->veast = cell.p->v; 
                        } 
                        else 
                        {
                                cell.r = &(stranddata[x + 1]);
                                cell.p->veast = cell.r->v;
                        }
 
                       	cell.update(x);
			cell.TR_max = (cell.TR_max < cell.p->TR) ? (cell.p->TR) : (cell.TR_max);
                        if (       i % cell.skip == 0 
                                        && cell.t > cell.CL
                                        && fmod(cell.t + cell.CL, cell.tsave) >= 0
                                        && fmod(cell.t + cell.CL, cell.tsave) <= cell.CL) 
                        { 
                                  cell.save(x, cell.strandlength); 
                        }
                }
 
                if (isnan(cell.p->v) && cell.t > (cell.ft - cell.CL))  
                {
                        TR_MX = fopen(cell.TR_mx_path,"a");
                        fprintf(TR_MX,"\nnan break\n");
                        fclose( TR_MX);
                        break;
                }

                cell.t = cell.t + cell.dt;
                i++;
          }//(cell.t <= cell.ft)
		  
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 x = 15; 
		 cell.p = &(stranddata[x]);
		 inicioFibraDespolariza = (cell.p->mxtail > 30.0) ? 1 : 0;
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 x = cell.strandlength - 15;
		 cell.p = &(stranddata[x]);
		 final_FibraDespolariza = (cell.p->mxtail > 30.0) ? 1 : 0;
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 if((inicioFibraDespolariza == 0) && (final_FibraDespolariza == 0))
		 {
			Minimo = Ensayo;
			    periodoRefractario_max    = Ensayo;	           
		 }
		 // - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 if( ((inicioFibraDespolariza == 1) && (final_FibraDespolariza == 0)) ||
                     ((inicioFibraDespolariza == 0) && (final_FibraDespolariza == 1)) )
		 {
			Maximo = Ensayo;

                        if(conduccUnidireccional_min > Ensayo)
                           conduccUnidireccional_min = Ensayo;

			if(conduccUnidireccional_max < Ensayo)
			   conduccUnidireccional_max = Ensayo;
		 }
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 if((inicioFibraDespolariza == 1) && (final_FibraDespolariza == 1))
		 {
			Maximo = Ensayo;

			if(conduccBidireccional_min > Ensayo)
			   conduccBidireccional_min = Ensayo;
		 }
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 condicion = (Minimo < Maximo-1);
                 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 if(condicion != 1)
		 {
	                 if((inicioFibraDespolariza == 0) && (final_FibraDespolariza == 0))
        	         {
                            Minimo = Ensayo;
 
                           if( conduccUnidireccional_min > Minimo )
                               conduccUnidireccional_min = Minimo;
 
		   	   if( conduccUnidireccional_max < conduccUnidireccional_min )
                               conduccUnidireccional_max = conduccUnidireccional_min;
                 	}
		 }
                 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
                 Ensayo = (int)((Minimo+Maximo)/2);		
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			TR_MX = fopen(cell.TR_mx_path,"a");	
                        fprintf(TR_MX,"%3d[%d%d]",(int)cell.extra_start,inicioFibraDespolariza, final_FibraDespolariza);
                        for (x = 15; x < cell.strandlength - 15; x = x + xx)
                        {
                                cell.p = &(stranddata[x]);
                                        fprintf(TR_MX," %5.01f",cell.p->mxtail);
                        } 
                        fprintf(TR_MX,"\n");
                        fclose(TR_MX);		  
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	delete stranddata;		  
	}

          // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
               TR_MX = fopen(cell.TR_mx_path,"a");
               fprintf(TR_MX,"\nResultado busqueda (1) -> ");
               fprintf(TR_MX,"Unidir min: [%d] ms, ",   conduccUnidireccional_min);
               fprintf(TR_MX,"Bidir min??  %d  ms\n\n", conduccBidireccional_min);
               fclose(TR_MX);
         // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    /****************************************************************************************************************/
	
    /****************************************************************************************************************/
    /* Iteracion para buscar conduccBidireccional_min                                                              */
    /****************************************************************************************************************/
	Minimo = conduccUnidireccional_max;
	Maximo = conduccBidireccional_min;
	Ensayo = (int)((Minimo+Maximo)/2);
    /****************************************************************************************************************/
        int valor_anterior=10,valor_actual=900;
	condicion = 1 * (Minimo < Maximo-1);
	while(condicion)
	{
	TR_MX = fopen(cell.TR_mx_path,"a");
	fprintf(TR_MX,"{%d,%d} -> ",Minimo,Maximo);
	fclose(TR_MX);

        human cell(argv[1], argv[2],argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], t_extra);

        humandata *stranddata;
        stranddata = new humandata[cell.strandlength];
 
        for (i = 0; i < cell.strandlength; i++) 
        {
                cell.extra_flag = 1;
				cell.extra_start= (double) Ensayo;
				
                strncpy(stranddata[i].fcell_save_path, cell.fpth, sizeof(cell.fpth));  
 
                if((savemode == 2)||(savemode == 3))
                                stranddata[i].load(i + 1);
                else
                                stranddata[i].init(i + 1, cell.CL, cell.endo, cell.M); 
        }
        i = 1;
        while (cell.t <= cell.ft) 
        {
                for (x = 0; x < cell.strandlength; x++) 
                {
                        cell.p = &(stranddata[x]);
                        if (x == 0) 
                        {
                                cell.p->vwest = cell.p->v;
                        } 
                        else 
                        {
                                cell.l = &(stranddata[x - 1]);
                                cell.p->vwest = cell.l->v;
                        }
                        if (x == (cell.strandlength - 1)) 
                        {
                                cell.p->veast = cell.p->v; 
                        } 
                        else 
                        {
                                cell.r = &(stranddata[x + 1]);
                                cell.p->veast = cell.r->v;
                        }
 
                        cell.update(x);
 			cell.TR_max = (cell.TR_max < cell.p->TR) ? (cell.p->TR) : (cell.TR_max);
                        if (       i % cell.skip == 0 
                                        && cell.t > cell.CL
                                        && fmod(cell.t + cell.CL, cell.tsave) >= 0
                                        && fmod(cell.t + cell.CL, cell.tsave) <= cell.CL) 
                        { 
                                  cell.save(x, cell.strandlength); 
                        }
                }
 
                if (isnan(cell.p->v) && cell.t > (cell.ft - cell.CL))
		{
			TR_MX = fopen(cell.TR_mx_path,"a");
		        fprintf(TR_MX,"\nnan break\n");
		        fclose(TR_MX);
			break;

		}
                cell.t = cell.t + cell.dt;
                i++;
          }//(cell.t <= cell.ft)
		  
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 x = 15; 
		 cell.p = &(stranddata[x]);
		 inicioFibraDespolariza = (cell.p->mxtail > 30.0) ? 1 : 0;
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 x = cell.strandlength - 15;
		 cell.p = &(stranddata[x]);
		 final_FibraDespolariza = (cell.p->mxtail > 30.0) ? 1 : 0;
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
                 if( ((inicioFibraDespolariza == 1) && (final_FibraDespolariza == 0)) ||
                     ((inicioFibraDespolariza == 0) && (final_FibraDespolariza == 1)) )		 
		 {
			Minimo = Ensayo;
			conduccUnidireccional_max = Ensayo;
		 }
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 if((inicioFibraDespolariza == 1) && (final_FibraDespolariza == 1))
		 {
			Maximo = Ensayo;
			conduccBidireccional_min  = Ensayo;
		 }
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		 Ensayo = (int)((Minimo+Maximo)/2);
		 condicion = (Minimo < Maximo-1);
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
                        TR_MX = fopen(cell.TR_mx_path,"a");
			valor_anterior = valor_actual;
			valor_actual = (int)cell.extra_start;
			condicion = (valor_actual == valor_anterior) ? 0: condicion;
			fprintf(TR_MX,"%3d[%d%d]",(int)cell.extra_start,inicioFibraDespolariza, final_FibraDespolariza);                                               
                        for (x = 15; x < cell.strandlength - 15; x = x + xx)
                        {
                                cell.p = &(stranddata[x]);
                                        fprintf(TR_MX," %5.01f",cell.p->mxtail);
                        } 
                        fprintf(TR_MX,"\n");
                        fclose(TR_MX);		  
		 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	delete stranddata;		  
	}

          // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
               TR_MX = fopen(cell.TR_mx_path,"a");

		fprintf(TR_MX,"\nResultado busqueda (2) -> ");
               	fprintf(TR_MX,"Unidir  min: [%d] ms, ",   conduccUnidireccional_min);
               	fprintf(TR_MX,"Bidir   min: [%d] ms\n\n", conduccBidireccional_min);

               fclose(TR_MX);
         // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -                                                                                                                    
    /****************************************************************************************************************/
        char* FileRslt = new char[80];
        FILE* RsltFile;
	sprintf(FileRslt,"./output/Rslt.txt");
        RsltFile = fopen(FileRslt, "a");
        fprintf(RsltFile,"%04d_%04d_%04d_%04d_%04d_%04d "
                                        ,(int)(1000*atof(argv[1])+0.5)
                                        ,(int)(1000*atof(argv[2])+0.5)
                                        ,(int)(1000*atof(argv[3])+0.5)
                                        ,(int)(1000*atof(argv[4])+0.5)
                                        ,(int)(1000*atof(argv[5])+0.5)
                                        ,(int)(1000*atof(argv[6])+0.5));
	fprintf(RsltFile,"conduccUnidireccional_min: %d conduccBidireccional_min: %d Ventana_Vulnerable: %d\n", conduccUnidireccional_min, conduccBidireccional_min, (conduccBidireccional_min-conduccUnidireccional_min) );
        fclose( RsltFile);
 
        return (0);
}
