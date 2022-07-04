//T07_G07
#include "Player.hpp"
#include "Consts.hpp"

using namespace std;


Player::Player() {}


void Player::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Player::getX() {
    return this->x;
}

int Player::getY() {
    return this->y;
}

bool Player::getStatus() {
    return this->alive;
}

char Player::getChar() {
    if (this->alive) return PLAYER_ALIVE;
    else return PLAYER_DEAD;
}

void Player::kill() {
    alive = false;
}

void Player::resetStatus() {
    alive = true;
}
