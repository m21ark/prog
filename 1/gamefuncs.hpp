// T07_G07 
#ifndef gamefuncs
#define gamefuncs
using namespace std;

struct Robot
{
    int xpos, ypos;
    bool alive = true;
};

struct Player
{
    int xpos, ypos;
    bool alive = true;
};

/*
Creates a prompt asking user for their name
@return 15 char name given by user
*/
string askWinnerName()
{
    while (1)
    {
        //asks name
        string s = "";
        string s2 = "";
        char c = ' ';
        cout << endl
             << "Please insert your name: \n"
             << " > ";
        getline(cin, s2);
        stripStr(s2);
        if (cin.fail() && cin.eof())
            exit(1); // detects ctrlz

        //test if empty name is choosed
        if (s2.size() == 0)
        {
            cout << "Empty name not allowed!" << endl;
            continue;
        }

        //reduce to 15 char if needed
        if (s2.size() <= 15)
        {
            s = s2;
        }
        else
            for (int i = 0; i < 15; i++)
                s += s2[i];
        stripStr(s);

        //stops user from using '-' as a caracter
        bool invalidChar = false;
        for (char ch : s)
            if (ch == '-')
            {
                cout << "You can't use \"-\" in your name!" << endl;
                invalidChar = true;
                break;
            }
        if (invalidChar)
            continue;

        //confirms name
        cout << "Is '" << s << "' the name you want? (Y/N)" << endl
             << " > ";
        if ((cin >> c))
        {
            //raises error if more than 1 char is written by user
            if (!emptyCin())
            {
                cout << "Invalid Input!" << endl;
                continue;
            }
            //tests user's answer
            if (c == 'y' || c == 'Y')
                return s;
            else if (c == 'N' || c == 'n')
                continue;
            else
            {
                cout << "Invalid Input!" << endl;
                continue;
            }
        }
        else
        {
            //deals with errors when trying to get the char
            if (cin.fail() && cin.eof())
                exit(1); // detects ctrlz
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Choose Y/N" << endl;
            continue;
        }
    }
}

/*
Creates a prompt asking user if they want to play again
@return true if said YES and NO otherwise
*/
bool AskPlayAgain()
{
    while (1)
    {
        //asks if player wants to play again
        char c;
        cout << "Do you want to play again? (Y/N)" << endl
             << " > ";
        if ((cin >> c))
        {
            //raises error if more than 1 char is written by user
            if (!emptyCin())
            {
                cout << "Invalid Input! Choose Y/N" << endl
                     << endl;
                continue;
            }
            //tests user's char
            if (c == 'y' || c == 'Y')
                return true;
            else if (c == 'N' || c == 'n')
                return false;
            else
            {
                cout << "Invalid Input! Choose Y/N" << endl
                     << endl;
                continue;
            }
        }
        else
        {
            //deals with errors when trying to get the char
            if (cin.eof())
                exit(1); // detects ctrlz
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Choose Y/N" << endl
                 << endl;
            continue;
        }
    }
}

/*
Shows map stored in vector in console
@param map vector that contains map
*/
void showMap(const vector<string> &map)
{
    for (string i : map)
        cout << i << endl;
    cout << endl;
}

/*
Gets player coordinates in the loaded map
@param map vector that contains map
@param &xpos Player's X coordinate 
@param &ypos Player's Y coordinate
*/
void findPlayer(const vector<string> &map, int &xpos, int &ypos)
{
    //prints and saves player cords
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[0].size(); j++)
            if (map[i][j] == 'H')
            {
                xpos = j;
                ypos = i;
            }
}

/*
Stores all Robot objects found on map to vector
@param map vector that contains map
@param &rlist vector that will store all Robot objects
*/
void findRobots(const vector<string> &map, vector<Robot> &rlist)
{
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[0].size(); j++)
            if (map[i][j] == 'R')
            {
                Robot aux;
                aux.xpos = j;
                aux.ypos = i;
                rlist.push_back(aux);
            }
}

/*
Evaluates robot's movement to new position and verifies it's consequences
@param map vector that contains map
@param &rb Robot object that moved
@param &rlist vector that stores all Robot objects
@param &alex Player Object
*/
void safeRobotPos(vector<string> &map, Robot &rb, vector<Robot> &rlist, Player &alex)
{
    //tests the new pos the player is moving to
    char new_pos = map[rb.ypos][rb.xpos];
    if (new_pos == '*' || new_pos == 'r')
    {
        //kills robot
        map[rb.ypos][rb.xpos] = 'r';
        rb.alive = false;
    }
    else if (new_pos == 'R')
    {
        //deal with alive robot colision
        rb.alive = false;
        map[rb.ypos][rb.xpos] = 'r';

        //find which robot is in the same pos
        for (Robot &r : rlist)
            if (r.xpos == rb.xpos && r.ypos == rb.ypos)
                r.alive = false;
    }
    else if (new_pos == 'H' || new_pos == 'h')
    {
        //kills player
        map[rb.ypos][rb.xpos] = 'h';
        alex.alive = false;
    }
    else
    {
        map[rb.ypos][rb.xpos] = 'R';
    }
}

/*
Makes all robots move based on Player's position
@param &map vector that contains map
@param &rlist vector that stores all Robot objects
@param &alex Player Object
*/
void robotsMove(vector<string> &map, vector<Robot> &rlist, Player &alex)
{
    for (int i = 0; i < rlist.size(); i++)
    {
        Robot &rb = rlist[i];
        if (rb.alive)
        {
            int xpos = alex.xpos;
            int ypos = alex.ypos;
            map[rb.ypos][rb.xpos] = ' ';

            //chooses best new pos for robot to reach player
            if (rb.xpos == xpos && rb.ypos < ypos)
            {
                rb.ypos++;
            }
            if (rb.xpos == xpos && rb.ypos > ypos)
            {
                rb.ypos--;
            }
            if (rb.xpos < xpos && rb.ypos == ypos)
            {
                rb.xpos++;
            }
            if (rb.xpos > xpos && rb.ypos == ypos)
            {
                rb.xpos--;
            }
            if (rb.xpos < xpos && rb.ypos < ypos)
            {
                rb.xpos++;
                rb.ypos++;
            }
            if (rb.xpos > xpos && rb.ypos < ypos)
            {
                rb.xpos--;
                rb.ypos++;
            }
            if (rb.xpos < xpos && rb.ypos > ypos)
            {
                rb.xpos++;
                rb.ypos--;
            }
            if (rb.xpos > xpos && rb.ypos > ypos)
            {
                rb.xpos--;
                rb.ypos--;
            }

            //evaluate robot's new pos
            safeRobotPos(map, rb, rlist, alex);
        }
    }
}

/*
Tests Player's movement to new position
@param &map vector that contains map
@param &alex Player Object
@return returns true if new pos is valid, false otherwise 
*/
bool SafePlayerPos(vector<string> &map, Player &alex)
{
    if (map[alex.ypos][alex.xpos] == '*' || map[alex.ypos][alex.xpos] == 'R')
    {
        map[alex.ypos][alex.xpos] = 'h';
        alex.alive = false;
        return true;
    }
    else if (map[alex.ypos][alex.xpos] == 'r')
    {
        return false;
    }
    else
    {
        map[alex.ypos][alex.xpos] = 'H';
        return true;
    }
}

/*
Makes Player move based on user's input
@param &map vector that contains map
@param &alex Player Object
@param move user's choice to move
@return true if player actually moved, false if a problem was raised
*/
bool playerMove(vector<string> &map, Player &alex, char move)
{
    //moves player
    int xcopy = alex.xpos;
    int ycopy = alex.ypos;

    move = (char)toupper(move);
    switch (move)
    {
    case 'Q':
        map[alex.ypos][alex.xpos] = ' ';
        --alex.ypos;
        --alex.xpos;
        break;
    case 'W':
        map[alex.ypos][alex.xpos] = ' ';
        --alex.ypos;
        break;
    case 'E':
        map[alex.ypos][alex.xpos] = ' ';
        --alex.ypos;
        ++alex.xpos;
        break;
    case 'A':
        map[alex.ypos][alex.xpos] = ' ';
        --alex.xpos;
        break;
    case 'S':
        //do nothing
        break;
    case 'D':
        map[alex.ypos][alex.xpos] = ' ';
        ++alex.xpos;
        break;
    case 'Z':
        map[alex.ypos][alex.xpos] = ' ';
        ++alex.ypos;
        --alex.xpos;
        break;
    case 'X':
        map[alex.ypos][alex.xpos] = ' ';
        ++alex.ypos;
        break;
    case 'C':
        map[alex.ypos][alex.xpos] = ' ';
        ++alex.ypos;
        ++alex.xpos;
        break;
    default:
        cout << "Invalid Input!" << endl
             << endl;
        return false;
        break;
    }
    if (!SafePlayerPos(map, alex))
    {
        //if new pos is already 'r', player stays inplace
        cout << "Invalid Position!" << endl
             << endl;
        alex.xpos = xcopy;
        alex.ypos = ycopy;
        map[alex.ypos][alex.xpos] = 'H';
        return false;
    }
    return true;
}

/*
Asks user for a map number and verifies its validity
@return number choosen by user or -1 if user entered CTRL-Z
*/
int askMapNum()
{
    int n;
    while (1)
    {
        cout << endl
             << "Please choose a number between 1-99 (0 to exit)" << endl
             << " > ";

        if ((cin >> n))
        {
            //raises error if more than a number is written by user
            if (!emptyCin())
            {
                cout << "Invalid Input!" << endl
                     << endl;
                continue;
            }
            if (validMapNum(n))
                return n;
            else
            {
                cout << "Map doesn't exist. Please choose a different one." << endl
                     << endl;
                continue;
            }
        }
        else
        {
            //deals with errors when trying to get the char
            if (cin.eof())
                return -1; // detects ctrlz
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl
                 << endl;
            continue;
        }
    }
}

/*
Prints to console the game rules
*/
void showRules()
{
    cout << endl
         << setfill('=') << setw(115) << "" << endl;
    cout << setfill(' ') << setw(63) << "INSTRUCTIONS" << endl;
    cout << setfill('=') << setw(115) << "" << endl;
    cout << "The player is placed in a maze made up of high-voltage fences and posts." << endl;
    cout << "There are also some interceptor robots that will try to destroy the player." << endl;
    cout << "If the player touches the maze or any of these robots, that is the end of the game (and the player!)." << endl;
    cout << "The robots are also destroyed when they touch the fences/posts or when they collide with each other." << endl;
    cout << "Every time the player moves in any direction (horizontally, vertically, or diagonally) to a contiguous cell, " << endl;
    cout << "each robot moves one cell closer to the new player's location, in whichever direction is the shortest path." << endl;
    cout << "The robots have no vision sensors but they have an accurate odour sensor that allows them to follow the player!" << endl;
    cout << "There is one hope: make the robots hit the maze or each other. If all of them are destroyed, the player wins." << endl;
    cout << "Use Q,W,E,A,S,D,Z,X,C Keys to move player. " << endl;
    cout << setfill('=') << setw(115) << "" << endl;
    cout << endl;
}

/*
Creates a menu that is presented to user when starting main program
asking which actions user wants
@return returns -1 if menu is interrupted by user entering CTRL-Z or the
        number of the map to play (choosed by user)
*/
int init_menu()
{
    char c;
    while (1)
    {
        //Start of MENU
        cout << "=================" << endl;
        cout << " Human vs Robot" << endl;
        cout << "=================" << endl;
        cout << "  1)  Rules" << endl;
        cout << "  2)  Play" << endl;
        cout << "  0)  Exit" << endl;
        cout << "================" << endl;
        cout << " > ";
        //End of MENU

        if ((cin >> c))
        {
            //raises error if more than 1 char is written by user
            if (!emptyCin())
            {
                cout << "Invalid Input!" << endl
                     << endl;
                continue;
            }
            //tests user's char
            if (c == '1')
            {
                showRules();
                continue;
            }
            else if (c == '2')
            {
                int n = askMapNum();
                // if map zero is picked, return to main menu
                if (n == 0)
                {
                    cout << endl;
                    continue;
                }
                else if (n == -1)
                {
                    //ctr-Z was pressed
                    return -1;
                }
                return n; // run game
            }
            else if (c == '0')
            {
                return -1;
            }
            else
            {
                cout << "Invalid Input!" << endl
                     << endl;
                continue;
            }
        }
        else
        {
            //deals with errors when trying to get the char
            if (cin.eof())
                return -1; // detects ctrlz
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl
                 << endl;
            continue;
        }
    }
}

#endif