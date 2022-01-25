#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

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
    //Save power spectrum into a file
    write_binary("powerSpectrumMeasured.data", 1025, powerMeasured);


    //Initialize arrays for average and error of the average
    double averageSpectrum[lenFile];
    double errorAverage[lenFile];
    for(int i = 0; i < lenFile; i++)
    {
        averageSpectrum[i] = 0.;
        errorAverage[i] = 0.;
    }
    //Read all 201 files
    for(int i = 0; i <= 200; i++)
    {
        //Get data from the file
        fileName = "PARTICLES/initial_positions_" + to_string(i) + ".data";
        lenFile = 2048;
        double measured[lenFile];
        read_binary(fileName, lenFile, measured);
        //Estimate power spectrum
        double *powerMeasured = estimateSpectrum(measured, lenFile, 1000);
        //Calculate sum and sum squared
        for(int b = 0; b < lenFile; b++)
        {
            averageSpectrum[b] += powerMeasured[b];
            errorAverage[b] += powerMeasured[b] * powerMeasured[b];
        } 
    }
    //Calculate average and error of the average
    for(int i = 0; i < lenFile; i++)
    {
        averageSpectrum[i] /= 201;
        errorAverage[i] = (errorAverage[i] / 201) - (averageSpectrum[i] * averageSpectrum[i]);
        errorAverage[i] = sqrt(errorAverage[i]);
    }
    //Save them into files
    write_binary("averageSpectrum.data", 1025, averageSpectrum);
    write_binary("errorSpectrum.data", 1025, errorAverage);
}