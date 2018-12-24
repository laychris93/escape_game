/********************************************************************* 
* ** Program Name: Hall Class
* ** Author: Chris Lay
* ** Date: 12/24/2018 
* ** Description: Implementation file for Hall class, derived from Space
* ** class.  
* *********************************************************************/

#include "Hall.hpp"
using std::string;
using std::cout;
using std::endl;

Hall::Hall() : Space()
{
	guard_locked = true;

	warden_locked = false;

	name = "";

	beat_a_guard = false;
}



/* Available actions for Hall Space.  function accepts reference to 
Prisoner object, reference to Space pointer representing current
location, and reference to bool representing whether game continues.
Hall actions implements surprise attacks from guards. */
bool Hall::actions(Prisoner &player, Space* &location, bool &free)
{
	int user_in = 0;

	/*50% chance to fight a guard if not previously fought on 
	this visit to Space */
	if (rand() % 2 && !beat_a_guard)
	{
		cout << endl << "A Guard Spotted You!" << endl;

		fight(player);

		beat_a_guard = true;
	}
	//actions if guard fight not initiated
	else
	{
		cout << endl << name <<  " Actions" << endl << endl;

		cout << "1. Move Rooms" << endl
	         << "2. Use Items" << endl << endl
	         << "Enter 1-2: ";

		util.validate_int(user_in, 1, 2);

		//user chooses to move
		if (user_in == 1)
		{
			location = move(player);

			//no time counted off if user cancels move
			if (location == this)
			{
				return false;
			}

			beat_a_guard = false;
		}
		//user chooses to use an item; no time counted off
		else
		{
			player.use_item();

			return false;
		}
	}

	return true;
}
