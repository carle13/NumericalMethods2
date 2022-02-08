#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include "particles.h"
#include <string>
#include <iostream>
#include <fstream>
#include "ic_generator.h"

//functions for cosmological values
#include "dofa.h"
#include "eofa.h"
#include "fofa.h"
#include "omofa.h"
#include "tofa.h"

using namespace std;

int main()
{
	//Simulation parameters:
	int Np = 2048;  //Number of particles
	int timeSteps = 1000;  //Number of timesteps
	int realisations = 100;  //Number of realisations to be performed
	string dataFile = "./Data/";  //Name of the files containing the data of the simulation
	int snaps = 50;  //Number of snapshots to be saved
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
		syst.getVbin(dataFile + "vel0.data");
		syst.getAbin(dataFile + "acc0.data");
		double *spec = syst.spectrumSystem(L);
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
			syst.moove(dt, L);

			if(b % (timeSteps / (snaps - 2)) == 0 && b != timeSteps)
			{
				//Save snapshot
				syst.getXbin(dataFile + "pos" + to_string(b) + ".data");
				syst.getVbin(dataFile + "vel" + to_string(b) + ".data");
				syst.getAbin(dataFile + "acc" + to_string(b) + ".data");
			}
			t = nt;
		}
		//Save final conditions
		syst.getXbin(dataFile + "pos" + to_string(timeSteps) + ".data");
		syst.getVbin(dataFile + "vel" + to_string(timeSteps) + ".data");
		syst.getAbin(dataFile + "acc" + to_string(timeSteps) + ".data");
		spec = syst.spectrumSystem(L);
		//Calculate sum and sum squared
		for (int b = 0; b < 1025; b++)
		{
			faverageSpectrum[b] += spec[b];
			ferrorAverage[b] += spec[b] * spec[b];
		}
	}
	//Calculate average and error of the average for initial realisations
	for(int i = 0; i < 1025; i++)
	{
		iaverageSpectrum[i] /= 201;
		ierrorAverage[i] = (ierrorAverage[i] / 201) - (iaverageSpectrum[i] * iaverageSpectrum[i]);
		ierrorAverage[i] = sqrt(ierrorAverage[i]);
	}
	//Save them into files
	write_binary("initialAverageSpectrum.data", 1025, iaverageSpectrum);
	write_binary("initialErrorSpectrum.data", 1025, ierrorAverage);
	//Calculate average and error of the average for final realisations
	for (int i = 0; i < 1025; i++)
	{
		faverageSpectrum[i] /= 201;
		ferrorAverage[i] = (ferrorAverage[i] / 201) - (faverageSpectrum[i] * faverageSpectrum[i]);
		ferrorAverage[i] = sqrt(ferrorAverage[i]);
	}
	//Save them into files
	write_binary("finalAverageSpectrum.data", 1025, faverageSpectrum);
	write_binary("finalErrorSpectrum.data", 1025, ferrorAverage);
}