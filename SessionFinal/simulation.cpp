#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include "particles.h"
#include <string>
#include <iostream>
#include <fstream>
#include "ic_generator.h"
#include "mm_systime.h"

//functions for cosmological values
#include "dofa.h"
#include "eofa.h"
#include "fofa.h"
#include "omofa.h"
#include "tofa.h"

using namespace std;

int main()
{
	double t1Total = mm_systime();
	//Simulation parameters:
	int Np = 2048;  //Number of particles
	int timeSteps = 1000;  //Number of timesteps
	int realisations = 1;  //Number of realisations to be performed
	int snaps = 10;  //Number of snapshots to be saved
	bool randPos = true;  //Bool to specify if positions should be randomized
	double L = 1000;  //Periodic box size
	double H0 = 100;  //H0 value
	double omegam0 = 0.32;  //density

	double ai = 0.1;  //Initial scale factor
	double af = 0.5;  //Final scale factor
	double si = sqrt(ai);
	double sf = sqrt(af);
	double s = si;
	double a = ai;
	double t = tofa(a, omegam0);
	double dt = 0;

	//Initialize arrays for average and error of the average
	double iaverageSpectrum[1025];
	double ierrorAverage[1025];
	double faverageSpectrum[1025];
	double ferrorAverage[1025];
	for(int i = 0; i < 1025; i++)
	{
		iaverageSpectrum[i] = 0.;
		ierrorAverage[i] = 0.;
		faverageSpectrum[i] = 0.;
		ferrorAverage[i] = 0.;
	}

	//PERFORM REALISATIONS
	for(int i = 0; i < realisations; i++)
	{
		string dataFile = "./Data/" + to_string(i);  //Name of the files containing the data of the simulation
		//INITIALIZATION
		double pos[Np];
		double vel[Np];
		for(int b = 0; b < Np; b++)
		{
			pos[b] = b * (L / Np);
			vel[b] = 0;
		}
		double specTheo[2048];
		read_binary("initial_pk_linear_theo.data", 2048, specTheo);
		if(randPos)
		{
			ic_generator(Np, L, H0 * eofa(ai, omegam0) * fofa(ai, omegam0), 1, specTheo, pos, vel);
		}
		particles syst = particles(Np, pos, vel);

		//Save initial conditions
		syst.getXbin(dataFile + "pos0.data");
		// syst.getVbin(dataFile + "vel0.data");
		// syst.getAbin(dataFile + "acc0.data");
		double *spec = syst.spectrumSystem(L);
		write_binary(dataFile + "spec0.data", 1025, spec);
		//Calculate sum and sum squared
		for (int b = 0; b < 1025; b++)
		{
			iaverageSpectrum[b] += spec[b];
			ierrorAverage[b] += spec[b] * spec[b];
		}

		//PERFORM THE SIMULATION STEPS
		for(int b = 1; b <= timeSteps; b++)
		{
			s = si + (b * ((sf - si) / timeSteps));
			a = s * s;
			double nt = tofa(a, omegam0);
			dt = nt - t;
			double c = 2 * M_PI * (1.3936388 * pow(10, -28)) * omegam0 * (2.77573 * pow(10, 11));
			c *= L / (Np * a);
			syst.acceleration(H0*eofa(a, omegam0), 4.5, L);
			syst.moove(dt, L);

			if(b % (timeSteps / snaps) == 0 && b != timeSteps)
			{
				//Save snapshot
				syst.getXbin(dataFile + "pos" + to_string(b) + ".data");
				// syst.getVbin(dataFile + "vel" + to_string(b) + ".data");
				// syst.getAbin(dataFile + "acc" + to_string(b) + ".data");
				spec = syst.spectrumSystem(L);
				write_binary(dataFile + "spec" + to_string(b) + ".data", 1025, spec);
			}
			t = nt;
		}
		//Save final conditions
		syst.getXbin(dataFile + "pos" + to_string(timeSteps) + ".data");
		// syst.getVbin(dataFile + "vel" + to_string(timeSteps) + ".data");
		// syst.getAbin(dataFile + "acc" + to_string(timeSteps) + ".data");
		spec = syst.spectrumSystem(L);
		write_binary(dataFile + "spec" + to_string(timeSteps) + ".data", 1025, spec);
		//Calculate sum and sum squared
		for (int b = 0; b < 1025; b++)
		{
			faverageSpectrum[b] += spec[b];
			ferrorAverage[b] += spec[b] * spec[b];
		}
	}
	double t2Total = mm_systime();
	cout << "TOTAL EXECUTION TIME: " << double(t2Total-t1Total)/1000. << " seconds" << endl;
	cout << "TIME PER REALISATION: " << double(t2Total-t1Total)/(1000 * realisations) << " seconds" << endl;

	//Calculate average and error of the average for initial realisations
	for(int i = 0; i < 1025; i++)
	{
		iaverageSpectrum[i] /= realisations;
		ierrorAverage[i] = (ierrorAverage[i] / realisations) - (iaverageSpectrum[i] * iaverageSpectrum[i]);
		ierrorAverage[i] = sqrt(ierrorAverage[i]);
	}
	//Save them into files
	write_binary("initialAverageSpectrum.data", 1025, iaverageSpectrum);
	write_binary("initialErrorSpectrum.data", 1025, ierrorAverage);
	//Calculate average and error of the average for final realisations
	for (int i = 0; i < 1025; i++)
	{
		faverageSpectrum[i] /= realisations;
		ferrorAverage[i] = (ferrorAverage[i] / realisations) - (faverageSpectrum[i] * faverageSpectrum[i]);
		ferrorAverage[i] = sqrt(ferrorAverage[i]);
	}
	//Save them into files
	write_binary("finalAverageSpectrum.data", 1025, faverageSpectrum);
	write_binary("finalErrorSpectrum.data", 1025, ferrorAverage);
}