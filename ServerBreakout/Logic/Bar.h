#ifndef SERVERBREAKOUT_BAR_H
#define SERVERBREAKOUT_BAR_H

#include <iostream>

using namespace std;

class Bar {
private:
    int size;

public:
    Bar() {
        size = 800;
    }

    const int getSize() const {
        return size;
    }

    void setSize(int size) {
        this->size = size;
    }

    void increaseSize() {
        this->size += 50;
    }

    void decreaseSize() {
        this->size -= 50;
    }

    void resetSize() {
        size = 300;
    }

};

#endif //SERVERBREAKOUT_BAR_H
