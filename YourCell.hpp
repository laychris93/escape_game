/********************************************************************* 
* ** Program Name: YourCell Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Header file for YourCell class, derived from Space
* ** class.  Class specific variables include bool for whether player
* ** has finished a shank and for whether a guard has been defeated, and 
* ** an int for how much time the player has spent working on the shank.
* *********************************************************************/

#ifndef YOUR_CELL_HPP
#define YOUR_CELL_HPP

#include "Space.hpp"
using std::string;

class YourCell : public Space
{
  private:
  	bool shank, guard_defeated;
  	int shank_hours;

  public:
	YourCell();
	void fight(Prisoner&);
	void shank_work(Prisoner&);
	void sleep(Prisoner&);
	virtual bool actions(Prisoner&, Space*&, bool&);
};

#endif
