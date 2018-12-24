/********************************************************************* 
 * ** Program Name: Game Class
 * ** Author: Chris Lay
 * ** Date: 12/24/2018 
 * ** Description: Implementation file for Game class.  
 * *********************************************************************/ 

#include "Game.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::streamsize;
using std::numeric_limits;
using std::to_string;
using std::vector;

Game::Game()
{
	location = &cell_1;

	hall_right.set_name("East Hall");

	hall_left.set_name("West Hall");

	hall_center.set_name("Center Hall");
 
 	divider_top = " ----- ----- ----- ";
 	divider_bot = " ----- --W-- ----- ";
 	divider_mid_1 = " --G-- --W-- --G-- ";
 	divider_mid_2 = " --W-- --W-- --W-- ";

 	time = 1;

 	free = false;	
}



//PRIVATE MEMBER FUNCTIONS

/* function creates prison structure by setting 
the non-NULL top/bottom/left/right pointers for 
each room of the prison */
void Game::build_prison()
{
	cell_1.set_bottom(&hall_right);

	hall_right.set_top(&cell_1);
	hall_right.set_bottom(&cell_2);
	hall_right.set_left(&hall_center);

	cell_2.set_top(&hall_right);

	hall_center.set_top(&hosp);
	hall_center.set_bottom(&front_door);
	hall_center.set_left(&hall_left);
	hall_center.set_right(&hall_right);

	hosp.set_bottom(&hall_center);

	hall_left.set_top(&warden);
	hall_left.set_bottom(&arms);
	hall_left.set_left(&hall_center);

	warden.set_bottom(&hall_left);

	arms.set_top(&hall_left);
	arms.set_right(&front_door);

	front_door.set_top(&hall_center);
	front_door.set_left(&arms);
}



//displays name of program 
void Game::display_header()
{
	cout << "** JAILBREAK! **" << endl << endl;
}



/* function allows user to choose to read game 
instructions or skip directly to game play */
void Game::display_instructions()
{
	int user_choice;

	util.clear_screen();

	display_header();

	cout << "Instructions" << endl << endl
	     << "1. View" << endl
	     << "2. Skip" << endl << endl
	     << "Enter 1-2: ";

	util.validate_int(user_choice, 1, 2);

	if (user_choice == 1)
	{
		util.clear_screen();

		display_header();

		cout << "YOU ARE IN JAIL!" << endl << endl
		     << "You have learned that a powerful prison gang plans to kill you in 48 hours."
		     << endl << "You must escape before the 48 hours is up to survive!" << endl << endl
		     << "Every action you take will cost 1 hour."
		     << endl << endl
		     << "You start the game in your cell with 25 health points." << endl << endl 
		     << "You can increase your health to a maximum of 30 points by resting in your cell." << endl
		     << "Each health point requires 1 hour of rest." << endl
		     << endl << "You can return to your cell to rest and recover after going elsewhere." << endl
		     << endl << "You die and the game ends if you run out of " 
		     << "health points or if you" << endl << "don't get out within 48 hours." << endl;

		util.enter_to_continue();

		util.clear_screen();

		display_header();

		cout << "To escape your cell, you will first have to attack a guard and steal his keys." << endl
		     << endl << "The Guard's keys will open your cell's door and the hallway doors, but you will" 
		     << endl << "have to defeat the Warden and steal his keys to open the other doors."
		     << endl << endl
		     << "You can also steal the Guard's gun to increase your attack power." << endl;
		     
		    
		util.enter_to_continue();

		util.clear_screen();

		display_header();
		
		cout << "Each Guard has 6 health points.  Although they are relatively weak," << endl
		     << "Guards will attack you with weapons." << endl 
		     << endl << "The Warden is like a Guard, except he has 8 health points." << endl
		     << endl << "The strongest Guards watch the exit - they have 9 health points." << endl
		     << endl << "Guards will first attempt to subdue you with a billy club."
		     << endl << "A billy club inflicts 2 points of damage." << endl
		     << endl << "Guards will use a gun if you do not defeat them within 2 attempts."
		     << endl << "A gun inflicts 4 points of damage." << endl;

		util.enter_to_continue();

		util.clear_screen();

		display_header();

		cout << "There is a 50%" << " chance that you will be spotted by a Guard in any prison hallway."
		     << endl << endl << "There is 1 Guard in the Armory, where weapons are stored." 
		     << endl << endl << "There are always 3 Guards watching the exit." << endl
		     << endl << "There will be new 3 Guards if you leave the Exit area and then return."
		     << endl;

		util.enter_to_continue();

		util.clear_screen();

		display_header();

		cout << "You can inflict 1 point of damage per attempt attacking with your hands alone." << endl
		     << endl << "You have been working on a Shank in your cell." << endl 
		     << "You can complete it with 2 additional hours of work." << endl
		     << endl << "A Shank will inflict 3 points of damage per attack." << endl 
		     << endl << "If you defeat the first Guard, you can steal his gun." << endl
		     << endl << "You can steal a shot gun (6 damage points) if you get the Warden's keys" 
		     << endl << "and break into the Armory."
		     << endl << endl << "Also, you can use the Warden's keys to open other prisoners' cells."
		     << endl << "This will increase your attacking power by 1 additional point." << endl 
		     << endl << "In any attempted attack, whether by you or a Guard, there is a 25%" << " chance that" 
		     << endl << "the attack will fail and inflict no damage." << endl
		     << endl << "You can break into the prison hospital to steal medicine." << endl
		     << endl << "Medicine will give you a full 20 points of health when you use it."
		     << endl << "Medicine can only be used once." << endl;
		     

		util.enter_to_continue();

		util.clear_screen();

		display_header();

		cout << "You have a backpack and can carry at most 4 items (weapons, keys, medicine, etc)."
		     << endl << "If your backpack is full, you will have to remove an item before adding something new."
		     << endl << "However, you cannot remove keys." << endl << endl
		     << "Use the Warden's keys to unlock the prison exit and defeat the Guards" 
		     << endl << "at the exit to escape and win the game!" << endl << endl
		     << "Remember, each fight with a Guard costs an hour, so give yourself time to fight all three!"
		     << endl << endl << "GOOD LUCK!" << endl;

		util.enter_to_continue();
	}

}
/* function assists print_map function by returning char for what should
be displayed in that space.  Returns 'X' representing player location if 
pointer passed in to function matches private member variable pointer 
representing current location, returns space otherwise. */
char Game::print_loc(Space* loc_in)
{
	if (loc_in == location)
	{
		return 'X';
	}
	else
	{
		return ' ';
	}
}



/* function creates console display of prison structure 
showing each room and doors between rooms.  Also,
shows player location, strength, and current weapon. */
void Game::print_map()
{
	cout << "Your Location (marked with 'X'): " << location -> get_name()
		 << endl << "STRENGTH: " << player.get_strength() << endl
		 << "CURRENT WEAPON: ";

	if (player.get_current_weapon().name == "")
	{
		cout << "Hands" << endl;
	}
	else
	{
		cout << player.get_current_weapon().name << endl;
	}
	
	cout << endl << divider_top << endl
	     << "| WO " << print_loc(&warden) 
	     << "| HP " << print_loc(&hosp) 
	     << "| YC " << print_loc(&cell_1) << "|" 
	     << endl << divider_mid_1 << endl
	     << "| WH " << print_loc(&hall_left) 
	     << "G CH " << print_loc(&hall_center)
	     << "G EH " << print_loc(&hall_right) << "|"
	     << endl << divider_mid_2 << endl
	     << "| AR " << print_loc(&arms)
	     << "W EX " << print_loc(&front_door)
	     << "| OC " << print_loc(&cell_2) << "|"
	     << endl << divider_bot << endl << endl
	     << "WO: Warden's Office; HP: Hospital; YC: Your Cell"
	     << endl << "WH: West Hall; CH: Center Hall; EH: East Hall"
	     << endl << "AR: Armory; EX: Exit; OC: Other Cell" << endl
	     << endl << "G: Door - Guard Key to Unlock" << endl
	     << "W: Door - Warden Key to Unlock" << endl;
}



//PUBLIC MEMBER FUNCTION

/* Function collects and validates user input on whether to  
play game or quit.  Returns true if user chooses to play; false if
user chooses to quit. Calls each prison space's actions function 
for user interaction while under time limit/user has not won game/user
has not lost game */
bool Game::main_menu()
{
	int user_choice;

	util.clear_screen();

	display_header();

	cout << "Main Menu" << endl << endl
         << "1. Play Game"
         << endl << "2. Exit" << endl << endl
         << "Enter 1-2: ";

    util.validate_int(user_choice, 1, 2);

    if (user_choice == 2)
    {
        return false;
    }

    //game setup
    build_prison();

   	display_instructions();

   	//game loop
    while (time <= TIME_LIMIT && !free && player.get_strength() > 0)
    {
    	util.clear_screen();

    	display_header();

    	cout << "HOUR " << time << endl << endl;

    	print_map();

    	if (location -> actions(player, location, free))
    	{
    		time++;	
    	}
    }

    //game result messages
    util.clear_screen();

    if (time > TIME_LIMIT && !free)
    {
    	cout << "YOU DID NOT ESCAPE IN TIME!!" << endl;
    }
    else if (player.get_strength() <= 0)
    {
    	cout << "YOU DIED!!" << endl;
    }
    else
    {
    	cout << "YOU ESCAPED!! ENJOY YOUR FREEDOM WHILE IT LASTS!" << endl;
    }

    cout << endl << "GAME OVER" << endl;

    util.enter_to_continue();

    return true;
}
