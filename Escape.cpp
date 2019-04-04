/********************************************************************* 
* ** Program Name: Escape Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Implementation file for Escape class, derived from Space
* ** class.  
* *********************************************************************/

#include "Escape.hpp"
using std::cout;
using std::endl;

Escape::Escape() : Space()
{
	guard_locked = true;

	warden_locked = true;

	name = "Front Door";

	guard_num = 1;

}


/* Available actions for Escape Space.  function accepts reference to 
Prisoner object, reference to Space pointer representing current
location, and reference to bool representing whether game continues.
Escape actions allow user to battle exit guards to try to win game. */
bool Escape::actions(Prisoner &player, Space* &location, bool &free)
{
	int user_in = 0;

	cout << endl << "You made it to the Prison Exit!  Defeat 3 Guards to Win!" << endl;

	cout << endl << name << " Actions" << endl << endl;

	cout << "1. Fight Guard " << guard_num << endl
         << "2. Move Rooms" << endl
         << "3. Use Items" << endl << endl
         << "Enter 1-3: ";

		util.validate_int(user_in, 1, 3);

	//battle 3 exit guards to win game
	if (user_in == 1)
	{
		fight(player);

		if (player.get_strength() > 0)
		{
			//user wins if beats 3rd guard
			if (guard_num == 3)
			{
				free = true;
			}
			//move on to next guard if less than 3rd guard
			else
			{
				guard_num++;
			}
		}	
	}
	//user chooses to move
	else if (user_in == 2)
	{
		location = move(player);

		//no time counted off if user cancels move
		if (location == this)
		{
			return false;
		}

		//reset guard count so there are still 3 guards if user returns
		guard_num = 1;
	}
	//user chooses to use an item; no time counted off
	else
	{
		player.use_item();

		return false;
	}

	return true;
	
}



/* function overrides base class function to implement stonger exit guards */
void Escape::fight_guard(Prisoner &player)
{
	int guard_strength = 9, round = 1;

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

