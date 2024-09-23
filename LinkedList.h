#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <iomanip>
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
    int findNode(string ID);
    template <typename U> void printByType();
    void printList();
    void printHeader();
    void printFooter();
};

// Định nghĩa các phương thức ngay trong file header
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
    if (this->findNode(newItem->getID()) == -1) {
        Node<T>* newNode = new Node<T>(newItem);
        newNode->next = head;
        head = newNode;
        return true;
    }
    return false;
}

template <class T>
int LinkedList<T>::findNode(string ID) {
    Node<T>* temp = head;
    int position = 0;
    while (temp != NULL) {
        if (temp->data->getID() == ID) {
            return position;
        }
        temp = temp->next;
        ++position;
    }
    return -1;
}

template <class T>
template <typename U>
void LinkedList<T>::printByType() {
    Node<T>* temp = head;
    printHeader();
    while (temp != NULL) {
        U* item = dynamic_cast<U*>(temp->data);
        if (item != NULL) {
            item->Print();
        }
        temp = temp->next;
    }
    printFooter();
}

template <class T>
void LinkedList<T>::printList() {
    Node<T>* temp = head;
    printHeader();
    while (temp != NULL) {
        temp->data->Print();
        temp = temp->next;
    }
    printFooter();
}

template <class T>
void LinkedList<T>::printHeader() {
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
    cout << "| ID             | Ten            | Size   | Mau    | Gia      | So luong  |" << endl;
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
}

template <class T>
void LinkedList<T>::printFooter() {
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
}

#endif
