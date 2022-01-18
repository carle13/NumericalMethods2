#include<string>
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;

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

    
}
