/********************************************************************* 
* ** Program Name: Prisoner Class
* ** Author: Jeremy Lay
* ** Date: 12/24/2018  
* ** Description: Implemenation file for Prisoner class.  
* *********************************************************************/ 

#include "Prisoner.hpp"

using std::vector;
using std::cout;
using std::endl;

Prisoner::Prisoner()
{
	strength = 25;

	attack_power = 1;

	guard_key = false;

	warden_key = false;

	extra_help = false;

	max_backpack = 4;
}

//Get and Set Functions


int Prisoner::get_attack_power()
{
	return attack_power;
}



vector<Item> Prisoner::get_backpack()
{
	return backpack;
}



Item Prisoner::get_current_weapon()
{
	return current_weapon;
}



bool Prisoner::get_guard_key()
{
	return guard_key;
}



int Prisoner::get_max_backpack()
{
	return max_backpack;
}



int Prisoner::get_strength()
{
	return strength;
}



bool Prisoner::get_warden_key()
{
	return warden_key;
}



void Prisoner::set_attack_power(int attack_in)
{
	if (attack_in > 0 && attack_in <= 6)
	{
		attack_power = attack_in;
	}

	if (extra_help)
	{
		attack_power++;
	}
}



void Prisoner::set_current_weapon(Item weapon_in)
{
	current_weapon = weapon_in;

	set_attack_power(current_weapon.attack_power);
}



void Prisoner::set_guard_key(bool key_in)
{
	guard_key = key_in;

}



void Prisoner::set_warden_key(bool key_in)
{
	warden_key = key_in;
}



/* function accepts input of Item struct.
adds Item to Item container if space available.
If not, calls rem_backpack function to give user
option to remove existing item and replace with 
new item.  returns true if item added to container,
false otherwise. */
bool Prisoner::add_backpack(Item item_in)
{
	bool not_cancel = true;

	int backpack_size = backpack.size();

	while (backpack_size >= max_backpack && not_cancel)
	{
		cout << endl << "Your backpack is full!"
		<< " You must discard an item before adding." << endl;

		not_cancel = rem_backpack();

		backpack_size = backpack.size();
	}

	if (backpack_size < max_backpack)
	{
		backpack.push_back(item_in);
		return true;
	}
		
	return false;
}



/* function impplements extra attack power due to 
freeing other prisoners by increasing attack_power by 1 */
void Prisoner::extra_help_on()
{
	extra_help = true;

	set_attack_power(attack_power);
}



/* function increases player's strength.  accepts 
integer representing the amount of increase.  if 
current strength plus added strength is less than 
max strength, adds input strength to current strength.
otherwise, sets strength to maximum */
void Prisoner::inc_strength(int strength_in)
{
	if (strength_in >= 0)
	{
		if (strength + strength_in <= 30)
		{
			strength += strength_in;
		}
		else
		{
			strength = 30;
		}
	}
}



/* function reduces player's strength.  accepts 
integer representing the amount of decrease. */
void Prisoner::red_strength(int strength_in)
{
	if (strength_in >= 0)
	{
		if (strength - strength_in >= 0)
		{
			strength -= strength_in;
		}
		else
		{
			strength = 0;
		}
	}
}


/* function removes user chosen item from backpack/item 
container if capacity limit is reached.  function does not 
allow user to remove keys.  returns true if an item is removed,
false otherwise. */
bool Prisoner::rem_backpack()
{
	int i = 0, user_in = 0, final = 0, ret_index = 0;

	Item array[4];

	//create array of items that can be removed
	for (unsigned j = 0; j < backpack.size(); j++)
	{
		if (backpack.at(j).use_attack || backpack.at(j).heal)
		{
			array[i] = backpack.at(j);
			i++;
		}
	}
	cout << endl << "You cannot remove keys." << endl;

	//if items can be removed
	if (i > 0)
	{
		//allows user to choose item to remove or cancel
		cout << endl << "Choose Item to Remove." << endl << endl;

		//generate menu and let user choose
		for (int j = 0; j < i; j++)
		{
			cout << j+1 << ". " << array[j].name << endl;
		}

		final = i + 1;

		cout << final << ". Cancel" << endl
		     << endl << "Enter 1-" << final << ": ";

		util.validate_int(user_in, 1, final);

		//if user did not choose to cancel
		if (user_in != final)
		{
			ret_index = user_in - 1;

			//remove item from container and display message
			for (unsigned i = 0; i < backpack.size(); i++)
			{
				if (backpack.at(i).name == array[ret_index].name)
				{
					backpack.erase(backpack.begin()+i); 
				}
			}

			cout << endl << "Item Removed." << endl;

			util.enter_to_continue();

			return true;
		}
	}
	else
	{
		cout << endl << "There are no items that you can remove." << endl;

		util.enter_to_continue();
	}

	return false;
}



/* function allows user to choose item from backpack to use.
weapons chosen are set to player's current weapon; medicine chosen
restores strength; keys chosen have no effect other than to display 
message to user re: key function is to open doors - as keys are 
applied automatically in the game. */
void Prisoner::use_item()
{
	int user_in = 0, ret_index = 0, size = backpack.size(), i = 0;

	//if no items in backpack
	if (size == 0)
	{
		cout << endl << "You have no items to use." << endl
		     << endl;
	}
	//if items in backpack
	else
	{
		//instructions to user and menu to choose item
		cout << endl << "Item Menu" << endl
			 << endl << "Selecting a weapon will make it your current weapon."
		     << endl << "Selecting medicine (if you have it) will restore your health."
		     << endl << "Keys are automatically used."
		     << endl << endl << "Choose an item: "
	         << endl << endl;

		while (i < size)
		{
			i++;
			cout << i << ". " << backpack.at(i - 1).name << endl;
		}

		cout << i + 1 << ". Cancel" << endl << endl
             << "Enter 1-" << i + 1 << ": "; 
		
		util.validate_int(user_in, 1, i + 1);

		//if user does not choose cancel 
		if (user_in != i + 1)
		{
			ret_index = user_in - 1;

			//user chooses medicine
			if (backpack.at(ret_index).heal)
			{
				//strength set to max
				strength = 30;

				cout << endl << "You used the medicine.  Your strength is replenished!" << endl;

				//medicine removed from container
				backpack.erase(backpack.begin()+ret_index);	
			}
			//if user chooses weapon
			else if (backpack.at(ret_index).use_attack)
			{
				//user choice is made player's current weapon
				set_current_weapon(backpack.at(ret_index));

				cout << endl << "Weapon Set!" << endl;
			}
			//user chooses a key
			else
			{
				//message displayed as to key function
				cout << endl << "Keys open doors!" << endl;
			}
		}
		//if user cancels use item
		else
		{
			cout << endl << "Action Canceled." << endl;
		}
	}

	util.enter_to_continue();
}
