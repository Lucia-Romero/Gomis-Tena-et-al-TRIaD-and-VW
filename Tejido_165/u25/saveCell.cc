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

			I_IKr    ,						/* Lucia 18-July-2011: To include IKr Fink formulation */
			C3_IKr   ,						/* Lucia 18-July-2011: To include IKr Fink formulation */
			C2_IKr   ,						/* Lucia 18-July-2011: To include IKr Fink formulation */
			O_IKr    ,						/* Lucia 18-July-2011: To include IKr Fink formulation */									
			C1_IKr   , 						/* Lucia 18-July-2011: To include IKr Fink formulation */									

			I_IKr_D  ,						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
			C3_IKr_D ,						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
			C2_IKr_D ,						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
			O_IKr_D  ,						/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
			C1_IKr_D ,	 					/* Lucia 2-August-2011: To include drug in IKr Fink formulation */
			
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
