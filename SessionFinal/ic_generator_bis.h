#include <random>
#include <stdlib.h>
#include <time.h> 

using namespace std ;

void ic_generator_bis (int num, double lbox, double hf, int flag, double * pk, double * positions, double * velocities) 
{ 

  // num: Number of particles
  // lbox: size of the box
  // hf: product of the expansion rate H and the growth rate f at the initial time or scale factor or redshift
  // flag: if this value is 0 then both phases and amplitudes are randomized (Gaussian field), if set to any other value then only the phases are random but the amplitude are set exactly to the expected ones.
  // pk: pointer to the first memory element of the table ontaining the expected power spectrum
  // positions: pointer to the first element of the table which will contain the particles positions
  // velocities: pointer to the first element of the table which will contain the particles velocities

  //DEFINE SOME TABLES
  int numk = num/2 + 1 ;
  double pi = 3.1415927 ;
  double kf = 2.*pi/lbox ;
  double s = lbox/num ;
  double psi, qj, qjkf ; 
  double en[numk], an[numk] ;
  
  //INITIALIZE RANDOMS:
  //int t1 = mm_systime() ;
  //random_device r1, r2;
  //default_random_engine generator1(r1()), generator2(r2());
  //uniform_real_distribution<double> distribution1(0., 1.);
  //uniform_real_distribution<double> distribution2(0., 1.);
  //normal_distribution<double> distribution2(0.,sigmav/10.);
srand (time(NULL));


  //GENERATE THE RANDOM PHASES
  for (int n=1 ; n < numk ; n++) 
    en[n] =  2.*pi*double(rand())/double(RAND_MAX) ;
  //distribution1.reset();


  //PUT AT ZERO FIRST ELEMENT
  en[0] = 0 ;
  an[0] = 0 ;
  //cout << flag << endl ;


//CHECK IF ONLY RANDOM PHASES IS REQUIRED:
switch (flag)
   {
   case 1:
   for (int n=1 ; n < numk ; n++) 
        an[n] =  sqrt( *(pk+n)/kf ) / double(n) ;   
   break;
   default :
   srand (time(NULL));
   for (int n=1 ; n < numk ; n++) 
     an[n] =  sqrt( - *(pk+n)/kf*log( 1 - rand()/RAND_MAX ) ) / double(n) ;   
   }

//distribution2.reset();


//COMPUTE THE DISPLACEMENT:
for (int j=0 ; j < num ; j++) 
    { 
      qj = *(positions+j);
      qjkf = qj*kf ;
      psi = 0;

      for (int n=1 ; n < numk ; n++) 
        {
	  psi+= an[n] * sin( en[n] + qjkf*double(n) ) ;
        }

      *(positions+j)-= 2.*psi ;
      *(velocities+j)= - 2.*psi*hf ;
    } 

 
}
