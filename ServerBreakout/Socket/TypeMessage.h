//
// Created by keyner on 9/14/21.
//

#ifndef SERVERBREAKOUT_TYPEMESSAGE_H
#define SERVERBREAKOUT_TYPEMESSAGE_H

#include <iostream>

using namespace std;

/**
 * @class Class made for a better communication between server and client.
 */
class TypeMessage
{

private:

    string matrix;

    string score;

    string barSize;

    string lives;

    string Depth;

    string ballMovement;

    string surprise;

    string win;

public:

    const string &getDepth() const {
        return Depth;
    }

    void setDepth(const string &depth) {
        Depth = depth;
    }


    const string &getLives() const {
        return lives;
    }

    void setLives(const string &lives) {
        TypeMessage::lives = lives;
    }

    const string &getScore() const {
        return score;
    }

    void setScore(const string &score) {
        TypeMessage::score = score;
    }

    const string &getSurprise() const {
        return surprise;
    }

    void setSurprise(const string &surprise) {
        TypeMessage::surprise = surprise;
    }

    const string &getBallMovement() const {
        return ballMovement;
    }

    void setBallMovement(const string &ballMovement) {
        TypeMessage::ballMovement = ballMovement;
    }

    const string &getBarSize() const {
        return barSize;
    }

    void setBarSize(const string &barSize) {
        TypeMessage::barSize = barSize;
    }

    const string &getMatrix() const {
        return matrix;
    }

    void setMatrix(const string &matrix) {
        TypeMessage::matrix = matrix;
    }

    const string &getWin() const {
        return win;
    }

    void setWin(const string &win) {
        TypeMessage::win = win;
    }

};


#endif //SERVERBREAKOUT_TYPEMESSAGE_H
