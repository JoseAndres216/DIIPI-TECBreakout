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

    /**
     * @brief Function that changes the type of an specific element to 0, emulating a delete function.
     * @param posX
     * @param posY
     */
    void deleteElement(int posX, int posY) {
        if (isElement(posX, posY)) {
            Node *element = getElement(posX, posY);
            if(element->getBlock()->getResistance() > 0 and element->getBlock()->getType() != 6){
                element->getBlock()->setResistance(element->getBlock()->getResistance()-1);
            }
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
