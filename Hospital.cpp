/********************************************************************* 
* ** Program Name: Hospital Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Implementation file for Hospital class, derived from Space
* ** class.  
* *********************************************************************/

#include "Hospital.hpp"
using std::cout;
using std::endl;


Hospital::Hospital() : Space()
{
	guard_locked = false;

	warden_locked = true;

	name = "Hospital";

	medicine_obtained = false;
}



/* Available actions for Hospital Space.  function accepts reference to 
Prisoner object, reference to Space pointer representing current
location, and reference to bool representing whether game continues.
Hospital actions allow user to try to restore health by taking medicine
immediately or adding medicine to backpack if space available. */
bool Hospital::actions(Prisoner &player, Space* &location, bool &free)
{
	int user_in = 0;

	//actions if user has not obtained the medicine
	if (!medicine_obtained)
	{
		cout << endl << "Welcome to the Prison Hospital!" << endl
		     << "You can get medicine here to restore your health." << endl;

		cout << endl << name <<  " Actions" << endl << endl;

		cout << "1. Take Medicine Now" << endl
		     << "2. Take Medicine with You for Later" << endl
	         << "3. Move Rooms" << endl
	         << "4. Use Items" << endl << endl
	         << "Enter 1-4: ";

			util.validate_int(user_in, 1, 4);

		//user chooses to take medicine immediately
		if (user_in == 1)
		{
			//player's strength to maximum
			player.inc_strength(30);

			medicine_obtained = true;

			cout << endl << "Your strength has been restored!" << endl;

			util.enter_to_continue();
		}
		//user chooses to add medicine to backpack for later use
		else if (user_in == 2)
		{
			//successul addition
			if (player.add_backpack(Item("Medicine", 0, false, false, false, true)))
			{
				medicine_obtained = true;

				cout << endl << "Choose \"Use Items\" to use your medicine later." << endl;
			}
			//user cancels/does not take medication if backpack is full
			else
			{
				cout << endl <<  "Medicine not taken." << endl;
			}

			util.enter_to_continue();

		} 
		//user chooses to move
		else if (user_in == 3)
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
	//if user has already used medicine
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





