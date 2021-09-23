//
// Created by keyner on 9/14/21.
//

#ifndef CLIENTBREAKOUT_TYPEMESSAGE_H
#define CLIENTBREAKOUT_TYPEMESSAGE_H

#include <iostream>

using namespace std;

class TypeMessage
{

private:

    string firstTime;
    string x;
    string y;
    string collision;

public:

    const string &getFirstTime() const {
        return firstTime;
    }

    void setFirstTime(const string &firstTime) {
        TypeMessage::firstTime = firstTime;
    }


    const string &getCollision() const {
        return collision;
    }

    void setCollision(const string &collision) {
        TypeMessage::collision = collision;
    }

    const string &getX() const {
        return x;
    }

    void setX(const string &x) {
        TypeMessage::x = x;
    }

    const string &getY() const {
        return y;
    }

    void setY(const string &y) {
        TypeMessage::y = y;
    }

};


#endif //CLIENTBREAKOUT_TYPEMESSAGE_H
