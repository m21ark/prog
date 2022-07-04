//T07_G07
#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;


/**
 * @brief Removes spaces in the beginning and end of string
 * 
 * @param s string to be strip
 */
void stripStr(string &s);


/**
 * @brief 
 * 
 * @return true empty buffer
 * @return false if there is something in buffer
 */
bool emptyCin();


/**
 * @brief Keeps track of how many seconds have passed since its first call
 * 
 * @return time_t Seconds since first call
 */
time_t timeElapsed();


/**
 * @brief Gets name from a line of the file "winners"
 * 
 * @param s 
 * @return string 
 */
string getName(const string &s);

/**
 * @brief Gets score from a line of the file "winners"
 * 
 * @param s string line which to extract number from
 * @return int extracted number/score 
 */
int getNum(const string &s);

/**
 * @brief Creates a vector with each line of a file
 * 
 * @param fileName  file which to extract from
 * @return vector <string> lines to be read from file
 */
vector <string> readFromFile(string fileName);

/**
 * @brief Given a file name, shows its contents (winners)
 * 
 * @param fileName string file name
 */
void showWinners(const string &fileName);

/**
 * @brief Sorts winners file vector based on score
 * 
 * @param v vector with the file lines to be sorted
 */
void sortNamesOrder(vector <string> &v);

/**
 * @brief Writes a new winner to file "winners"
 * 
 * @param fileName file where to write
 * @param name winner's name
 * @param score winner's time score
 */
void writeNameToFile(string fileName, string name, int score);

/**
 * @brief Verify if map number is valid by searching file names
 * 
 * @param n map number
 * @return true valid map
 * @return false invalid map
 */
bool validMapNum(int n);

/**
 * @brief Create a Blank String object, they'll be used in createBlankVector
 * 
 * @param n : the number of spaces the string should have
 * @return string : the string that was created
 */
string createBlankString(const int &n);

/**
 * @brief Create a Blank Vector object, useful for printing the map in Game::showMap()
 * 
 * @param n : The number of strings the vector should have
 * @param aString : The strings that the vector is composed of
 * @return vector<string> : The created vector object
 */
vector <string> createBlankVector(const int &n, const string &aString);