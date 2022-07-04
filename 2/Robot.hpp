//T07_G07
#pragma once

#include "Player.hpp"
#include "Consts.hpp"

using namespace std;

class Robot {
public:
    /**
     * @brief Construct a new Robot object
     * 
     * @param x The to-be created robot's X coordinate
     * @param y The to-be created robot's Y coordinate
     */
    Robot(int x, int y);

    /**
     * @brief Returns Robot::state
     * 
     * @return string Robot::state
     */
    string getStatus();

    /**
     * @brief Returns Robot::id
     * 
     * @return int Robot::id
     */
    int getId();

    /**
     * @brief Returns Robot::x
     * 
     * @return int Robot::x
     */
    int getX();

    /**
     * @brief Returns Robot::y
     * 
     * @return int Robot::y
     */
    int getY();

    /**
     * @brief Returns Robot::symbol
     * 
     * @return char Robot::symbol
     */
    char getChar();

    /**
     * @brief Sets Robot::state to "dead" and Robot::symbol to ROBOT_DEAD
     * 
     */
    void setDead();

    /**
     * @brief Sets Robot::state to "stuck" and Robot::symbol to ROBOT_STUCK
     * 
     */
    void setStuck();

    /**
     * @brief Increments Robot::x by dx and Robot::y by dy
     * 
     * @param dx How much the robot's x coordinate will change (-1, 0 or 1)
     * @param dy How much the robot's y coordinate will change (-1, 0 or 1)
     */
    void changePosition(const int &dx, const int &dy);

    /**
     * @brief Returns true if both robots have the same id, false if not
     * 
     * @param aRobot One robot
     * @return true If their ID's are the same
     * @return false If their ID's are not the same
     */
    bool operator==(Robot aRobot);

    /**
     * @brief Sets Robot::robotCounter to 0
     * 
     */
    static void resetRobotCounter();


private:
    int x, y, id;
    static int robotCounter;
    char symbol = ROBOT_ALIVE;
    string state = "alive";

};

