/********************************************************************* 
 * ** Program Name: Utilities class
 * ** Author: Jeremy Lay
 * ** Date: 12/24/2018  
 * ** Description: Header file for Utilities class.              
 * *********************************************************************/ 

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <limits>
using std::string;
using std::ifstream;

class Utilities
{
  public:
    void validate_int(int&, int = -2147483647, int = 2147483646);
    void validate_double(double&, double = -1.79769e+308, double = 1.79769e+308);
    void validate_string(string&, unsigned = 0);
    double f_rand(double, double);
    void enter_to_continue();
    void clear_screen();
};

#endif
