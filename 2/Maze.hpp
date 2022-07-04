//T07_G07
#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include "auxfuncs.hpp"
#include "Post.hpp"

using namespace std;

class Maze {
public:
    /**
     * @brief Construct a new Maze object
     * 
     */
    Maze();


    /**
     * @brief Sets Maze::colLen
     * 
     * @param y The number of rows (height) the board has
     */
    void setHeight(const int &y);

    /**
     * @brief Sets Maze::rowLen
     * 
     * @param x The number of columns (width) the board has
     */
    void setWidth(const int &x);

    /**
     * @brief Get Maze::colLen
     * 
     * @return int Maze::colLen
     */
    int getHeight();

    /**
     * @brief Get Maze::rowLen
     * 
     * @return int Maze::rowLen
     */
    int getLength();

    /**
     * @brief Get Maze::map
     * 
     * @return vector <Post> Maze::map
     */
    vector <Post> getMap();

    /**
     * @brief Creates and stores a post in Maze::map 
     * 
     * @param x Post's X coordinate
     * @param y Post's Y coordinate
     * @param electrified true if the post is electrified, false if otherwise 
     */
    void addPost(const int &x, const int &y, const bool &electrified);

    /**
     * @brief Deletes a post from Maze::map
     * 
     * @param x The to-be deleted post's X coordinate
     * @param y The to-be deleted post's Y coordinate
     */
    void removePost(const int &x, const int &y);

    /**
     * @brief Does Maze::map.clear(), acts as a reset once the user decides to play again after a loss
     * 
     */
    void clearMap();

    /**
     * @brief This function is called during a robot or a player move. It checks whether or not the
     * move is going to collide with a fence and changes the post's state if it does indeed collide
     * with an electrified post. Returns a short int based on what happened
     * 
     * @param x The move's X coordinate
     * @param y The move's Y coordinate
     * @return short 1: Collision with an electrified post. 0: Collision with a non electrified post.
     * -1: No collision with any posts.
     */
    short unelectrify(const int &x, const int &y);

private:
    int rowLen, colLen;
    vector <Post> map;
};