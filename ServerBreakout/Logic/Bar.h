#ifndef SERVERBREAKOUT_BAR_H
#define SERVERBREAKOUT_BAR_H

#include <iostream>

using namespace std;

class Bar {
private:
    int size;

public:
    Bar() {
        size = 300;
    }

    int getSize() {
        return size;
    }

    void setSize(int size) {
        this->size = size;
    }

    void increaseSize() {
        this->size += 25;
    }

    void decreaseSize() {
        this->size -= 25;
    }

    void resetSize() {
        this->size = 300;
    }

};

#endif //SERVERBREAKOUT_BAR_H
