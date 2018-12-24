/********************************************************************* 
* ** Program Name: Cell Class
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Implementation file for Cell class, derived from 
* ** Space class.
* *********************************************************************/

#include "Cell.hpp"
using std::cout;
using std::endl;

Cell::Cell() : Space()
{
	guard_locked = false;

	warden_locked = true;

	name = "Other Cells";

	prisoners_freed = false;
}


/* Available actions for Cell Space.  function accepts reference to 
Prisoner object, reference to Space pointer representing current
location, and reference to bool representing whether game continues.
Cell actions allow user to free other prisoners. */
bool Cell::actions(Prisoner &player, Space* &location, bool &free)
{
	int user_in = 0;

	//actions if user has not yet freed other prisoners 
	if (!prisoners_freed)
	{
		cout << endl << "You can create some chaos by freeing other prisoners!" << endl
		     << "This will increase your attack power by 1 point." << endl;

		cout << endl << name <<  " Actions" << endl << endl;

		cout << "1. Free Some Prisoners" << endl
	         << "2. Move Rooms" << endl
	         << "3. Use Items" << endl << endl
	         << "Enter 1-3: ";

			util.validate_int(user_in, 1, 3);

		//free prisoners
		if (user_in == 1)
		{
			//calls function to add extra power to player attacks
			player.extra_help_on();

			prisoners_freed = true;

			cout << endl << "Prisoners freed! Your attack power has increased by 1!" << endl;

			util.enter_to_continue();
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
		}
		//user chooses to use an item; no time counted off
		else
		{
			player.use_item();

			return false;
		}

		return true;
	}
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
		}
		//user chooses to use an item; no time counted off
		else
		{
			player.use_item();

			return false;
		}

		return true;
	}
}



