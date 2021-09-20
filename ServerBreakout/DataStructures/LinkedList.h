#ifndef SERVERBREAKOUT_LINKEDLIST_H
#define SERVERBREAKOUT_LINKEDLIST_H

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdio.h>
#include "Node.h"
#include "../Logic/Block.h"

using namespace std;

class LinkedList {
private:
    Node *head;
    Node *tail;
    int len;

public:
    /**
     * @brief Class constructor, getters and setters
     */
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->len = 0;
    }

    Node *getHead() {
        return head;
    }

    Node *getTail() {
        return tail;
    }

    int getLen() {
        return this->len;
    }

    /**
     * @brief Function to check if list is empty.
     * @return Returns true if empty and false if there is at least one element.
     */
    bool isEmpty() {
        if (this->len == 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief Function to check if there is an element in the list with the given parameters.
     * @param posX
     * @param posY
     * @return Returns true if could find the element, false if not.
     */
    bool isElement(int posX, int posY) {
        if (!isEmpty()) {
            bool flag = false;
            Node *aux = this->head;
            while (aux != nullptr) {
                if (aux->getBlock()->getPosX() == posX and aux->getBlock()->getPosY() == posY) {
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

    /**
     * @brief Function to get and specific element, based on the given parameters.
     * @param posX
     * @param posY
     * @return Returns the requested element.
     */
    Node *getElement(int posX, int posY) {
        if (!isEmpty()) {
            Node *aux = this->head;
            while (aux != nullptr) {
                if (aux->getBlock()->getPosX() == posX and aux->getBlock()->getPosY() == posY) {
                    return aux;
                } else {
                    aux = aux->getNext();
                }
            }
        } else {
            cerr << "Couldn't find the element, the list is empty.";
        }
    }

    /**
     * @brief Function to add a new element on the list.
     * @param block
     */
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

    /*
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
    */

    /**
     * @brief Function that changes the type of an specific element to 0, emulating a delete function.
     * @param posX
     * @param posY
     */
    void deleteElement(int posX, int posY) {
        if (isElement(posX, posY)) {
            Node *element = getElement(posX, posY);
            element->getBlock()->setType(0);
        } else {
            cerr << "Couldn't find the element.";
        }
    }

    /**
     * @brief Function to get a random element of the list.
     * @return Returns the element chosen.
     */
    Node *getRandom() {
        srand(time(NULL));
        int chosen = rand() % this->len;
        Node *aux = this->head;
        for (int i = 0; i < chosen; i++) {
            aux = aux->getNext();
        }
        return aux;
    }

    /**
     * @brief Function that prints the list.
     */
    void printList() {
        if (!isEmpty()) {
            Node *aux = this->head;
            while (aux != nullptr) {
                cout << "Element: (X: " << to_string(aux->getBlock()->getPosX()) << ", Y: "
                     << to_string(aux->getBlock()->getPosY()) << ", Type: " << to_string(aux->getBlock()->getType())
                     << ", Resistance: " << to_string(aux->getBlock()->getResistance()) << ")   ";
                aux = aux->getNext();
            }
        } else {
            cerr << "The list is empty.";
        }
    }
};

#endif //SERVERBREAKOUT_LINKEDLIST_H
