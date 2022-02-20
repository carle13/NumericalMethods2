#include <iostream>
#include <string> 
#include <fstream>

int write_binary ( std::string file_name, long num, double vec [] ) 
{  
  const char * nameout = file_name.c_str();  

  //std::ofstream bestand;  //Don't know but important out ftsream
  //size_t bytes = vec.size() * sizeof(vec[0]); //TOTAL BYTES OF THE VECTOR
  //const char* pointer = reinterpret_cast<const char*>(&vec[0]); //Create a const string variable 
  std::ofstream out(nameout, std::ios::out | std::ios::binary); //Open THE FILE
  //char byte[8]; //DEFINE THE CHARACTER ARRAY OF BYTE

  //bytes = vec.size() * sizeof(vec[0]) ;//GET THE NUMBER OF BYTES
  out.write((char *) vec, num*sizeof(double)); //WRITE INTO THE FILE
  out.close(); //CLOSE THE FILE

return -1 ;
}
