/********************************************************************* 
* ** Program Name: YourCell Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Header file for YourCell class, derived from Space
* ** class.  
* *********************************************************************/

#include "YourCell.hpp"
using std::cout;
using std::endl;


YourCell::YourCell() : Space()
{
	guard_locked = true;

	warden_locked = false;

	name = "Your Cell";

	shank_hours = 0;

	shank = false;

	guard_defeated = false;
}



/* function overrides base class function to implement
addition of guard's keys and gun to backpack if successfully defeated */
void YourCell::fight(Prisoner &player)
{
	cout << endl << "Here comes the Guard!  GET READY!!" << endl;

	util.enter_to_continue();

	//run battle
	fight_guard(player);

	//player defeats guard
	if (player.get_strength() > 0)
	{
		cout << endl << "YOU BEAT THE GUARD!" << endl << endl
		     << "You took his keys and his gun (damage power = 4)!" << endl
		     << "Now you can open prison doors marked with a \"G\"!" << endl; 

		guard_defeated = true;

		//add guard keys and gun to backpack
		if (player.add_backpack(Item("Guard Keys", 0, true, false, false, false)))
		{
			player.set_guard_key(true);
		} 

		if (player.add_backpack(Item("Hand Gun", 4, false, false, true, false)))
		{
			player.set_current_weapon(player.get_backpack().back());
		} 

		util.enter_to_continue();
	}
}



/* function implements user ability to make shank weapon */
void YourCell::shank_work(Prisoner &player)
{
	//takes 2 hours to make shank
	if (shank_hours == 0)
	{
		shank_hours++;
		cout << endl << "You worked on your Shank - 1 more hour to go!" << endl;
	}
	//shank now complete
	else if (shank_hours == 1 && !shank)
	{
		//if shank successfully made, add to backpack if space
		Item temp("Shank", 3, false, false, true, false);

		cout << endl << "You finished your Shank." << endl;
		
		//shank successfully added to backpack
		if (player.add_backpack(temp))
		{
			player.set_current_weapon(temp);

			cout << endl << "Shank added!" << endl;

			shank = true;
		}
		//if not space/not added message to user to start over on shank
		else 
		{
			cout << endl 
			     << "Shank not added.  You'll have to start over making a new one."
			     << endl;

			shank_hours = 0;
		}
	}
	
	util.enter_to_continue();
}



/* function implements action where user regains strength 
by resting */
void YourCell::sleep(Prisoner &player)
{
	//if strength less than maximum, add 1 strength point 
	if (player.get_strength() < 30)
	{
		player.inc_strength(1);

		cout << endl << "Your strength has increased by 1 point."
		     << endl;
	}
	//strength at maximum
	else
	{
		cout << endl << "Your strength was already at the maximum, but at least you got some rest."
		     << endl;
	}	

	util.enter_to_continue();
}



/* Available actions for YourCell Space.  function accepts reference to 
Prisoner object, reference to Space pointer representing current
location, and reference to bool representing whether game continues.
YourCell actions allow user to try to work on a shank, battle a guard to
get keys and a gun, or rest to recover. */
bool YourCell::actions(Prisoner &player, Space* &location, bool &free)
{
	int user_in;

	cout << endl << name << " Actions" << endl << endl;

	//actions if shank not completed and guard not defeated
	if (!shank && !guard_defeated)
	{
	 	cout << "1. Work on Your Shank" << endl
	     	 << "2. Jump the Guard" << endl
	         << "3. Go to Sleep" << endl
	         << "4. Move Rooms" << endl
	         << "5. Use Items"
	         << endl << endl
	         << "Enter 1-5: ";

		util.validate_int(user_in, 1, 5);

		//work on shank
		if (user_in == 1)
		{
			shank_work(player);
		}
		//battle guard
		else if (user_in == 2)
		{
			fight(player);
		}
		//rest to recover
		else if (user_in == 3)
		{
			sleep(player);	
		}
		//user chooses to move
		else if (user_in == 4)
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
	//actions if shank completed but guard not defeated
	else if (shank && !guard_defeated)
	{
		cout << "1. Jump the Guard" << endl
	         << "2. Go to Sleep" << endl
	         << "3. Move Rooms" << endl
	         << "4. Use Items" << endl << endl
	         << "Enter 1-4: ";

		util.validate_int(user_in, 1, 4);

		//battle guard
		if (user_in == 1)
		{
			fight(player);
		}
		//rest to recover
		else if (user_in == 2)
		{
			sleep(player);
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
	//actions if shank not completed but guard defeated
	else if (!shank && guard_defeated)
	{
		cout << "1. Work on Your Shank" << endl
	     	 << "2. Go to Sleep" << endl
	         << "3. Move Rooms" << endl
	         << "4. Use Items" << endl << endl
	         << "Enter 1-4: ";

		util.validate_int(user_in, 1, 4);

		//work on shank
		if (user_in == 1)
		{
			shank_work(player);
		}
		//rest to recover
		else if (user_in == 2)
		{
			sleep(player);
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
	//actions if shank completed and guard defeated
	else
	{
		cout << "1. Go to Sleep" << endl
	         << "2. Move Rooms" << endl
	         << "3. Use Items" << endl << endl
	         << "Enter 1-3: ";

		util.validate_int(user_in, 1, 3);

		//rest to recover
		if (user_in == 1)
		{
			sleep(player);
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
}



