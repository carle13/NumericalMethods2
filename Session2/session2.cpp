#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include "dofa.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //Get data from the file
    string fileName = "PARTICLES/final_pk_zeldovitch.data";
    int lenFile = 100;
    double theoretical[lenFile];
    read_binary(fileName, lenFile, theoretical);

    //Print the array
    for(int i = 0; i < lenFile; i++) cout << theoretical[i] << endl;

    //Convert theoretical to 1D
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

    //Get data from the file
    fileName = "PARTICLES/initial_positions_1.data";
    lenFile = 100;
    double measured[lenFile];
    read_binary(fileName, lenFile, measured);
    cout << endl << endl;
    //Print the array
    for(int i = 0; i < lenFile; i++) cout << measured[i] << endl;
    //Estimate power spectrum
    double *powerMeasured = estimateSpectrum(measured, lenFile, 2.);
}