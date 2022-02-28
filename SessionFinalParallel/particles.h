#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include "estimate_pk.h"

class particles {

friend void cross_acceleration(  particles &p1, particles &p2); 

  public:

 long num ;
 double * x ;
 double * v ;
 double * a ; 

  particles() { num=1; x[0]=0 ; v[0]=0; a[0]=0; } 

  //IF ONLY ONE ARGUMENT
  particles(long numo) 
  { 
  num = numo;  
  x = new double [num] ;
  v = new double [num] ;
  a = new double [num] ; 
  std::memset(x, 0, num*sizeof(double));  
  std::memset(v, 0, num*sizeof(double)); 
  std::memset(a, 0, num*sizeof(double)); 
  } 

  //IF ONLY TWO ARGUMENTS
  particles(long numo, double * xp) 
{
  num = numo; 
  x = new double [num] ;
  v = new double [num] ;
  a = new double [num] ; 
  for (int i=0; i<num;i++) 
   { 
     x[i]=*(xp++) ; 
   } 
std::memset(v, 0, num*sizeof(double)); 
std::memset(a, 0, num*sizeof(double)); 
}

 //IF ONLY THREE ARGUMENTS
  particles(long numo, double * xp, double * vp) 
{
  num = numo; 
  x = new double [num] ;
  v = new double [num] ;
  a = new double [num] ; 
  for (int i=0; i<num;i++) 
   { 
     x[i]=*(xp++) ;
     v[i]=*(vp++) ; 
   } 

std::memset(a, 0, num*sizeof(double)); 
}

 //IF ONLY FOUR ARGUMENTS
  particles(long numo, double * xp, double * vp, double * ap) 
{
  num = numo; 
  x = new double [num] ;
  v = new double [num] ;
  a = new double [num] ; 
  for (int i=0; i<num;i++) 
   { 
     x[i]=*(xp++) ; 
     v[i]=*(vp++) ;
     a[i]=*(ap++) ;
   } 
}


  ~particles() { }
//      il s'agissait de prototypes de fonctions, d'où le point-virgule 

//      les fonctions écrites complètement dans la déclaration de la classe sont inline par défaut

//PROVIDE A WAY OF SETTING POSITIONS FROM THE DEFINITION OF AN ARRAY:
  void setX(double * xp) { for (int i=0; i<num;i++) { x[i]=*(xp++) ; }  } 
  void setV(double * vp) { for (int i=0; i<num;i++) { v[i]=*(vp++) ; }  } 
  void setA(double * ap) { for (int i=0; i<num;i++) { a[i]=*(ap++) ; }  }

  //GET A PARTICULAR VALUE
  double getXelem(int i) { return x[i]; }
  double getVelem(int i) { return v[i]; }
  double getAelem(int i) { return a[i]; }

//PROVIDE A WAY OF READING AN EXTERNAL BINARY FILE:
void setXbin(std::string file_name) 
{   
  const char * nameout = file_name.c_str();  
  std::ifstream in( nameout , std::ios::in | std::ios::binary );
  in.read((char *) x, num*sizeof(double) ) ;
  in.close(); //CLOSE THE FILE
} 

void setVbin(std::string file_name) 
{   
  const char * nameout = file_name.c_str();  
  std::ifstream in( nameout , std::ios::in | std::ios::binary );
  in.read((char *) v, num*sizeof(double) ) ;
  in.close(); //CLOSE THE FILE
} 

void setAbin(std::string file_name) 
{   
  const char * nameout = file_name.c_str();  
  std::ifstream in( nameout , std::ios::in | std::ios::binary );
  in.read((char *) a, num*sizeof(double) ) ;
  in.close(); //CLOSE THE FILE
} 

//OUTPUT INTO A BINARY FILE:
void getXbin(std::string file_name) 
{   
  const char * nameout = file_name.c_str();  
  std::ofstream out(nameout, std::ios::out | std::ios::binary); //Open THE FILE
  out.write((char *) x, num*sizeof(double)); //WRITE INTO THE FILE
  out.close(); //CLOSE THE FILE
}

void getVbin(std::string file_name) 
{   
  const char * nameout = file_name.c_str();  
  std::ofstream out(nameout, std::ios::out | std::ios::binary); //Open THE FILE
  out.write((char *) v, num*sizeof(double)); //WRITE INTO THE FILE
  out.close(); //CLOSE THE FILE
}

void getAbin(std::string file_name) 
{   
  const char * nameout = file_name.c_str();  
  std::ofstream out(nameout, std::ios::out | std::ios::binary); //Open THE FILE
  out.write((char *) a, num*sizeof(double)); //WRITE INTO THE FILE
  out.close(); //CLOSE THE FILE
}

//METHOD TO MOOVE THE PARTICLES:
void moove (double dt, double lbox)
{
  double abs_pos ;
  for (int i=0; i<num;i++) 
   { 
     abs_pos = x[i] + v[i]*dt ;
     x[i] =  abs_pos + double(abs_pos < 0)*lbox - double( abs_pos > lbox )*lbox  ;
     v[i]+= a[i]*dt ;
   } 
}

//METHOD TO COMPUTE THE ACCELERATION:
void acceleration ( double hi, double coef, double lbox ) 
{ 
  double xi, dij, somme ; //, gamg, game;
  double lboxsur2 = lbox/2. ;
  double hi2 = 2.*hi ;
  
for (int i=0; i<num;i++)
   {
   xi = x[i] ;
   somme = 0.;
   for (int j=0; j<num;j++)
     {
       if (j != i) 
	 {
	   //xj = x[j]  ;
       dij = x[j]-xi ;
       dij = dij - double(dij > lboxsur2)*lbox + double(dij < -lboxsur2)*lbox ;
       somme +=  1.-2.*double(signbit(dij)) - dij/lboxsur2 ;
       
	 }
     }
   a[i] = coef*somme - hi2*v[i] ;
   }

}

//METHOD TO COMPUTE THE POTENTIALS:
void potentials ( double coef, double lbox, double * phipec, double * phiback ) 
{ 
  double xi, dij, sommep, sommeb ; //, gamg, game;
  double lboxsur2 = lbox/2. ;
  //double hi2 = 2.*hi ;
  
for (int i=0; i<num;i++)
   {
   xi = x[i] ;
   sommep = 0.;
   sommeb = 0.;
   for (int j=0; j<num;j++)
     {
       if (j != i) 
	 {
	   //xj = x[j]  ;
       dij = x[j]-xi ;
       dij = dij - double(dij > lboxsur2)*lbox + double(dij < -lboxsur2)*lbox ;
       sommep +=  abs(dij) ; //- dij/lboxsur2 ;
       sommeb += dij*dij ;
	 }
     }
   phipec[i] = coef*sommep ;
   phiback[i] = -coef*sommeb/lbox ;
   }

}

//Method to compute the power spectrum
double* spectrumSystem(double L)
{
	return estimateSpectrum(x, num, L);
}

//METHOD TO MOOVE THE PARTICLES:
void working (double dt, double coefw, double * work)
{
  for (int i=0; i<num;i++) work[i] += coefw*v[i]*v[i]*dt ;
}

void gworking (double dt, double coefg, double hi, double * workg)
{
  double h2 = hi*2. ;
  for (int i=0; i<num;i++) workg[i] += coefg*(a[i] + h2*v[i])*v[i]*dt ;
}


//         on pourrait continuer avec 

//         suivi des choses qu'on veut déclarer privées à cet endroit

}  ;


inline void cross_acceleration(particles &p1, particles &p2, double coef, double lbox )
{ 
  double xi, dij, somme ; //, gamg, game;
  double lboxsur2 = lbox/2. ;
  double num1 = p1.num ;
  double num2 = p2.num ;

for (int i=0; i<num1;i++)
   {
   xi = p1.x[i] ;
   somme = 0.;
   for (int j=0; j<num2;j++)
     {
	   //xj = x[j]  ;
       dij = p2.x[j]-xi ;
       dij = dij - double(dij > lboxsur2)*lbox + double(dij < -lboxsur2)*lbox ;
       somme +=  1.-2.*double(signbit(dij)) - dij/lboxsur2 ;
     }
   p1.a[i] += coef*somme ;
   }

}

