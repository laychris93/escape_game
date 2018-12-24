/********************************************************************* 
* ** Program Name: Armory Class
* ** Author: Chris Lay
* ** Date: 12/24/2018 
* ** Description: Header file for Armory class, derived from Space
* ** class.  Class specific variables include whether player obtains
* ** shotgun available in Armory.
* *********************************************************************/ 

#ifndef ARMORY_HPP
#define ARMORY_HPP

#include "Space.hpp"
using std::string;

class Armory : public Space
{
  private:
  	bool shotgun_obtained;

  public:
	Armory();
	virtual bool actions(Prisoner&, Space*&, bool&);
};

#endif