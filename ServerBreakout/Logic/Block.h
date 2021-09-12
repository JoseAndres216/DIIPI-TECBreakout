#ifndef SERVERBREAKOUT_BLOCK_H
#define SERVERBREAKOUT_BLOCK_H

#include <iostream>

using namespace std;

class Block {
private:
    int type;
    int resistance;
    int posX;
    int posY;
public:
    Block() {
        this->type = 0;
        this->resistance = 0;
        this->posX = 0;
        this->posY = 0;
    }

    Block(int posX, int posY) {
        this->type = 0;
        this->resistance = 0;
        this->posX = posX;
        this->posY = posY;
    }

    Block(int posX, int posY, int type) {
        this->type = type;
        this->resistance = 0;
        this->posX = posX;
        this->posY = posY;
    }

    int getType() const {
        return this->type;
    }

    void setType(int type) {
        this->type = type;
    }

    int getResistance() const {
        return this->resistance;
    }

    void setResistance(int resistance) {
        this->resistance = resistance;
    }

    int getPosX() const {
        return this->posX;
    }

    void setPosX(int posX) {
        this->posX = posX;
    }

    int getPosY() const {
        return this->posY;
    }

    void setPosY(int posY) {
        this->posY = posY;
    }

    void decreaseResistance() {
        this->resistance--;
    }
};

#endif //SERVERBREAKOUT_BLOCK_H
