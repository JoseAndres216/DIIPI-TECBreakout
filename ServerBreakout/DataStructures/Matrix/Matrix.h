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
    Matrix() {
        head = nullptr;
        tail = nullptr;
        len = 0;
    }

    bool isEmpty() {
        if (this->len == 0) {
            return true;
        } else {
            return false;
        }
    }

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

    void deleteElement(int posX, int posY) {
        MatrixNode *aux = getElement(posX, posY);
        aux->getLinkedlist()->deleteElement(posX, posY);
    }

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
