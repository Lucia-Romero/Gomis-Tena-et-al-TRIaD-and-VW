#include <iostream>
#include <math.h>
#include <stdio.h>
#include "humandata.h"
#include "human.h"

#include <fstream>
using std::ifstream;

humandata::humandata() {
}

void humandata::load(int x) {

	//sprintf(cell_save_path, "./cellstates/Cell_%d.txt", x);
	sprintf(cell_save_path, "./cellstates/%s_%03d.txt", fcell_save_path, x);

	ifstream cellin;
	cellin.open(cell_save_path);

	double states[69];
	for (int i = 0; i < 69; i++) {
		cellin >> states[i];
	}

	cellin >> APDflag;
	cellin >> endo;
	cellin >> M;

	cellin.close();

	int i = -1;

	v        = states[++i];
	vwest    = states[++i];
	veast    = states[++i];
	vrest    = states[++i];
	
	nai      = states[++i];
	nass     = states[++i];
	ki       = states[++i];
	kss      = states[++i];
	cai      = states[++i];
	cass     = states[++i];
	cansr    = states[++i];
	cajsr    = states[++i];
	m        = states[++i];
	hf       = states[++i];
	hs       = states[++i];
	jf       = states[++i];
	js       = states[++i];
	mL       = states[++i];
	hL       = states[++i];
	a        = states[++i];
	iF       = states[++i];
	iS       = states[++i];
	d        = states[++i];
	ff       = states[++i];
	fs       = states[++i];
	fcaf     = states[++i];
	fcas     = states[++i];
	jca      = states[++i];
	nca      = states[++i];
	xrf      = states[++i];
	xrs      = states[++i];
	xs1      = states[++i];
	xs2      = states[++i];
	xk1      = states[++i];
	Jrelnp   = states[++i];
	Jrelp    = states[++i];
	CaMKt    = states[++i];
	hsp      = states[++i];
	jfp      = states[++i];
	jsp      = states[++i];
	hLp      = states[++i];
	ap       = states[++i];
	iFp      = states[++i];
	iSp      = states[++i];
	ffp      = states[++i];
	fcafp    = states[++i];
	fcasp    = states[++i];

	I_IKr    = states[++i];						/* Lucia 18-July-2011: To include IKr Fink formulation */
	C3_IKr   = states[++i];						/* Lucia 18-July-2011: To include IKr Fink formulation */
	C2_IKr   = states[++i];						/* Lucia 18-July-2011: To include IKr Fink formulation */
	O_IKr    = states[++i];						/* Lucia 18-July-2011: To include IKr Fink formulation */									
	C1_IKr   = states[++i]; 					/* Lucia 18-July-2011: To include IKr Fink formulation */									

												/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	I_IKr_D  = states[++i];						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	C3_IKr_D = states[++i];						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	C2_IKr_D = states[++i];						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	O_IKr_D  = states[++i];						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	C1_IKr_D = states[++i]; 					/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	
	vold     = states[++i];
	vdot     = states[++i];
	vdotmax  = states[++i];
	tvdotmax = states[++i];
	vdotold  = states[++i];
	vmax     = states[++i];
	TR       = states[++i];
	APD90    = states[++i];
	APD60    = states[++i];
	APD50    = states[++i];
	APD30    = states[++i];	
	CL       = states[++i];
	

	
	
}

extern char fpt[250];

void humandata::init(int x, double CLin, int endoin, int Min) { //JORDI

	sprintf(cell_save_path, "./cellstates/%s_%03d.txt", fcell_save_path, x);
	//sprintf(cell_save_path, "./cellstates/Cell_%d.txt", x);

	CL = CLin; //JORDI

	endo = endoin;
	M = Min;

	sprintf(load_path_endo, "./endo/states%g_%s.txt", CL, fpt);
	sprintf(load_path_M, "./M/states%g_%s.txt", CL, fpt);
	sprintf(load_path_epi, "./epi/states%g_%s.txt", CL, fpt);

	//sprintf(load_path_endo, "./endo/states%g.txt", CL);
	//sprintf(load_path_M, "./M/states%g.txt", CL);
	//sprintf(load_path_epi, "./epi/states%g.txt", CL);

	ifstream statesin;
	if (x > M) {
		statesin.open(load_path_epi); // Cambio por comentario de Juanfran
	} else if (x > endo) {
		statesin.open(load_path_M);
	} else {
		statesin.open(load_path_endo); // Cambio por comentario de Juanfran
	}

	double states[54];
	for (int i = 0; i < 54; i++) { //44 Cambio por Lucia
		statesin >> states[i];
	}
	statesin.close();

	int i = -1;
	
	v        = states[++i];
	vwest    = v;
	veast    = v;
	vrest    = v;

	nai      = states[++i];
	nass     = states[++i];
	ki       = states[++i];
	kss      = states[++i];
	cai      = states[++i];
	
	cass     = states[++i];
	cansr    = states[++i];
	cajsr    = states[++i];
	m        = states[++i];
	hf       = states[++i];
	hs       = states[++i];
	jf       = states[++i];
	js       = states[++i];
	mL       = states[++i];
	hL       = states[++i];
	a        = states[++i];
	iF       = states[++i];
	iS       = states[++i];
	d        = states[++i];
	ff       = states[++i];
	fs       = states[++i];
	fcaf     = states[++i];
	fcas     = states[++i];
	jca      = states[++i];
	nca      = states[++i];
	xrf      = states[++i];
	xrs      = states[++i];
	xs1      = states[++i];
	xs2      = states[++i];
	xk1      = states[++i];
	Jrelnp   = states[++i];
	Jrelp    = states[++i];
	CaMKt    = states[++i];
	hsp      = states[++i];
	jfp      = states[++i];
	jsp      = states[++i];
	hLp      = states[++i];
	ap       = states[++i];
	iFp      = states[++i];
	iSp      = states[++i];
	ffp      = states[++i];
	fcafp    = states[++i];
	fcasp    = states[++i];

	I_IKr    = states[++i];// = 0;						/* Lucia 18-July-2011: To include IKr Fink formulation */
	C3_IKr   = states[++i];// = 1;						/* Lucia 18-July-2011: To include IKr Fink formulation */
	C2_IKr   = states[++i];// = 0;						/* Lucia 18-July-2011: To include IKr Fink formulation */
	O_IKr    = states[++i];// = 0;						/* Lucia 18-July-2011: To include IKr Fink formulation */									
	C1_IKr   = states[++i];// = 0; 						//Lucia 18-July-2011: It was: C1_IKr= 1-(I_IKr + C3_IKr + C2_IKr + O_IKr); 

														/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	I_IKr_D  = states[++i];// = 0;						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	C3_IKr_D = states[++i];// = 0;						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	C2_IKr_D = states[++i];// = 0;						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	O_IKr_D  = states[++i];// = 0;						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	C1_IKr_D = states[++i];// = 0; 						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
	
	vold     = v;
	vdot     = 0;
	vdotmax  = 0;
	tvdotmax = 0;
	vdotold  = 0;
	
	TR       = 0;
	APD90    = 0;
	APD60    = 0;
	APD50    = 0;
	APD30    = 0;
	
	APDflag  = 0;
	
}
