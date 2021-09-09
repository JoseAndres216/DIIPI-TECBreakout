#ifndef SERVERBREAKOUT_SIMPLELIST_H
#define SERVERBREAKOUT_SIMPLELIST_H

#include <iostream>
#include "Node.h"
#include "../Logic/Block.h"

using namespace std;

class SimpleList {
private:
    Node *head;
    Node *tail;
    int len;

public:
    SimpleList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->len = 0;
    }

    int getLen() {
        return this->len;
    }

    bool isEmpty() {
        if (this->len == 0) {
            return true;
        } else {
            return false;
        }
    }

    bool isElement(int posX, int posY) {
        if (!isEmpty()) {
            bool flag = false;
            Node *aux = this->head;
            while (aux != nullptr) {
                if (aux->getBlock().getPosX() == posX and aux->getBlock().getPosY() == posY) {
                    flag = true;
                    break;
                } else {
                    aux = aux->getNext();
                }
            }
            return flag;
        } else {
            cerr << "Couldn't find the element, the list is empty.";
        }
    }

    void addElement(Block *block) {
        Node *element = new Node(block);
        if (this->head == nullptr) {
            this->head = element;
            this->tail = element;
        } else {
            element->setPrev(this->tail);
            this->tail->setNext(element);
            this->tail = element;
        }
        this->len++;
    }

    void deleteElement(int posX, int posY) {
        if (!isEmpty()) {
            if (isElement(posX, posY)) {
                if (this->len == 1) {
                    this->head = nullptr;
                    this->tail = nullptr;
                } else if (this->len >= 2) {
                    if (this->head->getBlock().getPosX() == posX and this->head->getBlock().getPosY() == posY) {
                        this->head = this->head->getNext();
                        this->head->getPrev()->setNext(nullptr);
                        this->head->setPrev(nullptr);
                    } else if (this->tail->getBlock().getPosX() == posX and this->tail->getBlock().getPosY() == posY) {
                        this->tail = this->tail->getPrev();
                        this->tail->getNext()->setPrev(nullptr);
                        this->tail->setNext(nullptr);
                    } else {
                        Node *aux = this->head->getNext();
                        while (aux->getBlock().getPosX() != posX and aux->getBlock().getPosY() != posY and
                               aux != this->tail) {
                            aux = aux->getNext();
                        }
                        aux->getPrev()->setNext(aux->getNext());
                        aux->getNext()->setPrev(aux->getPrev());
                        aux->setNext(nullptr);
                        aux->setPrev(nullptr);
                    }
                }
                this->len--;
            } else {
                cerr << "Couldn't find the element, element doesn't exist.";
            }
        } else {
            cerr << "Couldn't delete the element, the list is empty.";
        }
    }

    void printList() {
        if (!isEmpty()) {
            Node *aux = this->head;
            while (aux != nullptr) {
                cout << "Element: (X: " << to_string(aux->getBlock().getPosX()) << ", Y: "
                     << to_string(aux->getBlock().getPosY()) << ") ";
                aux = aux->getNext();
            }
        } else {
            cerr << "The list is empty.";
        }
    }

};

#endif //SERVERBREAKOUT_SIMPLELIST_H
