//T07_G07
#include "Game.hpp"
#include <ctype.h>
#include "Consts.hpp"

using namespace std;

int Robot::robotCounter = 0;


int main() {
    Game game;
    game.menu();
    char playerDirection;
    game.timer();
    while (true) {
        game.boardStart();
        bool showMapVar = true;
        while (game.getGameRunningStatus()) {
            if (showMapVar) {
                cout << endl;
                game.showMap();
                game.updateRobotCount();
                game.showRobotCount();
                cout << " > ";
            } else {
                showMapVar = true;
            }

            if (cin >> playerDirection) {
                if (!emptyCin()) {
                    //if there are more things in buffer
                    cout << "\nInvalid Input!\n";
                    showMapVar = true;
                    continue;
                } else {
                    //run normally
                    cout << endl;
                    playerDirection = tolower(playerDirection);
                    if (playerDirection == 'q' || playerDirection == 'w' || playerDirection == 'e' ||
                        playerDirection == 'a' || playerDirection == 's' || playerDirection == 'd' ||
                        playerDirection == 'z' || playerDirection == 'x' || playerDirection == 'c') {
                        if (game.playerMove(playerDirection)) {
                            cout << "Not a valid move, there's a dead robot or a non-electrified fence in the way!\n";
                            showMapVar = true;
                            continue;
                        } else {
                            game.checkWin();
                            game.robotsMove();

                        }
                    } else if (playerDirection == 'p') exit(1);
                    else {
                        cout
                                << "Not a valid move.\nQ E Z C to move diagonally (up-left, up-right, down-left, down-right respectively)\nW A D X to move in a straight line (up, left, right or down respectively)\nor s to stay still\nControl+Z or p to quit."
                                << endl;
                        showMapVar = true;
                        continue;
                    }
                }
            } else {
                //deals with errors when trying to get the char
                if (cin.eof())
                    exit(1); // detects CTRL+Z
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Move!" << endl;
                showMapVar = false;
                continue;
            }
        }
        if (!game.getPlayerStatus() && game.getGameRunningStatus() != 1) {
            game.showMap();
            cout << "You lost!\n"
                 << endl;
            if (game.AskPlayAgain()) {
                game.playTimeUpdate(game.timer());
                game.resetPlayerStatus();
                continue;
            } else {
                exit(1);
            }
        } else
            break;

    }
    getchar();
}