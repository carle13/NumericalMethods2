#include <cmath>

double* estimateSpectrum(double* positions, int nParticles, double period)
{
    //Array to be return
    static double* spectrum = new double[nParticles];
    //Number of fourier coefficients
    int Nk = nParticles / 2. + 1.;
    //Sampling frequency
    double kf = 2. * M_PI / period;
    //Calculating the Fourier series of the density contrast
    for(int b = 0; b < Nk; b++)
    {
        double kn = b * kf;
        double Pn = 1. / pow(nParticles, 2.);
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
        Pn *= pow(sumCos, 2.) + pow(sumSin, 2.);
        spectrum[b] = Pn / kf;
    }
   return spectrum;
}