#ifndef SERVERBREAKOUT_NODE_H
#define SERVERBREAKOUT_NODE_H

#include <iostream>
#include "../Logic/Block.h"

using namespace std;

class Node {
private:
    Block *block;
    Node *next;
    Node *prev;

public:
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
