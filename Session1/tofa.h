#ifndef TOFA
#define TOFA

#include <bits/stdc++.h>
#include <math.h> 
using namespace std;

double tofa(double a, double H0, double omegam0)
{
    double t;
    t = 2 / (3 * H0 * sqrt(1 - omegam0));
    t *= log((sqrt(omegam0 + (1 - omegam0) * pow(a, 3.)) + sqrt((1 - omegam0) * pow(a, 3.))) / sqrt(omegam0));
    return t;
}

#endif /* TOFA */