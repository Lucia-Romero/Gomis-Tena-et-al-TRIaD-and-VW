#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "humandata.h"
#include "human.h"
#include <string>
using namespace std;

human::human(char argv1[], char argv2[], char argv3[], char argv4[], char argv5[], char argv6[],char argv7[], char argv8[], char argv9[], char argv10[]) 
{
    kC_D =  	pow(10,-1*(double) atof(argv1));  if(atof(argv1) == 9.999) kC_D=0;
    rC_D =  	pow(10,-1*(double) atof(argv2));  if(atof(argv2) == 9.999) rC_D=0;
    kO_D =  	pow(10,-1*(double) atof(argv3));  if(atof(argv3) == 9.999) kO_D=0;
    rO_D =  	pow(10,-1*(double) atof(argv4));  if(atof(argv4) == 9.999) rO_D=0;
    kI_D =  	pow(10,-1*(double) atof(argv5));  if(atof(argv5) == 9.999) kI_D=0;
    rI_D =  	pow(10,-1*(double) atof(argv6));  if(atof(argv6) == 9.999) rI_D=0; 
	Dofetilide= pow(10,-1*(double) atof(argv7));  if(atof(argv7) >  99.0 ) Dofetilide=0; 
	Dofetilide= Dofetilide * 1e9; // El programa trabaja en nM

	CL        = atof(argv8);
	beats     = atoi(argv9);
	beatssave = atoi(argv10);

	Markov = 1; 			   

	strandlength = 165;
	stim_here = 0;

	ft = beats * CL;
	dt = 0.003;
	skip = 200;

	//tsave=ft-beatssave*CL; //O'HARA-RUDY
	/*
	 * If third parameter is 0, then only save the last pulse. Else, use provided period. 
	 */
	 
	if (beatssave == 0) {
		tsave = ft;
	} else {
		tsave = beatssave;
	}

	QTint = CL;

	///////////ESTIMULO/////////////
	start = 1.0;     // 1.0
	amp = -200;      
	duration = 1.0;  // 1.0
	////////////////////////////////

	endo = 60;
	M = 105;
	epi = strandlength - 1;

	nao = 140.0;
	cao = 1.8;
	ko = 5.4;
	BSRmax = 0.047;
	KmBSR = 0.00087;
	BSLmax = 1.124;
	KmBSL = 0.0087;
	cmdnmax = 0.05;
	kmcmdn = 0.00238;
	trpnmax = 0.07;
	kmtrpn = 0.0005;
	csqnmax = 10.0;
	kmcsqn = 0.8;
	aCaMK = 0.05;
	bCaMK = 0.00068;
	CaMKo = 0.05;
	KmCaM = 0.0015;
	KmCaMK = 0.15;

	C = 1.0;
	R = 8314.0;
	T = 310.0;
	F = 96485.0;
	L = 0.01;
	rad = 0.0011;
	vcell = 1000 * 3.14 * rad * rad * L;
	Ageo = 2 * 3.14 * rad * rad + 2 * 3.14 * rad * L;
	Acap = 2 * Ageo;
	vmyo = 0.68 * vcell;
	vmito = 0.26 * vcell;
	vsr = 0.06 * vcell;
	vnsr = 0.0552 * vcell;
	vjsr = 0.0048 * vcell;
	vss = 0.02 * vcell;

	gj = 2.5; // default = 2.5 //1.73;// //uS

	Rmyo = 150.0;       //ohm*cm
	radius = 11.0;  //um
	dX = 100.0; //um

	t = 0.0;
	n = 0;
	save_flag = 0;

    kC_D =  	pow(10,-1*(double) atof(argv1));  if(atof(argv1) == 9.999) kC_D=0;
    rC_D =  	pow(10,-1*(double) atof(argv2));  if(atof(argv2) == 9.999) rC_D=0;
    kO_D =  	pow(10,-1*(double) atof(argv3));  if(atof(argv3) == 9.999) kO_D=0;
    rO_D =  	pow(10,-1*(double) atof(argv4));  if(atof(argv4) == 9.999) rO_D=0;
    kI_D =  	pow(10,-1*(double) atof(argv5));  if(atof(argv5) == 9.999) kI_D=0;
    rI_D =  	pow(10,-1*(double) atof(argv6));  if(atof(argv6) == 9.999) rI_D=0; 
	Dofetilide= pow(10,-1*(double) atof(argv7));  if(atof(argv7) >  99.0 ) Dofetilide=0; 
	Dofetilide= Dofetilide * 1e9; // El programa trabaja en nM

    sprintf(fpth,"%04d_%04d_%04d_%04d_%04d_%04d"
					,(int)(1000*atof(argv1)+0.5)
					,(int)(1000*atof(argv2)+0.5)
					,(int)(1000*atof(argv3)+0.5)
					,(int)(1000*atof(argv4)+0.5)
					,(int)(1000*atof(argv5)+0.5)
					,(int)(1000*atof(argv6)+0.5));


	if(atof(argv7)<10.0)
     sprintf(fpath,"./output/%s_0%02d_%04d_%04d"
					,fpth
					,(int)(  10*atof(argv7)+0.5)
					,(int)(CL)
					,beats					
					,beatssave);
    else
     sprintf(fpath,"./output/%s_0%02d_%04d_%04d"
					,fpth
					,(int)(  10*atof(argv7)+0.5)
					,(int)(CL)
					,beats					
					,beatssave);

	sprintf(apd_path,      "%s_APD.txt", fpath);
	sprintf(voltages_path, "%s_APs.txt", fpath);
	sprintf(one_path,      "%s__1_.txt", fpath);
	sprintf(two_path,      "%s__2_.txt", fpath);
	sprintf(three_path,    "%s__3_.txt", fpath);
	sprintf(four_path,     "%s__4_.txt", fpath);
	sprintf(five_path,     "%s__5_.txt", fpath);
	sprintf(ecg_path,      "%s_ECG.txt", fpath);
	sprintf(qtint_path,    "%s_QT_.txt", fpath);
}
