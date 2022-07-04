//T07_G07
#include "Post.hpp"
#include "Consts.hpp"

using namespace std;

Post::Post(const int &x, const int &y, const bool &electrified) {
    this->x = x;
    this->y = y;
    this->electrified = electrified;
}

int Post::getX() {
    return this->x;
}

int Post::getY() {
    return this->y;
}

char Post::getChar() {
    if (this->isElectrified()) return POST_ELEC;
    else return POST_NONELEC;
}

bool Post::isElectrified() {
    return this->electrified;
}

void Post::setNotElectrified() {
    this->electrified = false;
}