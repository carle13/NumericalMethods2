#include <iostream>
#include <string> 
#include <fstream>



int read_binary ( std::string file_name, long num, double vec[] ) 
{  
  const char * nameout = file_name.c_str();  
  //double vec [num] ;
  
  // std::ifstream inlezen;
  //inlezen.open(nameout , std::ios::in | std::ios::binary); //OPEN THE FILE
  //char byte[8]; //DEFINE THE CHARACTER ARRAY OF BYTE
  //bytes = vec.size() * sizeof(vec[0]) ;//GET THE NUMBER OF BYTES
  std::ifstream in( nameout , std::ios::in | std::ios::binary );
  //inlezen.read(reinterpret_cast<char*>(&vec[0]), bytes); //READ THE FILE
  in.read((char *) vec, num*sizeof(double) ) ;
  in.close(); //CLOSE THE FILE

return 1 ;
}
