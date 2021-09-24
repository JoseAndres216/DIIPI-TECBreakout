#ifndef SERVERBREAKOUT_MATRIXNODE_H
#define SERVERBREAKOUT_MATRIXNODE_H

#include <iostream>
#include "../LinkedList.h"

using namespace std;

/**
 * @class This class is an implementation of a Node in the Matrix that contains a linked list.
 */
class MatrixNode {

private:

    LinkedList *linkedList;
    MatrixNode *next;
    MatrixNode *prev;

public:

    /**
     * @brief Class constructor, getters and setters.
     * @param linkedList
     */
    MatrixNode(LinkedList *linkedList) {
        this->linkedList = linkedList;
        this->next = nullptr;
        this->prev = nullptr;
    }

    LinkedList *getLinkedlist() {
        return linkedList;
    }

    void setLinkedlist(LinkedList *linkedList) {
        this->linkedList = linkedList;
    }

    MatrixNode *getNext() {
        return next;
    }

    void setNext(MatrixNode *next) {
        this->next = next;
    }

    MatrixNode *getPrev() {
        return prev;
    }

    void setPrev(MatrixNode *prev) {
        this->prev = prev;
    }
};

#endif //SERVERBREAKOUT_MATRIXNODE_H
