#ifndef SERVERBREAKOUT_GAMEMANAGER_H
#define SERVERBREAKOUT_GAMEMANAGER_H

#include <iostream>
#include "../DataStructures/Matrix/Matrix.h"
#include "Player.h"
#include "Bar.h"
#include "Ball.h"
#include "../Socket/SocketServer.h"
#include "../DataStructures/Node.h"

using namespace std;

class GameManager {
private:
    Matrix matrix;
    Player player;
    Bar bar;
    Ball ball;
    static GameManager *instance;

    GameManager() {
        //No se para que sirve el constructor con Singleton
    }

    /**
     * @brief generates matrix based on given quantities.
     */
    void generateMatrix() {
        int internBlocksperRow = 1;
        int surpriseBlocksperRow = 2;
        int y = 100;
        for (int i = 1; i <= 6; i++) {
            matrix.addRow();
            if (i == 1 or i == 2) {
                for (int j = 1; j <= 14; j++) {
                    matrix.addElement(i, (j * 100), y, 3);
                }
                for(int j = 0; j < surpriseBlocksperRow; j++){
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if(aux->getBlock()->getType() == 3){
                        aux->getBlock()->setType(4);
                    }else{
                        j--;
                    }
                }
                for(int j = 0; j < internBlocksperRow; j++){
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if(aux->getBlock()->getType() == 3){
                        aux->getBlock()->setType(5);
                    }else{
                        j--;
                    }
                }
                y += 50;
            } else if (i == 3 or i == 4) {
                for (int j = 1; j <= 14; j++) {
                    matrix.addElement(i, (j * 100), y, 2);
                }

                for(int j = 0; j < surpriseBlocksperRow; j++){
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if(aux->getBlock()->getType() == 2){
                        aux->getBlock()->setType(4);
                    }else{
                        j--;
                    }
                }
                for(int j = 0; j < internBlocksperRow; j++){
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if(aux->getBlock()->getType() == 2){
                        aux->getBlock()->setType(5);
                    }else{
                        j--;
                    }
                }
                y += 50;
            } else {
                for (int j = 1; j <= 14; j++) {
                    matrix.addElement(i, (j * 100), y, 1);
                }
                matrix.getTail()->getLinkedlist()->getHead()->getBlock()->setType(6);
                matrix.getTail()->getLinkedlist()->getTail()->getBlock()->setType(6);
                for(int j = 0; j < surpriseBlocksperRow; j++){
                    Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                    if(aux->getBlock()->getType() == 1){
                        aux->getBlock()->setType(4);
                    }else{
                        j--;
                    }
                }
                if(i == 5){
                    for(int j = 0; j < internBlocksperRow; j++){
                        Node *aux = matrix.getTail()->getLinkedlist()->getRandom();
                        if(aux->getBlock()->getType() == 1){
                            aux->getBlock()->setType(5);
                        }else{
                            j--;
                        }
                    }
                }
                y += 50;
            }
        }
    }

public:
    static GameManager *getInstance() {
        if (instance == 0) {
            instance = new GameManager();
        }

        return instance;
    }

    Matrix getMatrix() {
        return matrix;
    }

    void initializeComponents(){
        this->generateMatrix();
        //Se etablecen los datos del jugador provenientes del socket
    }
};

GameManager *GameManager::instance = 0;

#endif //SERVERBREAKOUT_GAMEMANAGER_H
