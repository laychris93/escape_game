/********************************************************************* 
* ** Program Name: Prisoner Class
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Header file for Prisoner class.  Class holds int
* ** variables for player strength, current attack power, max backpack 
* ** (item container) size, a vector representing backpack/item container
* ** an Item struct representing user's current weapon, and bools 
* ** representing whether user has guard's key, warden's key, and has 
* ** freed other prisoners.  Includes functions for managing strength, 
* ** keys, and backpack items.
* *********************************************************************/ 

#ifndef PRISONER_HPP
#define PRISONER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "Item.hpp"
#include "Utilities.hpp"
using std::vector;

class Prisoner
{
  private:
  	int strength, attack_power, max_backpack;
  	vector<Item> backpack;
  	Item current_weapon;
  	bool guard_key, warden_key, extra_help;
  	
  	Utilities util;

  public:
  	Prisoner();
  	int get_attack_power();
  	vector<Item> get_backpack();
  	Item get_current_weapon();
  	bool get_guard_key();
  	int get_max_backpack();
  	int get_strength();
  	bool get_warden_key();
  	void set_attack_power(int);
  	void set_current_weapon(Item);
  	void set_guard_key(bool);
  	void set_warden_key(bool);
  	
  	bool add_backpack(Item);
  	void extra_help_on();
  	void inc_strength(int);
  	void red_strength(int);
  	bool rem_backpack();
  	void use_item();
};

#endif