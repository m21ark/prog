//T07_G07
#include "Game.hpp"
#include "Consts.hpp"

using namespace std;

Game::Game() {

}

bool Game::getPlayerStatus() {
    return this->alex.getStatus();
}

void Game::resetPlayerStatus() {
    this->alex.resetStatus();
    this->won = false;
    this->GameRunningStatus = true;
}

void Game::boardStart() {
    this->map.clearMap();
    this->robotList.clear();
    this->exitGatesList.clear();
    Robot::resetRobotCounter();
    ifstream file(this->mapNameFile);
    string aLine;

    int height, width;
    getline(file, aLine);
    stringstream oneLiner(aLine);
    char sep;
    oneLiner >> height >> sep >> width;
    this->map.setHeight(height);
    this->map.setWidth(width);
    this->setBlankMap();
    int row = 0, col = 0;
    while (getline(file, aLine)) {
        for (char aChar : aLine) {
            //switch doesn't allow for duplicate values, so it won't let me use "OR"s if
            //the consts are default values...
            if (aChar == '\r') {
                continue;
            }
            if (aChar == ROBOT_ALIVE || aChar == 'R') {
                Robot temp(row, col);
                this->robotList.push_back(temp);
            } else if (aChar == PLAYER_ALIVE || aChar == 'H') {
                this->alex.setPosition(row, col);
            } else if (aChar == EXIT_GATE || aChar == 'O') // this is a capital 'o'
            {
                Pos temp;
                temp.x = row;
                temp.y = col;
                this->exitGatesList.push_back(temp);
            } else if (aChar == POST_ELEC || aChar == '*') {
                this->map.addPost(row, col, true);
            } else if (aChar == POST_NONELEC || aChar == '+') {
                this->map.addPost(row, col, false);
            }
            row++;
        }
        col++;
        row = 0;
    }

    file.close();
}

void Game::checkRobotCollisions(Robot &movingRobot) {
    for (Robot &staticRobot : this->robotList) {
        if (!(movingRobot == staticRobot) && (movingRobot.getX() == staticRobot.getX()) &&
            (movingRobot.getY() == staticRobot.getY())) {
            movingRobot.setStuck();
            staticRobot.setStuck();
        }
    }
}

void Game::robotsMove() {
    if (!this->won && this->alex.getStatus()) {
        for (auto &aRobot : this->robotList)
            if (aRobot.getStatus() == "alive") {
                int dx, dy;
                if (this->alex.getX() > aRobot.getX())
                    dx = 1;
                else if (this->alex.getX() < aRobot.getX())
                    dx = -1;
                else
                    dx = 0;
                if (this->alex.getY() > aRobot.getY())
                    dy = 1;
                else if (this->alex.getY() < aRobot.getY())
                    dy = -1;
                else
                    dy = 0;
                short action = this->map.unelectrify(aRobot.getX() + dx, aRobot.getY() + dy);
                if (action == 1) {
                    aRobot.setDead();
                } else if (action == 0) {
                    aRobot.changePosition(dx, dy);
                    aRobot.setStuck();
                    this->map.removePost(aRobot.getX(), aRobot.getY());
                } else {

                    if (aRobot.getX() + dx == alex.getX() && aRobot.getY() + dy == alex.getY()) {
                        this->alex.kill();
                        this->GameRunningStatus = false;
                        this->won = false;
                        return;
                    } else {
                        aRobot.changePosition(dx, dy);
                        this->checkRobotCollisions(aRobot);
                    }
                }
            }
    }
}

short Game::checkPlayerRobotCollision(const int &x, const int &y) {
    for (Robot aRobot : this->robotList) {
        if (aRobot.getX() == x && aRobot.getY() == y) {
            if (aRobot.getStatus() == "alive") {
                return 1;
            } else {
                return -1;
            }
        }
    }
    return 0;
}

bool Game::playerMove(const char &move) {
    short dx, dy;
    switch (move) {
        case 'q':
            dx = -1;
            dy = -1;
            break;
        case 'w':
            dx = 0;
            dy = -1;
            break;
        case 'e':
            dx = 1;
            dy = -1;
            break;
        case 'a':
            dx = -1;
            dy = 0;
            break;
        case 's':
            dx = 0;
            dy = 0;
            break;
        case 'd':
            dx = 1;
            dy = 0;
            break;
        case 'z':
            dx = -1;
            dy = 1;
            break;
        case 'x':
            dx = 0;
            dy = 1;
            break;
        case 'c':
            dx = 1;
            dy = 1;
            break;
    }
    //return 1 if there's a robot alive, -1 if there's a dead robot, 0 if there is no robot
    short robotCollision = this->checkPlayerRobotCollision(alex.getX() + dx, alex.getY() + dy);
    if (robotCollision == 1) {
        this->alex.kill();
        this->GameRunningStatus = false;
        this->won = false;
        return false;
    } else if (robotCollision == -1) {
        return true;
    } else {
        short fenceCollision = this->map.unelectrify(alex.getX() + dx, alex.getY() + dy);
        if (fenceCollision == 1) {
            //collision with electrified post
            this->alex.kill();
            this->GameRunningStatus = false;
            this->won = false;
            return false;
        } else if (fenceCollision == 0) {
            //collision with non-electrified post
            return true;
        } else if (fenceCollision == -1) {
            //no object in new pos
            this->alex.setPosition(alex.getX() + dx, alex.getY() + dy);
            return false;
        }
    }
    return false;
}

void Game::playTimeUpdate(int time) {
    playTime = time;
}

void Game::gameWin() {
    this->won = true;
    this->GameRunningStatus = false;
    int currentTime = Game::timer() - playTime;
    this->showMap();
    cout << "You won in " << currentTime << "s!" << endl;
    writeNameToFile(WinnersNameFile, Game::askWinnerName(), currentTime);
}

void Game::setBlankMap() {
    string blankString = createBlankString(this->map.getLength());
    vector <string> blankMap = createBlankVector(this->map.getHeight(), blankString);
    this->aBlankMap = blankMap;
}

string Game::askWinnerName() {
    while (1) {
        //asks name
        string s = "";
        string s2 = "";
        char c = ' ';
        cout << endl
             << "Please insert your name: \n"
             << " > ";
        getline(cin, s2);
        stripStr(s2);
        if (cin.fail() && cin.eof())
            exit(1); // detects CTRL+Z

        //test if empty name has been chosen
        if (s2.size() == 0) {
            cout << "Empty name not allowed!" << endl;
            continue;
        }

        //reduce to 15 char if needed
        if (s2.size() <= 15) {
            s = s2;
        } else
            for (int i = 0; i < 15; i++)
                s += s2[i];
        stripStr(s);

        //stops user from using '-' as a character
        bool invalidChar = false;
        for (char ch : s)
            if (ch == '-') {
                cout << "You can't use \"-\" in your name!" << endl;
                invalidChar = true;
                break;
            }
        if (invalidChar)
            continue;

        //confirms name
        cout << "Is '" << s << "' the name you want? (Y/N)" << endl
             << " > ";
        if ((cin >> c)) {
            //raises error if more than 1 char is written by user
            if (!emptyCin()) {
                cout << "Invalid Input!" << endl;
                continue;
            }
            //tests user's answer
            if (c == 'y' || c == 'Y') {
                return s;
            } else if (c == 'N' || c == 'n')
                continue;
            else {
                cout << "Invalid Input!" << endl;
                continue;
            }
        } else {
            //deals with errors when trying to get the char
            if (cin.fail() && cin.eof())
                exit(1); // detects CTRL+Z
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Choose Y/N" << endl;
            continue;
        }
    }
}

bool Game::AskPlayAgain() {
    while (1) {
        //asks if the player wants to play again
        char c;
        cout << "Do you want to play again? (Y/N)" << endl
             << " > ";
        if ((cin >> c)) {
            //raises error if more than 1 char is written by user
            if (!emptyCin()) {
                cout << "Invalid Input! Choose Y/N" << endl
                     << endl;
                continue;
            }
            //tests user's char
            if (c == 'y' || c == 'Y')
                return true;
            else if (c == 'N' || c == 'n')
                return false;
            else {
                cout << "Invalid Input! Choose Y/N" << endl
                     << endl;
                continue;
            }
        } else {
            //deals with errors when trying to get the char
            if (cin.eof())
                exit(1); // detects CTRL+Z
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Choose Y/N" << endl
                 << endl;
            continue;
        }
    }
}

int Game::timer() {
    return timeElapsed();
}

void Game::setFileName() {
    if (this->mapNum < 10) {
        this->mapNameFile = "MAZE_0" + to_string(this->mapNum) + ".TXT";
        this->WinnersNameFile = "MAZE_0" + to_string(this->mapNum) + "_WINNERS" + ".TXT";
    } else {
        this->mapNameFile = "MAZE_" + to_string(this->mapNum) + ".TXT";
        this->WinnersNameFile = "MAZE_" + to_string(this->mapNum) + "_WINNERS" + ".TXT";
    }
}

void Game::showMap() {
    //reset blankMap to the default that was initialized in the beginning of the program, has the desired proportions
    vector <string> blankMap = this->aBlankMap;
    //one by one add all elements of the game to the blankMap, completing it
    for (const auto &anExitGate : exitGatesList) {
        blankMap[anExitGate.y][anExitGate.x] = EXIT_GATE;
    }

    for (Robot &aRobot : this->robotList) {
        blankMap[aRobot.getY()][aRobot.getX()] = aRobot.getChar();
    }

    for (Post &aPost : this->map.getMap()) {
        blankMap[aPost.getY()][aPost.getX()] = aPost.getChar();
    }

    blankMap[alex.getY()][alex.getX()] = alex.getChar();
    //print the now completed map
    for (const auto &line : blankMap) {
        cout << line << endl;
    }
}

void Game::showRobotCount() {
    printf("%d/%d robots alive\n", robotAliveCount, (int)robotList.size());
}

void Game::updateRobotCount() {
    this->robotAliveCount = 0;
    //increment by one for each robot that is alive
    for (Robot &aRobot : this->robotList) {
        if (aRobot.getStatus() == "alive")
            this->robotAliveCount++;
    }
}

bool Game::getGameRunningStatus() {
    return this->GameRunningStatus;
}

void Game::showRules() {
    cout << endl
         << setfill('=') << setw(120) << "";
    cout << setfill(' ') << setw(68) << "INSTRUCTIONS" << endl;
    cout << setfill('=') << setw(120) << "" << endl;

    //get the rules from the .txt file and print them
    ifstream file("RULES.TXT");
    string line;

    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();

    cout << setfill('=') << setw(120) << "" << endl
         << endl;
}

void Game::askMapNum() {
    int n;
    //asks the user for a number until the users enters a valid one or decides to quit
    while (1) {
        cout << endl
             << "Please choose a map number between 1-99 (0 to exit)" << endl
             << " > ";

        if ((cin >> n)) {
            //raises error if more than a number is written by user
            if (!emptyCin()) {
                cout << "Invalid Input!" << endl
                     << endl;
                continue;
            }
            //sets the attribute to the correct value and quits
            if (validMapNum(n)) {
                this->mapNum = n;
                return;
            } else {
                cout << "Map doesn't exist. Please choose a different one." << endl
                     << endl;
                continue;
            }
        } else {
            //deals with errors when trying to get the char
            if (cin.eof())
                exit(1); // detects CTRL+Z
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl
                 << endl;
            continue;
        }
    }
}

void Game::checkWin() {
    for (Pos exitGate : this->exitGatesList) {
        //one by one checks if the player has the same position as one of the exit gates
        if (this->alex.getX() == exitGate.x && this->alex.getY() == exitGate.y) {
            this->gameWin();
        }
    }
}

void Game::menu() {
    char c;
    while (1) {
        //Start of MENU
        cout << "=================" << endl;
        cout << " Human vs Robot" << endl;
        cout << "=================" << endl;
        cout << "  1)  Rules" << endl;
        cout << "  2)  Play" << endl;
        cout << "  3)  Winners" << endl;
        cout << "  0)  Exit" << endl;
        cout << "================" << endl;
        cout << " > ";
        //End of MENU

        if ((cin >> c)) {
            //raises error if more than 1 char is written by user
            if (!emptyCin()) {
                cout << "Invalid Input!" << endl
                     << endl;
                continue;
            }
            //tests user's char
            if (c == '1') {
                Game::showRules();
                continue;
            } else if (c == '3') {
                //Show Winners
                askMapNum();
                setFileName();
                vector <string> file = readFromFile(WinnersNameFile);

                //readFromFile returns {"No winners yet!"} if the reading of the file fails
                if (file.size() == 1 && file[0] == "No winners yet!") {
                    //quit to main menu if the number the user chose is 0
                    if (mapNum == 0) {
                        cout << endl;
                        continue;
                    } else {
                        cout << endl << "There aren't any winners for that map yet!" << endl << endl;
                    }
                }
                    //the file already exists
                else {
                    cout << endl
                         << setfill(' ') << left << setw(15) << "Player "
                         << " - Time" << endl;
                    cout << "----------------------" << endl;

                    for (auto line : file) {
                        cout << line << endl;
                    }
                    cout << endl;
                    continue;
                }
            } else if (c == '2') {
                this->askMapNum();
                // if map zero is picked, return to main menu
                if (this->mapNum == 0) {
                    cout << endl;
                    continue;
                }
                    // run game
                else {
                    this->setFileName();
                    return;
                }
            } else if (c == '0') {
                exit(1);
            } else {
                cout << "Invalid Input!" << endl
                     << endl;
                continue;
            }
        } else {
            //deals with errors when trying to get the char
            if (cin.eof()) {
                exit(1); //detects CTRL+Z
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl
                 << endl;
            continue;
        }
    }
}