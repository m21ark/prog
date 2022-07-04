//T07_G07
#pragma once

#include "Maze.hpp"

using namespace std;

class Player {
public:
    /**
     * @brief Construct a new Player object
     * 
     */
    Player();

    /**
     * @brief Sets Player::x and Player::y
     * 
     * @param x The to-be player's x position
     * @param y The to-be player's y position
     */
    void setPosition(int x, int y);

    /**
     * @brief Returns Player::x
     * 
     * @return int Player::x
     */
    int getX();

    /**
     * @brief Returns Player::y
     * 
     * @return int Player::y
     */
    int getY();

    /**
     * @brief Returns Player::alive
     * 
     * @return bool Player::alive
     */
    bool getStatus();

    /**
     * @brief Returns PLAYER_ALIVE if Player::alive is true, PLAYER_DEAD otherwise
     * 
     * @return char PLAYER_ALIVE or PLAYER_DEAD
     */
    char getChar();

    /**
     * @brief Sets Player::alive to false
     * 
     */
    void kill();

    /**
     * @brief Sets Player::alive to true
     * 
     */
    void resetStatus();

private:
    int x, y;
    bool alive = true;
};
