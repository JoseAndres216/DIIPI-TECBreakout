#ifndef SERVERBREAKOUT_BALL_H
#define SERVERBREAKOUT_BALL_H

#include <iostream>

using namespace std;

class Ball {
private:
    int speed;
    int depth;
public:
    Ball() {
        this->speed = 5;
        this->depth = 0;
    }

    int getSpeed() {
        return speed;
    }

    void setSpeed(int speed) {
        this->speed = speed;
    }

    int getDepth() {
        return depth;
    }

    void setDepth(int depth) {
        this->depth = depth;
    }

    void increaseSpeed() {
        this->speed += 10;
    }

    void decreaseSpeed() {
        this->speed -= 10;
    }

    void resetSpeed() {
        this->speed = 5;
    }

    void increaseDepth() {
        this->depth++;
    }

    void decreaseDepth() {
        this->depth--;
    }

    void resetDepth() {
        this->depth = 0;
    }
};

#endif //SERVERBREAKOUT_BALL_H
