#include "estimate_pk.h"
#include "read_binary.h"
#include "write_binary.h"
#include "particles.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //Create particles class object using empty constructor
    particles part = particles();
    //Check that the first position is zero
    cout << part.getXelem(0) << endl; //As expected, this prints "0"

    //Create particles class object using construct with size num
    particles part2 = particles(10);
    //Check that the last position is zero
    cout << part2.getXelem(9) << endl; //As expected, this prints "0"

    //Create particles class object reading data from file
    //Get data from the file
    string fileName = "PARTICLES/initial_pk_linear_theo.data";
    int lenFile = 2048;
    double theoretical[lenFile];
    read_binary(fileName, lenFile, theoretical);
    //use data in constructor
    particles part3 = particles(lenFile, theoretical);
    //Check that value at position 1000 is the same
    cout << "File: " << theoretical[1000] << " | Class: " << part3.getXelem(1000) << endl;
    //File: 0.0257753 | Class: 0.0257753    The values are the same

    //Creating particles with constructor using num
    particles part4 = particles(lenFile);
    //Set array using method
    part4.setX(theoretical);
    //Check that value at position 1000 is the same
    cout << "File: " << theoretical[1000] << " | Class: " << part4.getXelem(1000) << endl;
    //File: 0.0257753 | Class: 0.0257753     The values are the same

    //Save data into a file and reading it again to creat another particles object
    part4.saveXFile("dataTest.data");
    //Create new element
    particles part5 = particles(lenFile);
    part5.setXFile("dataTest.data");
    //Check that value at position 1000 is the same
    cout << "Part5: " << part5.getXelem(1000) << " | Part4: " << part4.getXelem(1000) << endl;
    //Part5: 0.0257753 | Part4: 0.0257753     The values are the same


    //Test of move and acceleration functions
    particles part6 = particles(3);
    double positions[] = {0, 0.5, 1};
    part6.setX(positions);
    //Perform 50 steps
    part6.calcAcc(1, 1.5, 0);
    for(int i = 0; i < 3; i++)
    {
        cout << part6.getXelem(i) << endl;
        cout << part6.getVelem(i) << endl;
        cout << part6.getAelem(i) << endl << endl;
    }
    /*As expected with equidistant particles, the acceleration is almost zero, and
    completely negligible at the scale of the distances of the particles
    */
    for(int i = 0; i < 10; i++)
    {
        part6.calcAcc(1, 1000, i * 0.5);
        part6.move(0.001, 1000);
        cout << part6.getXelem(1) << endl;
        cout << part6.getVelem(1) << endl;
        cout << part6.getAelem(1) << endl << endl;
    }
    /*
    After moving the particles through 10 steps, they are still at the same position,
    as the acceleration is very small
    */
}