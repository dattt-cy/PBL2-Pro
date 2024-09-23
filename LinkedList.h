#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(NULL) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList();
    ~LinkedList();
    bool isEmpty();
    bool addNode(T newItem);
    T findByID(const string& ID) const;
    Node<T>* getHead() const { return head; }
};

template <class T>
LinkedList<T>::LinkedList() : head(NULL) {}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current != NULL) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

template <class T>
bool LinkedList<T>::isEmpty() {
    return head == NULL;
}

template <class T>
bool LinkedList<T>::addNode(T newItem) {
    if (this->findByID(newItem->getID()) == nullptr) {
        Node<T>* newNode = new Node<T>(newItem);
        newNode->next = head;
        head = newNode;
        return true;
    }
    return false;
}

template <class T>
T LinkedList<T>::findByID(const string& ID) const{
    Node<T>* temp = head;
    while (temp != NULL) {
        if (temp->data->getID() == ID) {
            return temp->data;
        }
        temp = temp->next;
    }
    return nullptr;
}

#endif // LINKEDLIST_H