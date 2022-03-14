#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include "particles.h"
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include "ic_generator.h"
#include "mm_systime.h"

//functions for cosmological values
#include "dofa.h"
#include "eofa.h"
#include "fofa.h"
#include "omofa.h"
#include "tofa.h"

using namespace std;

//Simulation parameters:
int Np = 2048;		   //Number of particles
int timeSteps = 10000;  //Number of timesteps
int realisations = 5; //Number of realisations to be performed
int snaps = 100;		   //Number of snapshots to be saved
bool randPos = false;   //Bool to specify if positions should be randomized
double L = 1000;	   //Periodic box size
double H0 = 100;	   //H0 value
double omegam0 = 0.9; //density

double ai = 0.1; //Initial scale factor
double af = 5.0; //Final scale factor
double si = sqrt(ai);
double sf = sqrt(af);

void realisation(int i)
{
	string dataFile = "./Data/" + to_string(i); //Name of the files containing the data of the simulation
	//INITIALIZATION
	double pos[Np];
	double vel[Np];
	for (int b = 0; b < Np; b++)
	{
		pos[b] = b * (L / Np);
		vel[b] = 0;
	}
	double specTheo[1025];
	read_binary("initial_pk_linear_theo.data", 1025, specTheo);
	if (randPos)
	{
		ic_generator(Np, L, H0 * eofa(ai, omegam0) * fofa(ai, omegam0), 1, specTheo, pos, vel);
	}
	particles syst = particles(Np, pos, vel);

	//Save initial conditions
	syst.getXbin(dataFile + "pos0.data");
	// syst.getVbin(dataFile + "vel0.data");
	// syst.getAbin(dataFile + "acc0.data");
	write_binary(dataFile + "spec0.data", 1025, syst.spectrumSystem(L));

	double s = si;
	double a = ai;
	double t = tofa(a, omegam0);
	double dt = 0;

	//PERFORM THE SIMULATION STEPS
	for (int b = 1; b <= timeSteps; b++)
	{
		s = si + (b * ((sf - si) / timeSteps));
		a = s * s;
		double nt = tofa(a, omegam0);
		dt = nt - t;
		double c = 2 * M_PI * (4.30035 * pow(10, -9)) * omegam0 * (2.77573 * pow(10, 11));
		c *= L / (Np * pow(a, 3));
		syst.acceleration(H0 * eofa(a, omegam0), c, L);
		syst.moove(dt, L);

		if (b % (timeSteps / snaps) == 0 && b != timeSteps)
		{
			//Save snapshot
			syst.getXbin(dataFile + "pos" + to_string(b) + ".data");
			// syst.getVbin(dataFile + "vel" + to_string(b) + ".data");
			// syst.getAbin(dataFile + "acc" + to_string(b) + ".data");
			write_binary(dataFile + "spec" + to_string(b) + ".data", 1025, syst.spectrumSystem(L));
		}
		t = nt;
	}
	//Save final conditions
	syst.getXbin(dataFile + "pos" + to_string(timeSteps) + ".data");
	// syst.getVbin(dataFile + "vel" + to_string(timeSteps) + ".data");
	// syst.getAbin(dataFile + "acc" + to_string(timeSteps) + ".data");
	write_binary(dataFile + "spec" + to_string(timeSteps) + ".data", 1025, syst.spectrumSystem(L));
}

int main()
{
	double t1Total = mm_systime();

	//PERFORM REALISATIONS
	thread tr[realisations];
	for(int i = 0; i < realisations; i++)
	{
		tr[i] = thread(realisation, i);
	}

	for(int i = 0; i < realisations; i++)
	{
		tr[i].join();
	}

	double s = si;
	double a = ai;
	double t = tofa(a, omegam0);
	double dt = 0;

	double aVals[snaps+1];
	double dVals[snaps+1];
	double tVals[snaps+1];
	int snapshot = 1;

	aVals[0] = a;
	dVals[0] = dofa(a, omegam0);
	tVals[0] = tofa(a, omegam0);

	// Save the values of a, D(a) and t(a)
	for (int b = 1; b <= timeSteps; b++)
	{
		s = si + (b * ((sf - si) / timeSteps));
		a = s * s;
		double nt = tofa(a, omegam0);
		dt = nt - t;

		if (b % (timeSteps / snaps) == 0 && b != timeSteps)
		{
			// Save a, D(a), t(a)
			aVals[snapshot] = a;
			dVals[snapshot] = dofa(a, omegam0);
			tVals[snapshot] = tofa(a, omegam0);
			snapshot++;
		}
		t = nt;
	}
	aVals[snapshot] = a;
	dVals[snapshot] = dofa(a, omegam0);
	tVals[snapshot] = tofa(a, omegam0);

	write_binary("aVals.data", snaps+1, aVals);
	write_binary("dVals.data", snaps+1, dVals);
	write_binary("tVals.data", snaps+1, tVals);

	double t2Total = mm_systime();
	cout << "TOTAL EXECUTION TIME: " << double(t2Total-t1Total)/1000. << " seconds" << endl;
	cout << "TIME PER REALISATION: " << double(t2Total-t1Total)/(1000 * realisations) << " seconds" << endl;
}