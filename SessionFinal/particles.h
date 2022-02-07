#ifndef PARTIC
#define PARTIC

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iostream>

class particles
{
    private:
    //What is here is private
    long num;   //Number of particles
    double *x;  //Pointer to a double array containing the positions
    double *v;  //Pointer to a double array containing the velocities
    double *a;  //Pointer to a double array containing the accelerations
    double Sg(double x) //Private implementation of the Sg function just to use in this class
    {
        if (x > 0) return 1;
        if (x < 0) return -1;
        return 0;
    }

    public:
    //What is here is public and can be accessed from anywhere

    //Class constructor without parameters
    particles()
    {
        num = 1;
        x = new double[num];
        v = new double[num];
        a = new double[num];
    }

    //Class constructor for only one argument
    particles(long num0)
    {
        num = num0;
        x = new double[num];
        v = new double[num];
        a = new double[num];

        //Initialize the vectors to zero
        std::memset(x, 0, num*sizeof(double));
        std::memset(v, 0, num*sizeof(double));
        std::memset(a, 0, num*sizeof(double));
    }

    //Class constructor for when two arguments are given
    particles(long num0, double *xp)
    {
        num = num0;
        x = new double[num];
        v = new double[num];
        a = new double[num];

        //Copy data from the array given as argument
        for(int i = 0; i < num; i++)
        {
            x[i] = xp[i];
        }
        std::memset(v, 0, num*sizeof(double));
        std::memset(a, 0, num*sizeof(double));
    }

    //Class constructor used when positions and velocities are set
    particles(long num0, double *xp, double *vp)
    {
        num = num0;
        x = new double[num];
        v = new double[num];
        a = new double[num];

        //Copy data from the array given as argument
        for(int i = 0; i < num; i++)
        {
            x[i] = xp[i];
            v[i] = vp[i];
        }
        std::memset(a, 0, num*sizeof(double));
    }

    //Class destructor
    ~particles() {}

    //Setter methods
    //Provide a way of setting positions from the definition of an array
    void setX(double *xp)
    {
        for(int i = 0; i < num; i++)
        {
            x[i] = xp[i];
        }
    }

    void setV(double *vp)
    {
        for(int i = 0; i < num; i++)
        {
            v[i] = vp[i];
        }
    }

    void setA(double *ap)
    {
        for(int i = 0; i < num; i++)
        {
            a[i] = ap[i];
        }
    }

    //Getter methods
    //Get a particular value
    double getXelem(int i) {return x[i];}
    double getVelem(int i) {return v[i];}
    double getAelem(int i) {return a[i];}

    //Read array values from a binary file
    void setXFile(std::string filename)
    {
        const char* nameoutb = filename.c_str();
        std::ifstream in(nameoutb, std::ios::in | std::ios::binary);
        in.read((char *) x, num*sizeof(double));
        in.close(); //Close the file
    }

    void setVFile(std::string filename)
    {
        const char* nameoutb = filename.c_str();
        std::ifstream in(nameoutb, std::ios::in | std::ios::binary);
        in.read((char *) v, num*sizeof(double));
        in.close(); //Close the file
    }

    //Save array values into a binary file
    void saveXFile(std::string filename)
    {
        //Write a binary file
        const char* nameout = filename.c_str();
        std::ofstream out(nameout, std::ios::out | std::ios::binary);
        out.write((char *) x, num*sizeof(int));
        out.close();
    }

    void saveVFile(std::string filename)
    {
        //Write a binary file
        const char* nameout = filename.c_str();
        std::ofstream out(nameout, std::ios::out | std::ios::binary);
        out.write((char *) v, num*sizeof(int));
        out.close();
    }

    //Move the particles
    void move(double dt, double L)
    {
        for(int i = 0; i < num; i++)
        {
            v[i] += dt * a[i];
            x[i] += v[i];
            /*
            if(x[i] >= L)
            {
                x[i] -= L;
            }
            else if(x[i] < 0)
            {
                x[i] += L;
            }
            */
            x[i] += - (x[i] >= L) * L + (x[i] <  0) * L;
        }
    }

    void calcAcc(double co, double L, double H)
    {
        for(int i = 0; i < num; i++)
        {
            double gField = 0;
            for(int b = 0; b < num; b++)
            {
                double diff = x[b] - x[i];
                diff += - (diff >= L/2) * L + (diff < 0) * L;
                gField += Sg(diff) - 2 * (diff / L);
            }
            gField *= co;
            a[i] = gField - 2 * H * v[i];
        }
    }
};

#endif //PARTIC