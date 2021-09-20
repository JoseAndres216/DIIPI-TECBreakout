#ifndef SERVERBREAKOUT_MATRIX_H
#define SERVERBREAKOUT_MATRIX_H

#include <iostream>
#include "MatrixNode.h"
#include "../LinkedList.h"

using namespace std;

class Matrix {
private:
    MatrixNode *head;
    MatrixNode *tail;
    int len;
public:
    /**
     * @brief Class constructor, getters and setters.
     */
    Matrix() {
        head = nullptr;
        tail = nullptr;
        len = 0;
    }

    MatrixNode *getHead() const {
        return head;
    }

    MatrixNode *getTail() {
        return tail;
    }

    int getLen() {
        return len;
    }

    /**
     * @brief function to check if list is empty.
     * @return returns true if empty and false if there is at least one element.
     */
    bool isEmpty() {
        if (this->len == 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief Function that adds a row (new element in the main list)
     */
    void addRow() {
        MatrixNode *element = new MatrixNode(new LinkedList());
        if (isEmpty()) {
            this->head = element;
            this->tail = element;
        } else {
            element->setPrev(this->tail);
            this->tail->setNext(element);
            this->tail = element;
        }
        this->len++;
    }

    /**
     * @brief Function that adds a new element in an specific row.
     * @param row
     * @param posX
     * @param posY
     * @param type
     */
    void addElement(int row, int posX, int posY, int type) {
        if (row <= this->len) {
            MatrixNode *aux = this->head;
            for (int i = 1; i < row; i++) {
                aux = aux->getNext();
            }
            aux->getLinkedlist()->addElement(new Block(posX, posY, type));
        } else {
            cerr << "Out of index, impossible adding the element.";
        }
    }

    /**
     * @brief Function to check if there is an element in the list with the given parameters.
     * @param posX
     * @param posY
     * @return Returns true if could find the element, false if not.
     */
    bool isElement(int posX, int posY) {
        MatrixNode *aux = this->head;
        while (aux != nullptr) {
            if (aux->getLinkedlist()->isElement(posX, posY)) {
                return true;
            } else {
                aux = aux->getNext();
            }
        }
        return false;
    }

    /**
     * @brief Function to get and specific element, based on the given parameters.
     * @param posX
     * @param posY
     * @return Returns the requested element.
     */
    MatrixNode *getElement(int posX, int posY) {
        if (isElement(posX, posY)) {
            MatrixNode *aux = this->head;
            while (aux != nullptr) {
                if (aux->getLinkedlist()->isElement(posX, posY)) {
                    return aux;
                } else {
                    aux = aux->getNext();
                }
            }
        } else {
            cerr << "Couldn't find the element.";
        }
    }

    /**
     * @brief Function to change the type of an specific element to 0, emulating a delete function.
     * @param posX
     * @param posY
     */
    void deleteElement(int posX, int posY) {
        MatrixNode *aux = getElement(posX, posY);
        aux->getLinkedlist()->deleteElement(posX, posY);
    }

    /**
     * @brief Function to get a random element of the list.
     * @return Returns the element chosen.
     */
    void printMatrix() {
        MatrixNode *aux = this->head;
        while (aux != nullptr) {
            cout << "Row: [   ";
            aux->getLinkedlist()->printList();
            cout << " ]\n";
            aux = aux->getNext();
        }
    }
};

#endif //SERVERBREAKOUT_MATRIX_H
