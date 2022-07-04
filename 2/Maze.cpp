//T07_G07
#include "Maze.hpp"

using namespace std;


Maze::Maze() {

}

int Maze::getHeight() {
    return this->colLen;
}

int Maze::getLength() {
    return this->rowLen;
}

void Maze::addPost(const int &x, const int &y, const bool &electrified) {
    Post temp(x, y, electrified);
    this->map.push_back(temp);
}

void Maze::removePost(const int &x, const int &y) {
    int idx = 0;
    for (Post &aPost : this->map) {
        if (aPost.getX() == x && aPost.getY() == y) {
            this->map.erase(map.begin() + idx);
        } else idx++;
    }
}

vector <Post> Maze::getMap() {
    return this->map;
}

short Maze::unelectrify(const int &x, const int &y) {
    for (Post &aPost : this->map) {
        if (aPost.getX() == x && aPost.getY() == y) {
            if (aPost.isElectrified()) {
                aPost.setNotElectrified();
                return 1;
            } else {
                return 0;
            }
        }
    }
    //If there was no collision with a post
    return -1;
}

void Maze::clearMap() {
    this->map.clear();
}

void Maze::setHeight(const int &y) {
    this->colLen = y;
}

void Maze::setWidth(const int &x) {
    this->rowLen = x;
}