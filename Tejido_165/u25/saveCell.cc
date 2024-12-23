#include <math.h>
#include <stdio.h>
#include <iostream>
#include "humandata.h"
#include "human.h"

void humandata::saveCell() {

	cell_file = fopen(cell_save_path, "w");

	fprintf(cell_file, 
			"%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n"
			"%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n"
			"%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n"
			"%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n"
			"%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n"
			"%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n"
			"%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n%g\n"
			"%d\n%d\n%d",
			v, 
			vwest, 
			veast, 
			vrest, 
			
			nai, 
			nass, 
			ki, 
			kss, 
			cai,
			
			cass, 
			cansr, 
			cajsr, 
			m, 
			hf, 
			hs, 
			jf, 
			js, 
			mL, 
			hL, 
			a, 
			iF, 
			iS, 
			d, 
			ff, 
			fs,
			fcaf, 
			fcas, 
			jca, 
			nca, 
			xrf, 
			xrs, 
			xs1, 
			xs2, 
			xk1, 
			Jrelnp, 
			Jrelp, 
			CaMKt, 
			hsp, 
			jfp, 
			jsp, 
			hLp, 
			ap, 
			iFp, 
			iSp, 
			ffp, 
			fcafp, 
			fcasp, 

			I_IKr    ,						
			C3_IKr   ,						
			C2_IKr   ,						
			O_IKr    ,															
			C1_IKr   , 															

			I_IKr_D  ,						
			C3_IKr_D ,						
			C2_IKr_D ,						
			O_IKr_D  ,						
			C1_IKr_D ,	 					
			
			vold, 
			vdot,
			vdotmax, 
			tvdotmax, 
			vdotold, 
			vmax, 
			TR, 
			APD90, 
			APD60, 
			APD50, 
			APD30,
			CL, 
			
			APDflag, 

			endo, 
			M);
			
	fclose(cell_file);
}
