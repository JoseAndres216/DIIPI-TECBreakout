#ifndef SERVERBREAKOUT_GAMEMANAGER_H
#define SERVERBREAKOUT_GAMEMANAGER_H

#include <iostream>
#include "../DataStructures/Matrix/Matrix.h"
#include "Player.h"
#include "Bar.h"
#include "Ball.h"
#include "../Socket/SocketServer.h"

using namespace std;

class GameManager {
private:
    Matrix matrix;
    Player player;
    Bar bar;
    Ball ball;
    SocketServer server;
    static GameManager *instance;


    GameManager() {
        //No se para que sirve el constructor con Singleton
    }

public:
    static GameManager *getInstance() {
        if (instance == 0) {
            instance = new GameManager();
        }

        return instance;
    }

    Matrix getMatrix(){
        return matrix;
    }

    void setMatrix(Matrix matrix) {
        GameManager::matrix = matrix;
    }

    void generateMatrix() {
        int y = 100;
        for(int i = 1; i<=6; i++){
            matrix.addRow();
            if(i == 1 or i == 2){
                for(int j = 1; j<=14; j++){
                    matrix.addElement(i, (j*100), y, 3);
                }
                y += 50;
            }else if(i == 3 or i == 4){
                for(int j = 1; j<=14; j++){
                    matrix.addElement(i, (j*100), y, 2);
                }
                y += 50;
            }else{
                for(int j = 1; j<=14; j++){
                    matrix.addElement(i, (j*100), y, 1);
                }
                y += 50;
            }
        }

    }
};

GameManager *GameManager::instance = 0;

#endif //SERVERBREAKOUT_GAMEMANAGER_H
