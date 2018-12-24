/********************************************************************* 
* ** Program Name: Item struct
* ** Author: Chris Lay
* ** Date: 12/24/2018  
* ** Description: Implemenation file for Item struct.  
* *********************************************************************/

#include "Item.hpp"

Item::Item()
{
	name = "";

	attack_power = 0;

	open_guard_door = false;

	open_warden_door = false;

	use_attack = false;

	heal = false;
}



Item::Item(string name_in, int attack_power_in, bool gd_in,
           bool wd_in, bool attack_in, bool heal_in)
{
	name = name_in;

	if (attack_power_in > 0 && attack_power_in <= 10)
	{
		attack_power = attack_power_in;
	}
	else
	{
		attack_power = 10;
	}
	
	open_guard_door = gd_in;

	open_warden_door = wd_in;

	use_attack = attack_in;

	heal = heal_in;
}
