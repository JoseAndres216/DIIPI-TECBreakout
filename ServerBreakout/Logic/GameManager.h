#ifndef SERVERBREAKOUT_GAMEMANAGER_H
#define SERVERBREAKOUT_GAMEMANAGER_H

#include <iostream>
#include "../DataStructures/Matrix/Matrix.h"
#include "Player.h"
#include "Bar.h"
#include "Ball.h"
#include "../Socket/SocketServer.h"
#include "../DataStructures/Node.h"
#include <time.h>
#include <stdio.h>

using namespace std;

/**
 * @class This class is in charge for manage all the logic associated this the game.
 */
class GameManager {

private:

    Bar bar;
    Ball ball;
    Matrix matrix;
    Player player;
    string surprise = "";
    static GameManager *instance;

    /**
     * @brief Class constructor.
     */
    GameManager() {}

    /**
     * @brief Generates matrix based on given quantities.
     */
    void generateMatrix() {
        int internBlocksperRow = 1;
        int surpriseBlocksperRow = 2;
        int y = 100;
        for (int i = 1; i <= 6; i++) {
            matrix.addRow();
            if (i == 1 or i == 2) {
                for (int j = 0; j <= 15; j++) {
                    matrix.addElement(i, (j * 100), y, 3);
                }
                for (int j = 0; j < surpriseBlocksperRow; j++) {
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if (aux->getBlock()->getType() == 3) {
                        aux->getBlock()->setType(4);
                        aux->getBlock()->setResistance(1);
                    } else {
                        j--;
                    }
                }
                for (int j = 0; j < internBlocksperRow; j++) {
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if (aux->getBlock()->getType() == 3) {
                        aux->getBlock()->setType(5);
                        aux->getBlock()->setResistance(1);
                    } else {
                        j--;
                    }
                }
                y += 50;
            } else if (i == 3 or i == 4) {
                for (int j = 0; j <= 15; j++) {
                    matrix.addElement(i, (j * 100), y, 2);
                }

                for (int j = 0; j < surpriseBlocksperRow; j++) {
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if (aux->getBlock()->getType() == 2) {
                        aux->getBlock()->setType(4);
                        aux->getBlock()->setResistance(1);
                    } else {
                        j--;
                    }
                }
                for (int j = 0; j < internBlocksperRow; j++) {
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if (aux->getBlock()->getType() == 2) {
                        aux->getBlock()->setType(5);
                        aux->getBlock()->setResistance(1);
                    } else {
                        j--;
                    }
                }
                y += 50;
            } else {
                for (int j = 0; j <= 15; j++) {
                    matrix.addElement(i, (j * 100), y, 1);
                }
                matrix.getTail()->getLinkedlist()->getHead()->getBlock()->setType(6);
                matrix.getTail()->getLinkedlist()->getTail()->getBlock()->setType(6);
                for (int j = 0; j < surpriseBlocksperRow; j++) {
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if (aux->getBlock()->getType() == 1) {
                        aux->getBlock()->setType(4);
                        aux->getBlock()->setResistance(1);
                    } else {
                        j--;
                    }
                }
                if (i == 5) {
                    for (int j = 0; j < internBlocksperRow; j++) {
                        Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                        if (aux->getBlock()->getType() == 1) {
                            aux->getBlock()->setType(5);
                            aux->getBlock()->setResistance(1);
                        } else {
                            j--;
                        }
                    }
                }
                y += 50;
            }
        }
    }

public:

    /**
     * @brief Function to get the unique instance of the class GameManager.
     * @return GameManager
     */
    static GameManager *getInstance() {
        if (instance == 0) {
            instance = new GameManager();
        }

        return instance;
    }

    Matrix getMatrix() {
        return matrix;
    }

    /**
     * @brief Function made for get access to the generateMatrix Function.
     */
    void initializeComponents() {
        this->generateMatrix();
    }

    const Player getPlayer() const {
        return player;
    }

    void setPlayer(const Player &player) {
        this->player = player;
    }

    const string getSurprise() const {
        return surprise;
    }

    void setSurprise(const string &surprise) {
        this->surprise = surprise;
    }

    const Bar getBar() const {
        return bar;
    }

    void setBar(const Bar &bar) {
        this->bar = bar;
    }

    const Ball getBall() const {
        return ball;
    }

    void setBall(const Ball &ball) {
        this->ball = ball;
    }

    void collideBlock(int x, int y) {
        bool depth = false;

        if (ball.getDepth() > 0) {
            if (ball.getDepth() == 1) {
                if (y != 50) {
                    y = y - 50;
                    depth = true;
                }
            } else if (ball.getDepth() == 2) {
                if (y != 50 and y != 100) {
                    y = y - 100;
                    depth = true;
                }
                if (y == 100) {
                    y = y - 50;
                    depth = true;
                }
            }
        }

        if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 1) {
            player.increaseScore(10);
            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 2 and
                   (matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getResistance()) == 2) {
            player.increaseScore(5);
            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 2 and
                   (matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getResistance()) == 1) {
            player.increaseScore(10);
            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 3 and
                   (matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getResistance()) == 3) {
            player.increaseScore(5);
            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 3 and
                   (matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getResistance()) == 2) {
            player.increaseScore(5);
            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 3 and
                   (matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getResistance()) == 1) {
            player.increaseScore(10);
            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 4) {
            srand(time(NULL));
            int surprise = rand() % 8;

            switch (surprise) {
                case 0:
                    bar.increaseSize();
                    this->surprise = "Bar Size (+)";
                    break;
                case 1:
                    bar.decreaseSize();
                    this->surprise = "Increase Size";
                    break;
                case 2:
                    ball.setMovementChange("increase");
                    this->surprise = "Increase Speed";
                    break;
                case 3:
                    ball.setMovementChange("decrease");
                    this->surprise = "Decrease Speed";
                    break;
                case 4:
                    player.increaseLives();
                    this->surprise = "Lives (+1)";
                    break;
                case 5:
                    player.decreaseLives();
                    this->surprise = "Lives (-1)";
                    break;
                case 6:
                    player.increaseScore(200);
                    this->surprise = "Score (+200)";
                    break;
                case 7:
                    player.decreaseScore(200);
                    this->surprise = "Score (-200)";
                    break;
            }

            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 5) {
            if (depth) {
                player.increaseScore(30);
            } else {
                player.increaseScore(10);
            }
            ball.setDepth(0);
        } else if ((matrix.getElement(x, y)->getLinkedlist()->getElement(x, y)->getBlock()->getType()) == 6) {
            ball.increaseDepth();
        }

        if ((this->player.getScore() % 100) == 0 or (this->player.getScore() % 100) == 5) {
            bar.increaseSize();
        }

        if ((this->player.getScore() >= 500 and this->player.getScore() < 505) or
            (this->player.getScore() >= 1000 and this->player.getScore() < 1005)){
            this->player.increaseLives();
        }

        matrix.deleteElement(x, y);
    }

    void ballFall() {
        player.decreaseLives();
        bar.decreaseSize();
        ball.resetDepth();
    }

    void resetBallMovement() {
        ball.setMovementChange("");
    }

};

GameManager *GameManager::instance = 0;


#endif //SERVERBREAKOUT_GAMEMANAGER_H
