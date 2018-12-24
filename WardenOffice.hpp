/********************************************************************* 
* ** Program Name: WardenOffice Class
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Header file for WardenOffice class, derived from Space
* ** class.  Class specific variables include bool for whether player
* ** has defeated the Warden and int for Warden's strength.
* *********************************************************************/

#ifndef WARDEN_OFFICE_HPP
#define WARDEN_OFFICE_HPP

#include "Space.hpp"
using std::string;

class WardenOffice : public Space
{
  private:
  	bool warden_defeated;
  	int warden_strength;

  public:
	WardenOffice();
	void fight(Prisoner&);
	virtual void fight_guard(Prisoner&);
	virtual bool actions(Prisoner&, Space*&, bool&);
};

#endif