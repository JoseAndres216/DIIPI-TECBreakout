//
// Created by keyner on 9/14/21.
//

#ifndef SERVERBREAKOUT_TYPEMESSAGE_H
#define SERVERBREAKOUT_TYPEMESSAGE_H

#include <iostream>

using namespace std;

class TypeMessage
{

private:

    string matrix;

public:
    const string &getMatrix() const {
        return matrix;
    }

    void setMatrix(const string &matrix) {
        TypeMessage::matrix = matrix;
    }

};


#endif //SERVERBREAKOUT_TYPEMESSAGE_H
