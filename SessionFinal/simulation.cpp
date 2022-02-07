#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include "particles.h"
#include <string>
#include <iostream>
#include <fstream>
#include <random>
// #include "ic_generator_bis.h"

using namespace std;

int main()
{
	//Simulation parameters:
	int Np = 500;  //Number of particles
	int timeSteps = 1000;  //Number of timesteps
	int realisations = 100;  //Number of realisations to be performed
	string dataFile = "Data/simulation";  //Name of the files containing the data of the simulation
	int snaps = 50;  //Number of snapshots to be saved
	bool randPos = true;  //Bool to specify if positions should be randomized

	double zi = 0.5;  //Initial redshift
	double zo = 1.3;  //Final redshift
	double a = 1 / (1 + zi);  //Scaling factor as a function of redshift

	//Get a true random number
	random_device seed;

	//Initialize the random generator
	default_random_engine generator(seed());

	//Define a distribution
	uniform_real_distribution<double> distribution(0.0, 1.0);

	//Define the random variable
	double epsilon;

	int nk = 200; //Number of random values obtained

	for (int n = 0; n < nk; n++)
	{
		//Call a random number following the required distribution
		epsilon = distribution(generator);

		//Get random distributions
	}
}