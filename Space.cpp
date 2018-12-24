/********************************************************************* 
* ** Program Name: Space Class
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Implementation file for abstract Space class.  
* *********************************************************************/ 

#include "Space.hpp"
using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;


Space::Space()
{
	top = NULL;

	bottom = NULL;

	left = NULL;

	right = NULL;

}


//Set and Get Functions

void Space::set_top(Space* top_in)
{
	if (top_in != NULL)
	{
		top = top_in;
	}
}



void Space::set_bottom(Space* bottom_in)
{
	if (bottom_in != NULL)
	{
		bottom = bottom_in;
	}
}



void Space::set_left(Space* left_in)
{
	if (left_in != NULL)
	{
		left = left_in;
	}
}



void Space::set_right(Space* right_in)
{
	if (right_in != NULL)
	{
		right = right_in;
	}
}



void Space::set_name(string name_in)
{
	name = name_in;
}



bool Space::get_guard_locked()
{
	return guard_locked;
}



bool Space::get_warden_locked()
{
	return warden_locked;
}



string Space::get_name()
{
	return name;
}



/* displays game name */
void Space::display_header()
{
	cout << "** JAILBREAK! **" << endl << endl;
}



/* function assists move function.  function accepts reference to
o Prisoner object and Space pointer representing intended new Space 
to move to.  Function checks whether there is a locked door between the 
Spaces.  Returns Space pointer  representing new location.  If door is 
locked and no key available, returns current location.  If door is unlocked, 
returns the new Space.*/
Space* Space::door_check(Prisoner &player, Space* move_ptr)
{
	int confirm_in = 0;

	//if door is locked and player doesn't have required Warden key 
	if (!(player.get_warden_key()) && (warden_locked || move_ptr -> get_warden_locked()))
	{
		cout << endl << "You cannot open the door - you need the WARDEN'S KEY." 
		     << endl;

		util.enter_to_continue();

		return this;
	}
	//if door is locked and player doesn't have required Guard key
	else if (!(player.get_guard_key()) && (guard_locked || move_ptr -> get_guard_locked()))
	{
		cout << endl << "You cannot open the door - you need the GUARD'S KEY." 
		     << endl;

		util.enter_to_continue();

		return this;
	}
	//if player can unlock door
	else
	{
		cout << endl << "You can unlock the door with your keys!" << endl
		     << endl << "Confirm Move to " << move_ptr -> get_name()
	     	 << endl << endl << "1. Move" << endl << "2. Cancel" << endl << endl
	         << "Enter 1-2: ";

	    util.validate_int(confirm_in, 1, 2);

	    //return pointer to new location
		if (confirm_in == 1)
		{
			return move_ptr;
		}
		else
		{
			cout << endl << "Move Canceled." << endl;
			util.enter_to_continue();
		}

		//player canceled move
		return this;
	}
}



/* user interaction for battle with Guards */
void Space::enter_to_attack()
{
    cout << endl << "Press Enter to attack the guard: ";

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}


/* function runs one round of battle between player and Guard.
function accepts reference to Prisoner object, reference to int representing
guard's strength, int representing guard's attack strength, int representing 
round, and strings representing type of weapon used by guard and type of guard.
implements 25% chance that an attack will fail.  If attack successful removes
attack value from player/guard strength */
void Space::run_round(Prisoner &player, int &guard_strength, 
	                  int guard_attack, int round, string weapon, string name)
{
	int dice_roll = 0, attack = player.get_attack_power();

	util.clear_screen();

	display_header();

	//display round info to user
	cout << name << " Battle - Round " << round << endl;

	cout << endl << "Your Strength: " << player.get_strength() << endl
	     << name << " Strength: " << guard_strength << endl << endl;

	//player attacks guard
	enter_to_attack();

	//25% chance player attack fails
	dice_roll = rand() % 4;

	if (dice_roll < 3)
	{
		//if attack successful subtract from guard strength and display message
		guard_strength -= attack;

		cout << endl << "You hit the " << name << "!" << endl << "He lost " << attack
		     << " health points." << endl;
	}
	else
	{
		cout << endl << "Your attack was not successful!" << endl;
	}

	if (guard_strength > 0)
	{
		dice_roll = rand() % 4;

		if (dice_roll < 3)
		{
			player.red_strength(guard_attack); 

			cout << endl << "The " << name << " attacked you with his " << weapon << "!"
			     << endl << "You lost " << guard_attack
			     << " health points." << endl;
		}
		else
		{
			cout << endl << "The " << name << "'s attack was not successful!" << endl;
		}
	}
	
	util.enter_to_continue();
}



/* virtual fight function displays message and calls functions to
run player/guard battle.  function accepts reference to Prisoner
object.  base class version for standard guard. */
void Space::fight(Prisoner &player)
{
	cout << endl << "Here comes the Guard!  GET READY!!" << endl;

	util.enter_to_continue();

	fight_guard(player);

	if (player.get_strength() > 0)
	{
		cout << endl << "YOU BEAT THE GUARD!" << endl;

		util.enter_to_continue();
	}
}



/* virtual function allows guard to switch weapons. accepts reference
to Prisoner object.  calls run_round function while player and guard
both have strength remaining.  base class function for standard guard. */
void Space::fight_guard(Prisoner &player)
{
	int guard_strength = 6, round = 1;

	while (player.get_strength() > 0 && guard_strength > 0 && round <= 2)
	{
		
		run_round(player, guard_strength, 2, round, "billy club", "Guard");

		round++;
	}

	while (player.get_strength() > 0 && guard_strength > 0)
	{
		run_round(player, guard_strength, 4, round, "gun", "Guard");

		round++;
	}
}



/* function accepts reference to Prisoner object.  function
creates menu of Spaces that are available for moves, collects
and validates user input on choice of move, then calls door_check
function to test whether user can open doors. */
Space* Space::move(Prisoner& player)
{	
	int i = 0, user_in = 0, ret_index = 0;

	Space* array[4] = {NULL};

	//create array of available moves
	if (top != NULL)
	{
		array[i] = top;
		i++;
	}

	if (bottom != NULL)
	{
		array[i] = bottom;
		i++;
	} 

	if (left != NULL)
	{
		array[i] = left;
		i++;
	}

	if (right != NULL)
	{
		array[i] = right;
		i++;
	}

	/*if only 1 move available checks whether player
	has key to open door */
	if (i == 1)
	{		
		return door_check(player, array[0]);
	}
	else
	{
		//user chooses move if multiple available
		cout << endl << "Choose Move" << endl << endl;

		//creates menu of availble move
		for (int j = 0; j < i; j++)
		{
			cout << j+1 << ". " << array[j] -> get_name() << endl;
		}

		cout << endl << "Enter 1-" << i << ": ";

		util.validate_int(user_in, 1, i);

		ret_index = user_in - 1;

		//check if user has key to open chosen door
		return door_check(player, array[ret_index]);
	}
}




