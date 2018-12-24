/********************************************************************* 
* ** Program Name: WardenOffice Class
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Implemenation file for WardenOffice class, derived from 
* ** Space class.  
* *********************************************************************/

#include "WardenOffice.hpp"
using std::cout;
using std::endl;


WardenOffice::WardenOffice() : Space()
{
	guard_locked = true;

	warden_locked = false;

	name = "Warden's Office";

	warden_defeated = false;

	warden_strength = 9;
}


/* function overrides base class function to implement 
additional strength and different weapon for Warden */
void WardenOffice::fight_guard(Prisoner &player)
{
	int round = 1;

	while (player.get_strength() > 0 && warden_strength > 0 && round <= 2)
	{
		run_round(player, warden_strength, 3, round, "taser", "Warden");

		round++;
	}

	while (player.get_strength() > 0 && warden_strength > 0)
	{
		run_round(player, warden_strength, 4, round, "gun", "Warden");

		round++;
	}
}



/* function overrides base class function to implement 
otaining Warden's keys if Warden defeated */
void WardenOffice::fight(Prisoner &player)
{
	bool not_cancel = true;

	int backpack_size = player.get_backpack().size(),
	    max_backpack = player.get_max_backpack(); 

	cout << endl << "Here comes the Warden!  GET READY!!" << endl;

	util.enter_to_continue();

	//fight warden
	fight_guard(player);

	//player beats Warden
	if (player.get_strength() > 0)
	{
		cout << endl << "YOU BEAT THE WARDEN!" << endl << endl;

		//if user's backpack is full, item must be discarded
		while (backpack_size >= max_backpack && not_cancel)
		{
			cout << "You have too many items.  You need to discard one to get the Warden's keys."
			     << endl << endl;

			not_cancel = player.rem_backpack();

			backpack_size = player.get_backpack().size();
		}
		//if backpack is not full
		if (backpack_size < max_backpack)
		{
			//keys successfully added
			if (player.add_backpack(Item("Warden Keys", 0, true, true, false, false)))
			{
				player.set_warden_key(true);

				cout << endl << "You've taken the Warden's keys!" << endl
				     << "You can open prison doors marked with a \"W\"!" << endl; 
			
				warden_defeated = true;
			}	
		}
		//keys not successfully added
		else
		{
			cout << endl << "Too Bad.  You'll have to fight the Warden again for his keys." << endl;
		}
		
		util.enter_to_continue();
	}	
}



/* Available actions for WardenOffice Space.  function accepts reference to 
Prisoner object, reference to Space pointer representing current
location, and reference to bool representing whether game continues.
WardenOffice actions allow user to battle Warden to obtain his keys. */
bool WardenOffice::actions(Prisoner &player, Space* &location, bool &free)
{
	int user_in = 0;

	//actions if warden not yet defeated
	if (!warden_defeated)
	{
		cout << endl << "You made it to the Warden's Office!  Are you ready to take him on?" << endl;

		cout << endl << name << " Actions" << endl << endl;

		cout << "1. Battle the Warden" << endl
	         << "2. Move Rooms" << endl
	         << "3. Use Items" << endl << endl
	         << "Enter 1-3: ";

			util.validate_int(user_in, 1, 3);

		//fight warden
		if (user_in == 1)
		{
			fight(player);
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
	//actions if warden has been defeated
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




