#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

double mean(double data[], int length)
{
    double sum = 0.;
    for(int i = 0; i < length; i++)
    {
        sum += data[i];
    }
    return sum / length;
}

double errorMean(double data[], int length)
{
    double sumSquared = 0.;
    for(int i = 0; i < length; i++)
    {
        sumSquared += pow(data[i], 2.);
    }
    double sigmaSquared = - pow(mean(data, length), 2.) + sumSquared/length;
    return sqrt(sigmaSquared / length);
}

int main()
{
    //Get data from the file
    string fileName = "PARTICLES/initial_pk_linear_theo.data";
    int lenFile = 2048;
    double theoretical[lenFile];
    read_binary(fileName, lenFile, theoretical);
    //The linear theoretical data is used so no rescaling is necessary
    /*
    Convert theoretical to 1D
    double theor1D[lenFile];
    for(int i = 0; i < lenFile; i++)
    {
        theor1D[i] = 4. * M_PI * pow(i, 2.) * theoretical[i];
    }
    //Rescaling to early time
    double theorTime[lenFile];
    for(int i = 0; i < lenFile; i++)
    {
        theorTime[i] = pow(dofa(a, om0), 2.) * theor1D[i];
    }
    */

    //Get data from the file for measured data
    
    fileName = "PARTICLES/initial_positions.data";
    lenFile = 2048;
    double measured[lenFile];
    read_binary(fileName, lenFile, measured);
    //Print the array
    for(int i = 0; i < 10; i++) cout << measured[i] << endl;
    //Estimate power spectrum
    double *powerMeasured = estimateSpectrum(measured, lenFile, 1000);
    for(int i = 0; i < 10; i++) cout << powerMeasured[i] << endl;
    write_binary("powerSpectrumMeasured.data", lenFile, powerMeasured);


    double averageSpectrum[lenFile];
    for(int i = 0; i < lenFile; i++)
    {
        averageSpectrum[i] = 0.;
    }
    //Read all files
    for(int i = 0; i <= 200; i++)
    {
        //Get data from the file
        fileName = "PARTICLES/initial_positions_" + to_string(i) + ".data";
        lenFile = 2048;
        double measured[lenFile];
        read_binary(fileName, lenFile, measured);
        //Estimate power spectrum
        double *powerMeasured = estimateSpectrum(measured, lenFile, 1000);
        for(int b = 0; b < lenFile; b++)
        {
            averageSpectrum[b] += powerMeasured[b];
        } 
    }
    for(int i = 0; i < lenFile; i++)
    {
        averageSpectrum[i] /= 201;
    }
    write_binary("averageSpectrum.data", lenFile, averageSpectrum);
}