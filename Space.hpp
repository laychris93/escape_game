/********************************************************************* 
* ** Program Name: Space Class
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Header file for abstract Space class.  Class holds
* ** variables for pointers to adjacent Space objects, bools for whether 
* ** doors are locked, and string for name of space.  Includes functions
* ** for mananaging player interaction with the Spaces.
* *********************************************************************/ 

#ifndef SPACE_HPP
#define SPACE_HPP

#include <iostream>
#include <string>
#include <limits>
#include "Prisoner.hpp"
#include "Item.hpp"
#include "Utilities.hpp"
using std::string;

class Space
{
  protected:
  	Space* top;
  	Space* bottom;
  	Space* left;
  	Space* right;
  	bool guard_locked, warden_locked; 
  	string name;
  	Utilities util;

  public:
  	Space();
  	void set_top(Space*);
  	void set_bottom(Space*);
  	void set_left(Space*);
  	void set_right(Space*);
    void set_name(string);
  	bool get_guard_locked();
  	bool get_warden_locked();
  	string get_name();
  	void display_header();
  	Space* door_check(Prisoner&, Space*);
  	void enter_to_attack();
  	void run_round(Prisoner&, int&, int, int, string, string);
  	virtual void fight(Prisoner&);
  	virtual void fight_guard(Prisoner&);
  	virtual Space* move(Prisoner&);
  	virtual bool actions(Prisoner&, Space*&, bool&) = 0;
};

#endif