/********************************************************************* 
 * ** Program Name: Jailbreak!
 * ** Author: Chris Lay
 * ** Date: 12/24/2018  
 * ** Description: Program for running Jailbreak! game.  
 * ** Run program with ./jailbreak. 
 * *********************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.hpp"

int main()
{
	srand(time(0));

	bool keep_playing = true;

	while (keep_playing)
	{
		Game game_1;

		keep_playing = game_1.main_menu();
	}
	
	return 0;
}