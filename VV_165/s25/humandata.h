class humandata {
public:

	humandata();
	void init(int x, double CLin, int endoin, int Min); //JORDI
	void load(int x);
	void saveCell();

	FILE *cell_file;

	double v, vwest, veast, vrest,mxtail;
	double nai, nass, ki, kss, cai, cass, cansr, cajsr;
	double m, hf, hs, jf, js, mL, hL, a, iF, iS, d, ff, fs, fcaf, fcas, jca,
			nca, xrf, xrs, xs1, xs2, xk1;
	double Jrelnp, Jrelp;
	double CaMKt;
	double hsp, jfp, jsp, hLp, ap, iFp, iSp, ffp, fcafp, fcasp;
	double vold, vdot, vdotmax, tvdotmax, vdotold, vmax, TR, APD90, APD60,
			APD50, APD30;
	int APDflag;
	char load_path_endo[250], load_path_M[250], load_path_epi[250];
	char fcell_save_path[250], cell_save_path[250];
	double CL;
	int endo, M;
	double I_IKr, C3_IKr, C2_IKr, O_IKr, C1_IKr; 			
	double I_IKr_D, C3_IKr_D, C2_IKr_D, O_IKr_D, C1_IKr_D; 	
};
