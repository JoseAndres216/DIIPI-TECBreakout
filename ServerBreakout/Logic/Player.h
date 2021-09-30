#ifndef SERVERBREAKOUT_PLAYER_H
#define SERVERBREAKOUT_PLAYER_H

#include <iostream>

using namespace std;

/**
 * @class This class is an abstraction of a player.
 */
class Player {

private:

    int score;
    int lives;

public:

    /**
     * @brief Class constructor, getters and setters,
     */
    Player(){
        this->score = 0;
        this->lives = 20;
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

    void setLives(int lives) {
        this->lives = lives;
    }

    /**
     * @brief Function to increase the score.
     */
    void increaseScore(int increase) {
        this->score += increase;
    }

    /**
     * @brief Function to decrease the score.
     */
    void decreaseScore(int decrease) {
        this->score -= decrease;
    }

    /**
     * @brief Function to increase the lives.
     */
    void increaseLives() {
        this->lives++;
    }

    /**
     * @brief Function to decrease the lives.
     */
    void decreaseLives() {
        this->lives--;
    }

};

#endif //SERVERBREAKOUT_PLAYER_H
