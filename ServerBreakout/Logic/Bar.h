#ifndef SERVERBREAKOUT_BAR_H
#define SERVERBREAKOUT_BAR_H

#include <iostream>

using namespace std;

/**
 * @class This class is an abstraction of a bar.
 */
class Bar {

private:

    int size;

public:

    /**
     * @brief Class constructor, getters and setters,
     */
    Bar() {
        size = 200;
    }

    const int getSize() const {
        return size;
    }

    void setSize(int size) {
        this->size = size;
    }

    /**
     * @brief Function to increase the lives.
     */
    void increaseSize() {
        if(this->size < 400){
            this->size += 50;
        }
    }

    /**
     * @brief Function to increase the lives.
     * @
     */
    void decreaseSize() {
        if(this->size > 0){
            this->size -= 50;
        }
    }

    /**
     * @brief Function to increase the lives.
     */
    void resetSize() {
        size = 200;
    }

};

#endif //SERVERBREAKOUT_BAR_H
