#ifndef CLIENTBREAKOUT_TYPEMESSAGE_H
#define CLIENTBREAKOUT_TYPEMESSAGE_H

#include <iostream>

using namespace std;

/**
 * @class Keys dictionary for JsonManagement translation.
 */
class TypeMessage {

private:

    string firstTime;
    string x;
    string y;
    string collision;
    string fall;

public:

    /**
     * @brief firstTime getter.
     * @return The value of the firstTime key the string (response).
     */
    const string &getFirstTime() const {
        return firstTime;
    }

    /**
     * @brief firstTime setter.
     * @param firstTime
     */
    void setFirstTime(const string &firstTime) {
        TypeMessage::firstTime = firstTime;
    }

    /**
     * @brief fall getter.
     * @return The value of the fall key the string (response).
     */
    const string &getFall() const {
        return fall;
    }

    /**
     * @brief fall setter.
     * @param fall
     */
    void setFall(const string &fall) {
        TypeMessage::fall = fall;
    }

    /**
     * @brief collision getter.
     * @return The value of the collision key the string (response).
     */
    const string &getCollision() const {
        return collision;
    }

    /**
     * @brief collision setter.
     * @param collision
     */
    void setCollision(const string &collision) {
        TypeMessage::collision = collision;
    }

    /**
     * @brief x getter.
     * @return The value of the x key the string (response).
     */
    const string &getX() const {
        return x;
    }

    /**
     * @brief x setter.
     * @param x
     */
    void setX(const string &x) {
        TypeMessage::x = x;
    }

    /**
     * @brief y getter.
     * @return The value of the y key the string (response).
     */
    const string &getY() const {
        return y;
    }

    /**
     * @brief y setter.
     * @param y
     */
    void setY(const string &y) {
        TypeMessage::y = y;
    }

};


#endif //CLIENTBREAKOUT_TYPEMESSAGE_H
