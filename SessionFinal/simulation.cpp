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
		write_binary(dataFile + "spec0.data", 1025, spec);

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
				spec = syst.spectrumSystem(L);
				write_binary(dataFile + "spec" + to_string(b) + ".data", 1025, spec);
			}
			t = nt;
		}
		//Save final conditions
		syst.getXbin(dataFile + "pos" + to_string(timeSteps) + ".data");
		syst.getVbin(dataFile + "vel" + to_string(timeSteps) + ".data");
		syst.getAbin(dataFile + "acc" + to_string(timeSteps) + ".data");
		spec = syst.spectrumSystem(L);
		write_binary(dataFile + "spec" + to_string(timeSteps) + ".data", 1025, spec);
	}
}