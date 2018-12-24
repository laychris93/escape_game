/********************************************************************* 
* ** Program Name: Hall Class
* ** Author: Chris Lay
* ** Date: 12/24/2018 
* ** Description: Header file for Hall class, derived from Space
* ** class.  Class specific variables include bool for whether player
* ** has fought a guard on a particular visit to the Space.
* *********************************************************************/

#ifndef HALL_HPP
#define HALL_HPP

#include "Space.hpp"
using std::string;

class Hall : public Space
{
 private:
  	bool beat_a_guard;
  
  public:
  	Hall();
  	virtual bool actions(Prisoner&, Space*&, bool&);
};


#endif