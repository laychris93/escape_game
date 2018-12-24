
/********************************************************************* 
 * ** Program Name: Utilities Class
 * ** Author: Chris Lay
 * ** Date: 12/24/2018 
 * ** Description: Implementation file for Utilities class.              
 * *********************************************************************/ 


#include "Utilities.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istringstream;
using std::isdigit;
using std::streamsize;
using std::numeric_limits;
using std::ifstream;



/********************************************************************* 
** Description: Function accepts input of integer reference variable  and
** and ints representing max and min values and collects user input.  
** Function validates that user input is of type int and within range.  
** If not, error message is displayed and user is asked to re-enter input.
*********************************************************************/

void Utilities::validate_int(int &intIn, int min, int max)
{
    bool error = true;

    string userIn;

    int start, size;

    while (error)
    {

        error = false;

        getline(cin, userIn);

        if (userIn.empty())
        {
            cout << "Invalid entry - re-enter: ";
            
            error = true;
        }
        else
        {
            size = userIn.length();

            if (userIn[0] == '-')
            {
                start = 1;
            }
            else 
            {
                start = 0;
            }

            for (int pos = start; pos < size; pos++)
            {
                if (!(isdigit(userIn[pos]))) 
                {
                    error = true;
                }
            }

            if (error)
            {
                cout << "Invalid entry - re-enter: ";
            }
            else
            {
                istringstream str(userIn);

                str >> intIn;

                if (intIn < min || intIn > max)
                {
                    cout << "Invalid entry - re-enter: ";
                    error = true;
                }
            }
        }   
    }
}

/********************************************************************* 
** Description: Function accepts input of double reference variable and
** and doubles representing max and min values and collects user input.  
** Function validates that user input is of type double and within range.  
** If not, error message is displayed and user is asked to re-enter input.
*********************************************************************/

void Utilities::validate_double(double &doubleIn, double min, double max)
{
    bool error, firstPoint;

    string userIn;

    int start, size;

    do
    {

        error = false;

        firstPoint = true;

        getline(cin, userIn);

        if (userIn.empty())
        {
            cout << "Invalid entry - re-enter: ";
            error = true;
        }
        else
        {
            size = userIn.length();

            if (userIn[0] == '-')
            {
                start = 1;
            }
            else 
            {
                start = 0;
            }

            for (int pos = start; pos < size; pos++)
            {
                if (!(isdigit(userIn[pos]))) 
                {
                    if (userIn[pos] == '.' && firstPoint)
                    {
                        firstPoint = false;
                    }
                    else
                    {
                        error = true;
                    }
                    
                }
            }

            if (error)
            {
                cout << "Invalid entry - re-enter: ";
            }
            else
            {
                istringstream str(userIn);

                str >> doubleIn;

                if (doubleIn < min || doubleIn > max)
                {
                    cout << "Invalid entry - re-enter: ";
                    error = true;
                }
            }
        }
        
    } while (error);

}



//collects and validates user string input, allowing for 
//limit on string size
void Utilities::validate_string(string& string_in, unsigned max)
{
    unsigned string_max = string_in.max_size();

    if (max == 0 || max > string_max)
    {
        max = string_max;
    }

    getline(cin, string_in);

    while (string_in.size() > max || string_in.empty())
    {
        cout << "Invalid entry - re-enter: ";
        getline(cin, string_in);
    }
}


//generates a random float value between the input min
//and max values
//https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
double Utilities::f_rand(double min, double max)
{
    double f = (double)rand() / RAND_MAX;

    return min + f * (max - min);
}



//pauses interaction until user presses enter
void Utilities::enter_to_continue()
{
    cout << endl << "Press Enter to continue: ";

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}



//clears console screen
void Utilities::clear_screen()
{
    cout << "\033[2J\033[1;1H";
}








