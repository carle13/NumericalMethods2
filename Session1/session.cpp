#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include <stdlib.h> 
#include <string>

#include "mm_systime.h"

#include <sstream>
#include <iomanip>

using namespace std;

std::string arond_st (double x, int n)
{
    std::string Result;  //String which will contain the result
    std::ostringstream convert; //Stream used for the conversion
    convert << std::fixed << std::setprecision(n) << x;  //Insert the textual representation
    Result = convert.str();  //Set 'Result' to the contents of the stream
    return Result;
}

int main(int argc, char *argv[])
{
    //Tell the user the number of arguments
    cout << "There are " << argc << " arguments" << endl;

    //Loop over the arguments
    for(int narg = 0; narg < argc; narg++)
    {
        //Print every element of the array
        cout << narg << " " << argv[narg] << endl;
    }

    //Define two integers and a string
    int num, nstep;
    string ref;

    //Check the number of arguments and assign values to the missing ones
    switch(argc)
    {
        case 2:
            //This will run if one parameter is given and it will assign variable num that value
            num = atof(argv[1]);
            nstep = 1000;
            ref = "";
            break;
        case 3:
            //This will run if 2 parameters are given, and will assign them to num and nstep
            num = atof(argv[1]);
            nstep = atof(argv[2]);
            ref = "";
            break;
        case 4:
            //This will run if 3 parameters are given, and will assign them to num, nstep and ref respectively
            num = atof(argv[1]);
            nstep = atof(argv[2]);
            ref = argv[3];
            break;
        default:
            //This code will run when no parameter is given, or more than 3 parameters are given
            num = 512;
            nstep = 1000;
            ref = "";
    }

    double grid_size, lbox;

    lbox = 1000.;  //h-1Mpc

    grid_size = lbox / num; //Implicit conversion type

    cout << "The box size is: " << lbox << "h-1Mpc" << endl;  //Prints The box size is: 1000h-1Mpc
    cout << "The grid size is: " << grid_size << "h-1Mpc" << endl;  //The grid size is: 1.95312h-1Mpc

    cout << "Number of particles: " << endl;
    cout << num << endl;  //Prints 512 or the number given by the user
    cout << " " << endl;
    cout << "ref: " + ref << endl;  //Prints ref: or ref: + the text given by the user
    cout << nstep << endl;  //Prints 1000 or the value given by the user
    cout << " " << endl;

    //Print the size of integer and double
    cout << "size of an integer: " << sizeof(int) << endl;  //Prints the number of bytes used by an integer variable
    cout << "size of a double: " << sizeof(double) << endl;  //Prints the number of bytes used by a double variable

    //Example of output running the code using "./session 315 123 asdf"
    //It counts the arguments and prints all of them
    //Then it prints the box size and grid size
    //This sets the value of the variables num = 315, nstep = 123, ref = "asdf"
    //Then it prints the size of integer and double variables
        //There are 4 arguments
        //0 ./a.out
        //1 315
        //2 123
        //3 asdf
        //The box size is: 1000h-1Mpc
        //The grid size is: 3.1746h-1Mpc
        //Number of particles: 
        //315
        // 
        //ref: asdf
        //123
        // 
        //size of an integer: 4
        //size of a double: 8


    //Working with arrays
    int numbers[10];
    numbers[0] = 1;
    numbers[1] = 5;
    numbers[5] = 28;
    numbers[8] = 8.2;

    //Loop through the elements and print them
    for(int i = 0; i < sizeof(numbers) / 4; i++)
    {
        cout << i << ": " << numbers[i] <<endl;
    }

    //The output of printing the arrays is:
    //The values at position 0, 1 and 5, are printed as given
    //The value at position 8 is rounded to 8, as it is converted to integer type
    //The values at positions 2, 3, 4, 6, 7 and 9, are unexpected values, as the variables in that position were not initialized
        //0: 1
        //1: 5
        //2: 5
        //3: 0
        //4: 979789170
        //5: 28
        //6: 0
        //7: 0
        //8: 8
        //9: 22042

    //Use of different declaration method
    int numbers2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int i = 0; i < sizeof(numbers2) / 4; i++)
    {
        cout << numbers2[i] << ", ";
    }
    cout << endl;
    
    //Now, the output of printing the array is:
    //All the values are printed as given
        //1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 

    //Saving a file
    string filename;
    //Write an ASCII file
    ofstream myfile;
    filename = ref + ".txt";
    myfile.open(filename.c_str());
    for(int i = 0; i < 10; i++) myfile << numbers2[i] << endl;
    myfile.close();
    //A file is produced, with the text saved in ref + .txt
    //The file contains the values 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10



    cout << endl << "Reading a txt file" << endl;
    //Reading data from the file
    //Clear the array
    memset(numbers, 0, 10*sizeof(int));
    //Print the array
    //This prints an array full of 0, as the data contained in them was deleted
    for(int i = 0; i < 10; i++) cout << numbers[i] << endl;
    
    //Read an ASCII file
    string line;
    ifstream myfile_read (filename.c_str());
    for(int i = 0; i < 10; i++)
    {
        //Read each line of the file and store it in the array
        getline(myfile_read, line);
        numbers[i] = atof(line.c_str());
    }
    myfile_read.close();

    //Print the array
    //Now, the array contains the data from the file
    //It prints 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    for(int i = 0; i < 10; i++) cout << numbers[i] << endl;



    cout << endl << "Saving into a binary file" << endl;
    //Doing the same with a binary file
    //Write a binary file
    filename = ref + ".data";
    const char* nameout = filename.c_str();
    ofstream out(nameout, std::ios::out | std::ios::binary);
    out.write((char *) numbers, 10*sizeof(int));
    out.close();

    //Clear the array
    memset(numbers, 0, 10*sizeof(int));
    //Print the array
    //This prints an array full of 0, as the data contained in them was deleted
    for(int i = 0; i < 10; i++) cout << numbers[i] << endl;

    //Read the binary file
    const char* nameoutb = filename.c_str();
    ifstream in(nameoutb, std::ios::in | std::ios::binary);
    in.read((char *) numbers, 10*sizeof(int));
    in.close(); //Close the file

    //Print the array
    //Now, the array contains the data from the file
    //It prints 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    for(int i = 0; i < 10; i++) cout << numbers[i] << endl;
    //The binary file looks nothing like the data, depending on the text editor it shows random characters
    //This is because the computer is trying to read the data as characters, when it is pure binary numbers
    //One might want to use the binary format for its efficiency, as well as the privacy added to not being able to directly see the data



    cout << endl << "Time execution of saving methods" << endl;
    //We are going to measure the execution time of the saving methods by saving with different number elements, multiples of num
    //Initialize random seed
    srand(time(NULL));

    int n = 50;

    //Test 10 different array sizes
    for(int i = 11; i <= 20; i++)
    {
        //Create array to be saved
        double arrSave[num*i];
        //Give array random values
        for(int b = 0; b < num*i; b++)
        {
            arrSave[b] = rand() % num*i + 1;
        }

        cout << endl << "Execution times for size " << num*i << endl;

        //Measure time of text data
        //Average over n iterations
        int t1 = mm_systime();  //Calling the function returns the time in milliseconds
        for(int s = 0; s < n; s++)
        {
            //Code which time is to be measured
            //Saving a file
            string filename;
            //Write an ASCII file
            ofstream myfile;
            filename = ref + to_string(num*i) + "text.txt";
            myfile.open(filename.c_str());
            for(int h = 0; h < num*i; h++) myfile << arrSave[h] << endl;
            myfile.close();
        }
        int t2 = mm_systime(); //Get time in milliseconds
        //Print measured time per iteration
        cout << "Execution time (text file): " << (double(t2 - t1) / 1000.) / n << " seconds" << endl;

        //Measure time of binary data
        //Average over n iterations
        t1 = mm_systime();  //Calling the function returns the time in milliseconds
        for(int s = 0; s < n; s++)
        {
            //Write a binary file
            filename = ref + to_string(num*i) + "binary.data";
            const char* nameout = filename.c_str();
            ofstream out(nameout, std::ios::out | std::ios::binary);
            out.write((char *) arrSave, (i*num)*sizeof(int));
            out.close();
        }
        t2 = mm_systime(); //Get time in milliseconds
        //Print measured time per iteration
        cout << "Execution time (binary file): " << (double(t2 - t1) / 1000.) / n << " seconds" << endl;
    }

    //The resulting times are as follows:
        // Time execution of saving methods

        // Execution times for size 3465
        // Execution time (text file): 0.03552 seconds
        // Execution time (binary file): 0.00092 seconds

        // Execution times for size 3780
        // Execution time (text file): 0.03758 seconds
        // Execution time (binary file): 0.00084 seconds

        // Execution times for size 4095
        // Execution time (text file): 0.0431 seconds
        // Execution time (binary file): 0.00086 seconds

        // Execution times for size 4410
        // Execution time (text file): 0.04286 seconds
        // Execution time (binary file): 0.0009 seconds

        // Execution times for size 4725
        // Execution time (text file): 0.0449 seconds
        // Execution time (binary file): 0.0009 seconds

        // Execution times for size 5040
        // Execution time (text file): 0.0497 seconds
        // Execution time (binary file): 0.00084 seconds

        // Execution times for size 5355
        // Execution time (text file): 0.05472 seconds
        // Execution time (binary file): 0.0009 seconds

        // Execution times for size 5670
        // Execution time (text file): 0.05978 seconds
        // Execution time (binary file): 0.001 seconds

        // Execution times for size 5985
        // Execution time (text file): 0.06236 seconds
        // Execution time (binary file): 0.00164 seconds

        // Execution times for size 6300
        // Execution time (text file): 0.06116 seconds
        // Execution time (binary file): 0.00102 seconds

    //It can be seen that saving in the binary file is much more efficient
    //For the sizes of the array chosen, the binary file was around two order of magnitude faster

    //In terms of storage size we analyzed the largest files, with size of 6300
    //The text file has a size of 32 KB
    //The binary file has a size of 28 KB



    //Using the arond_st() function
    double test = 234.2542509;
    cout << test << endl;  //Prints 234.254
    cout << arond_st(test, 2) << endl;  //Prints 234.25
    cout << arond_st(test, 4) << endl;  //Prints 234.2543
    cout << arond_st(test, 6) << endl;  //Prints 234.254251
    cout << arond_st(test, 8) << endl;  //Prints 234.25425090
    cout << arond_st(test, 10) << endl;  //Prints 234.2542509000
    //As it can be seen, the function allows us to set the number of decimal numbers that we want to be represented in the string
}