#ifndef SERVERBREAKOUT_NODE_H
#define SERVERBREAKOUT_NODE_H

#include <iostream>
#include "../Logic/Block.h"

using namespace std;

/**
 * @class This class is an implementation of a node that contain instances of Block class.
 */
class Node {

private:

    Block *block;
    Node *next;
    Node *prev;

public:

    /**
     * @brief Class constructor, getters and setters.
     * @param block
     */
    Node(Block *block) {
        this->block = block;
        this->next = nullptr;
        this->prev = nullptr;
    }

    Block *getBlock() {
        return this->block;
    }

    void setBlock(Block *block) {
        this->block = block;
    }

    Node *getNext() {
        return next;
    }

    void setNext(Node *next) {
        this->next = next;
    }

    Node *getPrev() {
        return prev;
    }

    void setPrev(Node *prev) {
        this->prev = prev;
    }
};

#endif //SERVERBREAKOUT_NODE_H
