#ifndef SERVERBREAKOUT_BALL_H
#define SERVERBREAKOUT_BALL_H

#include <iostream>

using namespace std;

/**
 * @class
 */
class Ball {

private:

    float speedX;

    float speedY;

    int depth;

public:

    Ball() {
        this->speedX = 5;
        this->speedY = -5;
        this->depth = 0;
    }


    const float getSpeedX() const {
        return speedX;
    }

    void setSpeedX(const float &speedX) {
        Ball::speedX = speedX;
    }

    const float getSpeedY() const {
        return speedY;
    }

    void setSpeedY(const float &speedY) {
        Ball::speedY = speedY;
    }

    const int getDepth() const {
        return depth;
    }

    void setDepth(int depth) {
        this->depth = depth;
    }

    void increaseSpeed() {
        this->speedX += speedX*1.2;
        this->speedY += speedX*1.2;
    }

    void decreaseSpeed() {
        this->speedX = speedX/1.2;
        this->speedY = speedY/1.2;
    }

    void resetSpeed() {
        this->speedX = 5;
        this->speedY = -5;
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
