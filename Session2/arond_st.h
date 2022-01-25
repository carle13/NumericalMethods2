#include <iostream>
#include <string> 
#include <sstream>
#include <iomanip>

std::string arond_st (double x, int n)
{  
  std::string Result;          // string which will contain the result
  std::ostringstream convert;   // stream used for the conversion
  convert << std::fixed << std::setprecision(n) << x;      // insert the textual representation of 'Number' in the characters in the stream
   Result = convert.str(); // set 'Result' to the contents of the stream

return Result ;
}
