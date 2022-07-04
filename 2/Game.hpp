//T07_G07
#pragma once

#include "Robot.hpp"
#include "Consts.hpp"

using namespace std;

/**
 * @brief Struct used to easily store exit gates
 * 
 */
struct Pos {
    int x, y;
};

class Game {
public:
    /**
     * @brief Construct a new Game object
     * 
     */
    Game();

    /**
     * @brief Shows and handles the initial menu of the game
     * 
     */
    void menu();

    /**
     * @brief Asks the user for the number of the map he wishes to play / see winners
     * and handles bad input / errors
     */
    void askMapNum();

    /**
     * @brief Prints the rules of the game, read from a text file
     * 
     */
    void showRules();

    /**
     * @brief Using Game::mapNum sets Game::mapNameFile and Game::WinnersNameFile
     * 
     */
    void setFileName();

    /**
     * @brief In charge of keeping track of time
     * 
     * @return int Current time after first initialization
     */
    int timer();

    /**
     * @brief Asks the user if they want to play again, exits if CTRL+Z is detected
     * 
     * @return true When the user has decided to play again
     * @return false When the user has decided to not play again
     */
    bool AskPlayAgain();

    /**
     * @brief Asks the user for a name until a valid one is entered or they decide to quit (CTRL+Z)
     * 
     * @return string The winner's name
     */
    string askWinnerName();

    /**
     * @brief Triggers winning sequence (setting Game:: attributes to the correct values, like
     *  Game::won to true and Game::GameRunningStatus to false) and calls Game::writeNameToFile
     * 
     */
    void gameWin();

    /**
     * @brief "Resets" the timer so the timer works well when you retry to play the map after a loss
     * 
     * @param time The current time when this function is called, will serve as the new baseline
     */
    void playTimeUpdate(int time);

    /**
     * @brief Initializes / resets all the game's robots, maze (posts), player and exit gates
     * 
     */
    void boardStart();

    /**
     * @brief Moves the robots, checking for collisions with fences, other robots and players along the way
     * 
     */
    void robotsMove();

    /**
     * @brief prints the map to the screen, uses a blank map and then adds the robots, player, exit gates and posts one by one
     * 
     */
    void showMap();

    /**
     * @brief Displays a brief message to inform the player how many robots are still alive
     * 
     */
    void showRobotCount();

    /**
     * @brief Updates the number of robots still alive
     * 
     */
    void updateRobotCount();

    /**
     * @brief Checks if the robot that is trying to moving will collide with a robot that isn't moving
     * 
     * @param movingRobot The robot that is trying to move 
     */
    void checkRobotCollisions(Robot &movingRobot);

    /**
     * @brief Checks if the player will collide with a robot
     * 
     * @param x The x value to which the player is trying to move to
     * @param y The y value to which the player is trying to move to
     * @return short 1: There's a living robot there.   -1: There's a dead robot there.    0: There is no robot there
     */
    short checkPlayerRobotCollision(const int &x, const int &y);

    /**
     * @brief Moves the player if there's nothing on the way, sets the player dead if he collides
     * with an electric fence or a robot, doesn't do anything if there's a non-electric fence or a
     * dead/stuck robot in the way.
     * 
     * @param move One of QWEASDZXC.
     * @return true If it's needed to ask for another move (dead/stuck robot or non-electric post in the way).
     * @return false If it's not needed to ask for another move.
     */
    bool playerMove(const char &move);

    /**
     * @brief Get Game::GameRunningStatus
     * 
     * @return Game::GameRunningStatus
     */
    bool getGameRunningStatus();

    /**
     * @brief Checks if the player is at an exit gate, if yes calls Game::gameWin()
     * 
     */
    void checkWin();

    /**
     * @brief Get the Game::alex.getStatus()
     * 
     * @return Game::alex.getStatus()
     */
    bool getPlayerStatus();

    /**
     * @brief Resets player's attributes plus Game::GameRunningStatus and Game::won
     * 
     */
    void resetPlayerStatus();

    /**
     * @brief Creates and stores Game::aBlankMap
     * 
     */
    void setBlankMap();

private:
    int playTime = 0;
    int mapNum;
    int robotAliveCount;
    bool GameRunningStatus = true;
    string mapNameFile;
    string WinnersNameFile;
    Maze map;
    Player alex;
    bool won = false;
    vector <string> aBlankMap;
    vector <Robot> robotList;
    vector <Pos> exitGatesList;
};
