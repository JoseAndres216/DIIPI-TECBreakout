#ifndef SERVERBREAKOUT_PLAYER_H
#define SERVERBREAKOUT_PLAYER_H

#include <iostream>

using namespace std;

class Player {
private:
    string name;
    int score;
    int lives;
public:
    Player() {
        this->name = "";
        this->score = 0;
        this->lives = 3;
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

    int getLives() const {
        return lives;
    }

    void setLifes(int lifes) {
        this->lives = lifes;
    }

    void increaseScore(int increase) {
        this->score += increase;
    }

    void increaseLifes() {
        this->lives++;
    }

    void decreaseLifes() {
        this->lives--;
    }
};

#endif //SERVERBREAKOUT_PLAYER_H
