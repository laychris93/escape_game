/********************************************************************* 
 * ** Program Name: Game Class
 * ** Author: Jeremy Lay
 * ** Date: 12/24/2018  
 * ** Description: Header file for Game class.  Provides menus 
 * ** and functionality for user interaction with the Jailbreak!
 * ** game
 * *********************************************************************/ 

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <limits>
#include "Prisoner.hpp"
#include "YourCell.hpp"
#include "Cell.hpp"
#include "Hall.hpp"
#include "Hospital.hpp"
#include "WardenOffice.hpp"
#include "Armory.hpp"
#include "Escape.hpp"
#include "Item.hpp"
#include "Utilities.hpp"
using std::string;

const int TIME_LIMIT = 48;

class Game
{
  private:
  	Prisoner player;
    Space* location;

    YourCell cell_1;
    Cell cell_2;
    Hospital hosp;
    Escape front_door;
    WardenOffice warden;
    Armory arms;
  	Hall hall_left, hall_right, hall_center;
  
  	Utilities util; 

  	string divider_bot, divider_top, divider_mid_1, divider_mid_2;

    int time; 

    bool free;

  	void build_prison();
    void display_header();
    void display_instructions();
    char print_loc(Space*);
    void print_map();   
    
  public:
  	Game();
  	bool main_menu();
};

#endif
