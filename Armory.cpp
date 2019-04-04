/********************************************************************* 
* ** Program Name: Armory Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018 
* ** Description: Implementation file for Armory class, derived from Space
* ** class.  
* *********************************************************************/ 

#include "Armory.hpp"
using std::cout;
using std::endl;

Armory::Armory() : Space()
{
	guard_locked = true;

	warden_locked = true;

	name = "Armory";

	shotgun_obtained = false;
}


/* Available actions for Armory Space.  function accepts reference to 
Prisoner object, reference to Space pointer representing current
location, and reference to bool representing whether game continues.
Armory actions allow user to try to obtain shotgun from Armory, move rooms,
or use items. returns true if game hour count should be advanced, false if not. */
bool Armory::actions(Prisoner &player, Space* &location, bool &free)
{
	int user_in = 0;

	//actions where user has not yet obtained the shotgun
	if (!shotgun_obtained)
	{
		cout << endl << "You can steal a shotgun (attack power: 6) if you beat the Guard!" << endl;

		cout << endl << name << " Actions" << endl << endl;

		cout << "1. Fight the Guard for a Shotgun" << endl
	         << "2. Move Rooms" << endl
	         << "3. Use Items" << endl << endl
	         << "Enter 1-3: ";

			util.validate_int(user_in, 1, 3);

		//user chooses to fight guard for shotgun
		if (user_in == 1)
		{
			fight(player);

			//user wins battle
			if (player.get_strength() > 0)
			{
				//user successfully obtains shotgun
				if (player.add_backpack(Item("Shotgun", 6, false, false, true, false)))
				{
					shotgun_obtained = true;

					player.set_current_weapon(player.get_backpack().back());

					cout << endl << "You've got the shotgun!" << endl;   
				}
				//user cancel shotgun add or doesn't have room and won't discard
				//another item
				else
				{
					cout << endl << "You will have to fight another guard to get a shotgun."
					     << endl;
				}
				
				util.enter_to_continue();
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
		}
		//user chooses to use an item; no time counted off
		else
		{
			player.use_item();

			return false;
		}

		return true;
	}
	//actions where user has already obtained shotgun
	else
	{
		cout << endl << name <<  " Actions" << endl << endl;

		cout << "1. Move Rooms" << endl
	         << "2. Use Items" << endl << endl
	         << "Enter 1-2: ";

			util.validate_int(user_in, 1, 2);

		//user chooses to move rooms
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


