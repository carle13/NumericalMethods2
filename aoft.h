#ifndef AOFT
#define AOFT

#include <bits/stdc++.h>
#include <math.h> 
using namespace std;

double aoft(double t, double H0, double omegam0)
{
    double a;
    a = 0.5 * omegam0 / (1 - omegam0);
    a *= cosh(3 * H0 * t * sqrt(1 - omegam0)) - 1;
    a = pow(a, 1./3.);
    return a;
}

#endif /* AOFT */