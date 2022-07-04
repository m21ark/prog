// T07_G07 
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include "auxfuncs.hpp"
#include "gamefuncs.hpp"

using namespace std;

/*This function is the core of the game dealing with showing map, 
  asking player their move and computing all game logic
@param map,alex, rlist are the gamemap vector, alex (player),robot list with their stats
@return true if win and false if lost
*/
bool mainGame(vector<string> &map, Player &alex, vector<Robot> &rlist)
{
    string restInput;
    printf("%d/%d robots alive", rlist.size(), rlist.size());
    cout << " > ";

    char Playerdirection;
    while (true)
    {
        if (cin >> Playerdirection)
        {
            if (!emptyCin())
            {
                //if there are more things in buffer
                cout << endl
                     << "Invalid Input!" << endl
                     << endl;
                showMap(map);
            }
            else
            {
                //run normally
                cout << endl;
                //player tries to move, then checks if it is still alive and if so, robots move
                if (playerMove(map, alex, Playerdirection))
                    if (alex.alive)
                        robotsMove(map, rlist, alex);
                showMap(map);
            }
        }
        else
        {
            //deals with errors when trying to get the char
            if (cin.eof())
                exit(1); // detects ctrlz
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Move!" << endl;
            continue;
        }

        //detect lost
        if (!(alex.alive))
            return false;

        //detect win
        int t = 0;
        for (Robot r : rlist)
            if (r.alive)
                t++;
        if (t == 0)
            return true;
        printf("%d/%d robots alive", t, rlist.size());
        cout << " > ";
    }
}

int main()
{
    cout << endl;

    //keps track of time between in-game tries
    int TimeScoreAttempt = 0;

    //prompts menu to user and gets the files where game and scores are stored
    int menu = init_menu();
    if (menu == -1)
    {
        return 0;
    }

    string MAP_NAME, MAP_WINNERS;
    if (menu < 10)
    {
        MAP_NAME = "MAZE_0" + to_string(menu) + ".TXT";
        MAP_WINNERS = "MAZE_0" + to_string(menu) + "_WINNERS" + ".TXT";
    }
    else
    {
        MAP_NAME = "MAZE_" + to_string(menu) + ".TXT";
        MAP_WINNERS = "MAZE_" + to_string(menu) + "_WINNERS" + ".TXT";
    }

    timeElapsed(); //start timer
    while (1)
    {
        //initialization of core variables
        vector<string> map = loadMap(MAP_NAME);
        Player alex; //the player object is alex
        vector<Robot> robotList;
        findPlayer(map, alex.xpos, alex.ypos);
        findRobots(map, robotList);
        cout << endl
             << endl;
        showMap(map);
        int playerStatus = mainGame(map, alex, robotList);

        if (playerStatus)
        {
            //the win time is de difference of total time and time spent in losses
            int winTime = timeElapsed() - TimeScoreAttempt;
            cout << "You won in " << winTime << "s!" << endl;
            string PlayerName = askWinnerName();

            //writes score to file and shows score table to user
            writeNameToFile(MAP_WINNERS, PlayerName, winTime);
            break;
        }
        else
        {
            //Asks player if he wants to play again
            char c;
            cout << "You died!" << endl;
            if (!AskPlayAgain())
                exit(1);

            //if user wants to play again store current time spent
            TimeScoreAttempt = timeElapsed();
        }
    }
    getchar(); //prevents cmd closing after end of program
}

