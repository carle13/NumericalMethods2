#ifndef OMOFA
#define OMOFA

#include <bits/stdc++.h>
#include <math.h> 
using namespace std;

double omofa(double a, double H0, double omegam0, double omegalambda0)
{
    double om;
    om = omegam0 / (omegam0 + omegalambda0 * pow(a, 3.));
    return om;
}

#endif /* OMOFA */