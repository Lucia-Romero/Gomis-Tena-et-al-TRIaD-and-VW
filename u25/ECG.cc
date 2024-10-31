#include <math.h>
#include <stdio.h>
#include <iostream>
#include "humandata.h"
#include "human.h"

void human::ECG(int x) {
	if (x == 0) {
		Phi = 0.0;
		gradV = 0;
	}
	if (x >= 15 && x <= 149) { //ignore the ends as in gima & rudy
		double K = 1;
		Phi += K * (p->vwest - p->veast)
				/ pow(2.0 + (strandlength - x) / 100.0, 2.0);
		gradV += (p->vwest - p->veast);
	}
}

void human::ecg_heading() {
	ecg_file = fopen(ecg_path, "w");
	fprintf(ecg_file, "%-07s\t%-07s\t%-07s\t%-07s\n", "t", "Phi", "gradV",
			"CV");
	fclose(ecg_file);

	//JORDI
	QTint_file = fopen(qtint_path, "w");
	fprintf(QTint_file, "%-07s\t%-07s\n", "t", "QTint");
	fclose(QTint_file);
}

void human::ecg_save(int i) { //JORDI

	if (i % skip == 0) { //JORDI
		ecg_file = fopen(ecg_path, "a");
		fprintf(ecg_file, "%-016e\t%-07g\t%-07g\t%-07g\n", t + dt, Phi, gradV,
				CV); //-tsave
		fclose(ecg_file);
	}

	/*
	 //JORDI: lo he modificado para que guarde los QTint en archivos separados.
	 Así no se interfieren durante simulaciones en paralelo.
	 */

	if (QTint == CL && i % 10 == 0) //JORDI
		if (fmod(t + CL, tsave) > 250.0) //JORDI. "fmod(t+CL,tsave)" ERA t-tsave;
			if (fabs(gradV) <= 0.200) {
				QTint = fmod(t + CL, tsave); //JORDI
				QTint_file = fopen(qtint_path, "a"); //JORDI
				fprintf(QTint_file, "%-07g\t%-07g\n", t - QTint, QTint + dt); //JORDI
				fclose(QTint_file); //JORDI
			}
}
