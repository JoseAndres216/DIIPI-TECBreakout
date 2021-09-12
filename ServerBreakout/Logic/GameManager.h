#ifndef SERVERBREAKOUT_GAMEMANAGER_H
#define SERVERBREAKOUT_GAMEMANAGER_H

#include <iostream>
#include "../DataStructures/Matrix/Matrix.h"
#include "Player.h"
#include "Bar.h"
#include "Ball.h"

using namespace std;

class GameManager {
private:
    Matrix matrix;
    Player player;
    Bar bar;
    Ball ball;
    static GameManager *instance;

    GameManager() {
        //Asignacion de valores
    }

public:
    static GameManager *getInstance() {
        if (instance == 0) {
            instance = new GameManager();
        }

        return instance;
    }

    void generateMatrix() {
        cout << "Se genera la matriz!";
    }
};

GameManager *GameManager::instance = 0;

#endif //SERVERBREAKOUT_GAMEMANAGER_H
