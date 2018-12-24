/********************************************************************* 
* ** Program Name: Hospital Class
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Header file for Hospital class, derived from Space
* ** class.  Class specific variables include bool for whether player
* ** has obtained medicine available in the Hospital.
* *********************************************************************/

#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include "Space.hpp"
using std::string;

class Hospital : public Space
{
  private:
  	bool medicine_obtained;

  public:
	Hospital();
	virtual bool actions(Prisoner&, Space*&, bool&);
};

#endif