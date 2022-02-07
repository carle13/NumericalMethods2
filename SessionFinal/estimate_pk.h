#include <cmath>
#include <iostream>
using namespace std;

double* estimateSpectrum(double* positions, int nParticles, double period)
{
    //Number of fourier coefficients
    int Nk = nParticles / 2. + 1.;
    //Array to be returned
    static double* spectrum = new double[Nk];
    
    //Fundamental frequency
    double kf = 2. * M_PI / period;
    //Calculating the Fourier series of the density contrast
    for(int b = 0; b < Nk; b++)
    {
        double kn = b * kf;
        double Pn = 1. / (nParticles * nParticles);
        double sumCos = 0.;
        for(int i = 0; i < nParticles; i++)
        {
            sumCos += cos(kn * positions[i]);
        }
        double sumSin = 0.;
        for (int i = 0; i < nParticles; i++)
        {
            sumSin += sin(kn * positions[i]);
        }
        Pn *= (sumCos * sumCos) + (sumSin * sumSin);
        spectrum[b] = Pn / kf;
    }
   return spectrum;
}