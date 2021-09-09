#ifndef SERVERBREAKOUT_PLAYER_H
#define SERVERBREAKOUT_PLAYER_H

#include <iostream>

using namespace std;

class Player {
private:
    string name;
    int score;
    int lifes;
public:
    Player() {
        this->name = "";
        this->score = 0;
        this->lifes = 3;
    }

    const string &getName() const {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    int getScore() const {
        return score;
    }

    void setScore(int score) {
        this->score = score;
    }

    int getLifes() const {
        return lifes;
    }

    void setLifes(int lifes) {
        this->lifes = lifes;
    }

    void increaseScore(int increase) {
        this->score += increase;
    }

    void increaseLifes() {
        this->lifes++;
    }

    void decreaseLifes() {
        this->lifes--;
    }
};

#endif //SERVERBREAKOUT_PLAYER_H
