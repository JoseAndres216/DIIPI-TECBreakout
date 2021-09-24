#ifndef SERVERBREAKOUT_BLOCK_H
#define SERVERBREAKOUT_BLOCK_H

#include <iostream>

using namespace std;

/**
 * @class This class is an abstraction of a block.
 */
class Block {

private:

    int type;
    int resistance;
    int posX;
    int posY;

public:

    /**
     * @brief Class constructor that instance the variables on 0 or 1.
     */
    Block() {
        this->type = 0;
        this->resistance = 1;
        this->posX = 0;
        this->posY = 0;
    }

    /**
     * @brief Class constructor, getters and setters.
     * @param posX
     * @param posY
     * @param type
     */
    Block(int posX, int posY, int type) {
        this->type = type;
        if(type <= 3){
            this->resistance = type;
        }else{
            this->resistance = 1;
        }
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

    /**
     * @brief Function that decrease the resistance of the Block.
     */
    void decreaseResistance() {
        this->resistance--;
    }
};

#endif //SERVERBREAKOUT_BLOCK_H
