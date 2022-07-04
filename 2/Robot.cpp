//T07_G07
#include "Robot.hpp"
#include "Consts.hpp"

using namespace std;

Robot::Robot(int x, int y) {
    this->id = robotCounter;
    this->robotCounter++;
    this->x = x;
    this->y = y;
}

string Robot::getStatus() {
    return this->state;
}

int Robot::getId() {
    return this->id;
}

int Robot::getX() {
    return this->x;
}

int Robot::getY() {
    return this->y;
}

char Robot::getChar() {
    return this->symbol;
}

void Robot::setDead() {
    this->state = "dead";
    this->symbol = ROBOT_DEAD;
}

void Robot::setStuck() {
    this->state = "stuck";
    this->symbol = ROBOT_STUCK;
}

void Robot::changePosition(const int &dx, const int &dy) {
    this->x += dx;
    this->y += dy;
}

void Robot::resetRobotCounter() {
    robotCounter = 0;
}

bool Robot::operator==(Robot aRobot) {
    return this->id == aRobot.getId();
}
