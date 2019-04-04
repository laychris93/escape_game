/********************************************************************* 
* ** Program Name: Escape Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Header file for Escape class, derived from Space
* ** class.  Class specific variable includes int for guard count.
* *********************************************************************/

#ifndef ESCAPE_HPP
#define ESCAPE_HPP

#include "Space.hpp"
using std::string;

class Escape : public Space
{
  private: 
  	int guard_num;
  public:
	Escape();
	virtual bool actions(Prisoner&, Space*&, bool&);
	virtual void fight_guard(Prisoner &player);
};

#endif
