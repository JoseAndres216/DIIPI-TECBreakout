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
        int internBlocksperRow = 2;
        int surpriseBlocksperRow = 3;
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
                if (y > 100) {
                    if((matrix.getElement(x, y-50)->getLinkedlist()->getElement(x, y-50)->getBlock()->getResistance()) != 0){
                        y = y - 50;
                        depth = true;
                    }
                }
            } else if (ball.getDepth() == 2) {
                if (y > 150) {
                    if((matrix.getElement(x, y-100)->getLinkedlist()->getElement(x, y-100)->getBlock()->getResistance()) != 0){
                        y = y - 100;
                        depth = true;
                    }
                }
                if (y == 150) {
                    if((matrix.getElement(x, y-50)->getLinkedlist()->getElement(x, y-50)->getBlock()->getResistance()) != 0){
                        y = y - 50;
                        depth = true;
                    }
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
                    this->surprise = "Bar Size+";
                    break;
                case 1:
                    bar.decreaseSize();
                    this->surprise = "Bar Size-";
                    break;
                case 2:
                    ball.setMovementChange("increase");
                    this->surprise = "Ball Speed+";
                    break;
                case 3:
                    ball.setMovementChange("decrease");
                    this->surprise = "Ball Speed-";
                    break;
                case 4:
                    player.increaseLives();
                    this->surprise = "Lives+";
                    break;
                case 5:
                    if (this->player.getLives() >= 2) {
                        player.decreaseLives();
                        this->surprise = "Lives-";
                    } else {
                        this->surprise = "Close One-";
                    }
                    break;
                case 6:
                    if ((player.getScore() > 305 and player.getScore() < 500) or
                        (player.getScore() > 805 and player.getScore() < 1000) or
                        (player.getScore() > 1305 and player.getScore() < 1500) or
                        (player.getScore() > 1805 and player.getScore() < 2000)) {
                        this->player.increaseLives();
                    }
                    player.increaseScore(200);
                    this->surprise = "200 Score+";
                    break;
                case 7:
                    if (this->player.getScore() >= 200) {
                        player.decreaseScore(200);
                        if ((player.getScore() > 505 and player.getScore() < 700) or
                            (player.getScore() > 1005 and player.getScore() < 1200) or
                            (player.getScore() > 1505 and player.getScore() < 1700) or
                            (player.getScore() > 2005 and player.getScore() < 2200)) {
                            this->player.decreaseLives();
                        }
                        this->surprise = "200 Score-";
                    } else {
                        this->surprise = "Close One-";
                    }
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

        if ((this->player.getScore() % 200) == 0 or (this->player.getScore() % 200) == 5) {
            bar.increaseSize();
            this->player.increaseScore(10);
        }

        if ((this->player.getScore() >= 500 and this->player.getScore() < 505) or
            (this->player.getScore() >= 1000 and this->player.getScore() < 1005) or
            (this->player.getScore() >= 1500 and this->player.getScore() < 1505) or
            (this->player.getScore() >= 2000 and this->player.getScore() < 2005)) {
            this->player.increaseLives();
            this->player.increaseScore(10);
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
