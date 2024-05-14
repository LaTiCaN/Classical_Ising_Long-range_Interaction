#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "/home/heejeong/Lib/NRinC/nrutil.c"
#include "/home/heejeong/Lib/dSFMT-src-2.2.3/dSFMT.h"

#define J 1.0


int main(int argc, char **argv) {
	int i, j, k;
	int nr, nl;
	int Nv; //Max distance of long-range interaction
	int L;
	int *spins;
	float al, T;
	double eng;
	double E;
	double M;
	double Esum, E2sum;
	double Msum, M2sum, M4sum;
	float spec;
	unsigned MCS, step;
	unsigned long seed;
	dsfmt_t dsfmt;
	char datafile[80];
	int repeat, index;
	FILE *fp;

	if (argc < 7) {
		printf("Usage: Ising  alpha  temperature  MCS  repeat\n");
		exit(1);
	}

	L = atoi(argv[1]);
	Nv = atoi(argv[2]);
	al = atof(argv[3]);
	T = atof(argv[4]);
	MCS = atoi(argv[5]);
	repeat = atoi(argv[6]);

	spins = ivector(0,L-1);

	seed = getpid() + getppid() + (long)time(NULL);
	dsfmt_init_gen_rand(&dsfmt,seed);

	sprintf(datafile, "./l%dal%.2fT%.2f.dat",L,al,T);
    fp = fopen(datafile,"w+");

	if (fp == NULL){
		printf("Error opening file.\n");
		exit(1);
	}

	for (index = 1; index <= repeat; index++) {

		if (T == 0) T = 0.0001;

		//eng = 0.;
		E = 0.0;
		Esum = E2sum = 0.0;
		Msum = M2sum = M4sum = 0.0;
		spec = 0.0;

	 	//initialize spin
		for (i = 0; i < L; i++) 
		{
			spins[i] = (dsfmt_genrand_close_open(&dsfmt) < 0.5) ? 1 : -1;
		}

		// metropolis
		for (step = 0; step < MCS; step++) 
		{
			M = 0.0;
			eng = 0.0;
			
			for (i = 0; i < L; i++) 
			{
				int site = (int)(L * dsfmt_genrand_close_open(&dsfmt));
       			double delta_E = 0.0;
        		
				for (j=1; j<=Nv; j++) // j is distance of long-range interaction
				{ 
                    nl = (site - j + L) % L; // Left neighbor
                    nr = (site + j) % L;     // Right neighbor

                    double inter = J / pow(j, al);
                    delta_E += 2.0 * inter * spins[site] * (spins[nl] + spins[nr]);
                }

        		if (delta_E < 0 || (dsfmt_genrand_close_open(&dsfmt) < exp(-delta_E / T))){
					spins[site] = -spins[site];
				}
    		}

			//measure
    		for(i = 0; i < L; i++)
			{
				for (j=1; j<=Nv; j++) 
				{
                    nl = (i - j + L) % L; // Left neighbor
                    nr = (i + j) % L;     // Right neighbor

                    double inter = J / pow(j, al);
                    eng += -inter * spins[i] * (spins[nl] + spins[nr]);
                }
        		M += spins[i];
    		}
			eng /= 2;
			//E = eng / L;
			E = fabs(eng); //for avoiding double counting problem
    		M /= L;
    		
			Esum += E;
			E2sum += E * E;
			Msum += fabs(M);
			M2sum += M * M;
			M4sum += M * M * M * M;
		}

		Esum /= MCS;
		E2sum /= MCS;
		Msum /= MCS;
		M2sum /= MCS;
		M4sum /= MCS;

		spec = (E2sum - (Esum * Esum))/(T*T);

		fprintf(fp, "%.2f	%.20f	%.20f	%.20f	%.20f	%.20f	%.4f\n", T, Msum, M2sum, M4sum, Esum, E2sum, spec);
		
	}
	fclose(fp);
	return 0;
}
