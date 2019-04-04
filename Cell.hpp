/********************************************************************* 
* ** Program Name: Cell Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Header file for Cell class, derived from Space
* ** class.  Class specific variables include whether player frees
* ** other prisoners.
* *********************************************************************/ 

#ifndef CELL_HPP
#define CELL_HPP

#include "Space.hpp"
using std::string;

class Cell : public Space
{
  private:
  	bool prisoners_freed;

  public:
	Cell();
	virtual bool actions(Prisoner&, Space*&, bool&);
};

#endif
