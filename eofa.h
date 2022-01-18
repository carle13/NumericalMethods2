#ifndef EOFA
#define EOFA

#include <bits/stdc++.h>
#include <math.h> 
using namespace std;

double eofa(double a, double H0, double omegam0, double omegalambda0)
{
    double e;
    e = omegam0 * pow(a, -3.) + omegalambda0;
    e = pow(e, 1./2.);
    return e;
}

#endif /* EOFA */