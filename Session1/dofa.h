#include <bits/stdc++.h>
#include <math.h> 
#include "fofa.h"
#include "eofa.h"
using namespace std;

double dofa(double a, double H0, double omegam0)
{
    double d;
    d = fofa(1., H0, omegam0) + 1.5 * omegam0;
    d /= pow(a, 2.) * pow(eofa(a, H0, omegam0), 2.) * (fofa(a, H0, omegam0) + 1.5 * omofa(a, H0, omegam0));
    return d;
}