//T07_G07
#pragma once

#include <iostream>

using namespace std;

class Post {
public:
    /**
     * @brief Construct a new Post object
     * 
     * @param x The to-be created post's X coordinate
     * @param y The to-be created post's Y coordinate
     * @param electrified true if the post is electrified, false otherwise
     */
    Post(const int &x, const int &y, const bool &electrified);

    /**
     * @brief Returns Post::x
     * 
     * @return int Post::x
     */
    int getX();

    /**
     * @brief Returns Post::y
     * 
     * @return int Post::y
     */
    int getY();

    /**
     * @brief Returns POST_ELEC if post.isElectrified, POST_NONELEC otherwise
     * 
     * @return char POST_ELEC or POST_NONELEC
     */
    char getChar();

    /**
     * @brief Sets Post::electrified to false
     * 
     */
    void setNotElectrified();

    /**
     * @brief Returns Post::electrified
     * 
     * @return bool Post::electrified
     */
    bool isElectrified();

private:
    int x, y;
    bool electrified;
};