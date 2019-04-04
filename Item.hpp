/********************************************************************* 
* ** Program Name: Item struct
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Header file for Item struct.  Struct holds string for
* ** Item name, int for Item's attack power, and bools representing Item
* ** potential functions
* *********************************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using std::string;

struct Item
{
  	string name;
  	int attack_power;
  	bool open_guard_door, open_warden_door, use_attack, heal;
  	Item();
  	Item(string, int, bool, bool, bool, bool);
};

#endif
