#ifndef FOFA
#define FOFA

#include <bits/stdc++.h>
#include <math.h>
#include "omofa.h"
using namespace std;

double fofa(double a, double H0, double omegam0, double omegalambda0)
{
    double f;
    double alpha = (6/11) - (15/2057)*log(omofa(a, H0, omegam0, omegalambda0)) + (205/540421)*pow(log(omofa(a, H0, omegam0, omegalambda0)), 2.);
    f = pow(omofa(a, H0, omegam0, omegalambda0), alpha);
    return f;
}

#endif /* FOFA */