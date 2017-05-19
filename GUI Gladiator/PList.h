//
// Created by aaronsolera on 08/05/17.
//

#ifndef PRUEBAS_PLIST_H
#define PRUEBAS_PLIST_H
#include "ListNode.h"

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------- CLASS DEFINITION ---------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

template <class Type>

class PList {

private:
    ListNode<Type> *_head;
    int _size;

public:
    PList();
    ~PList();

    int insert(Type);

    Type get(int);

    int remove(int);

    int clear();

    int size();

    bool isEmpty();

};

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------ END CLASS DEFINITION ------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------ CLASS IMPLEMENTATION ------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

/**
 * Constructor of the class
 *
 */
template <class Type>
PList<Type>::PList() {
    this->_head = nullptr;
    this->_size = 0;
}

template <class Type>
PList<Type>::~PList() {
    //?????
}

/**
 *
 *
 * @param pData -
 * @return -
 */
template <class Type>
int PList<Type>::insert(Type pData) {

    ListNode<Type> *newNode = new ListNode<Type>(pData);

    if(this->isEmpty()) {
        this->_head = newNode;
    }
    else {
        ListNode<Type> *currentNode = this->_head;
        while(currentNode->getNext() != nullptr) {
            currentNode = currentNode->getNext();
        }
        currentNode->setNext(newNode);
    }
    this->_size++;
    return 0;
}

/**
 *
 *
 * @param pPosition -
 * @return -
 */
template <class Type>
Type PList<Type>::get(int pPosition) {

    if(pPosition < this->size()) {

        ListNode<Type> *currentNode = this->_head;

        for (int i = 0; i < this->size(); i++) {
            if (i == pPosition) {
                return currentNode->getData();
            }
            currentNode = currentNode->getNext();
        }
    }
    else {
        cout << "Error" << endl;
    }
}

/**
 *
 *
 * @param pPosition -
 * @return -
 */
template <class Type>
int PList<Type>::remove(int pPosition) {

    if(this->isEmpty() || (pPosition < 0) || (pPosition > (this->size()) - 1)) {
        //ERROR
        return -1;
    }
    else {

        ListNode<Type> *currentNode = this->_head;
        ListNode<Type> *previousNode = this->_head;

        for(int i = 0; i < pPosition; i++) {
            previousNode = currentNode;
            currentNode = currentNode->getNext();
        }

        if(this->_head == currentNode) {
            this->_head = currentNode->getNext();
        }
        else {
            previousNode->setNext(currentNode->getNext());
        }
        delete currentNode;
        this->_size--;
        return 1;
    }
}

/**
 *
 *
 * @return -
 */
template <class Type>
int PList<Type>::clear() {

    if(this->size() > 0) {

        ListNode<Type> *tempNode = this->_head;

        while(tempNode != nullptr) {

            this->_head = tempNode->getNext();

            delete tempNode;

            tempNode = this->_head;

        }

        this->_head = nullptr;
        this->_size = 0;
        return 1;
    }
}

/**
 *
 *
 * @return -
 */
template <class Type>
int PList<Type>::size() {
    return this->_size;
}

/**
 *
 *
 * @return -
 */
template <class Type>
bool PList<Type>::isEmpty() {
    return (this->_head == NULL);
}
#endif //PRUEBAS_PLIST_H
