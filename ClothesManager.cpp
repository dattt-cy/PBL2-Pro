#include "ClothesManager.h"
#include "Dress.h"
#include "Vest.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

void ClothesManager::addClothes(Clothes* clothes) {
    list.addNode(clothes);
}

void ClothesManager::printAllClothes() const {
    Node<Clothes*>* current = list.getHead();
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
    cout << "| ID             | Ten            | Size   | Mau    | Gia      | So luong  |" << endl;
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
    while (current != nullptr) {
        current->data->Print();
        current = current->next;
    }
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
}

void ClothesManager::printByType(const string& type) const {
    Node<Clothes*>* current = list.getHead();
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
    cout << "| ID             | Ten            | Size   | Mau    | Gia      | So luong  |" << endl;
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
    while (current != nullptr) {
        if ((type == "Dress" && dynamic_cast<Dress*>(current->data)) ||
            (type == "Vest" && dynamic_cast<Vest*>(current->data))) {
            current->data->Print();
        }
        current = current->next;
    }
    cout << "+----------------+----------------+--------+--------+----------+-----------+" << endl;
}

Clothes* ClothesManager::findByID(const string& id) const {
    Node<Clothes*>* current = list.getHead();
    while (current != nullptr) {
        if (current->data->getID() == id) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void ClothesManager::readClothesFromFile(const string& filename) {
    ifstream filein(filename);
    if (!filein.is_open()) {
        cerr << "Không thể mở file!" << endl;
        return;
    }
    string line;
    Clothes* item = nullptr;

    while (getline(filein, line)) {
        if (line[0] == 'V') {
            item = new Vest();
        } else if (line[0] == 'D') {
            item = new Dress();
        } 

        if (item != nullptr) {
            stringstream ss(line);
            item->ReadFile(ss);
            addClothes(item);
            Clothes::updateHighestID(item->getID()); 
        }
    }

    filein.close();
}

void ClothesManager::writeClothesToFile(const string& filename) {
    ofstream fileout(filename);
    if (!fileout.is_open()) {
        cerr << "Khong the mo file!" << endl;
        return;
    }
    Node<Clothes*>* current = list.getHead();
    while (current != nullptr) {
        current->data->WriteFile(fileout);
        current = current->next;
    }
    fileout.close();
}

void ClothesManager::addClothesManually() {
    char type;
    cout << "Nhap loai quan ao (V: Vest, D: Dress): ";
    cin >> type;
    cin.ignore(); 

    Clothes* item = nullptr;

    if (type == 'V') {
        item = new Vest();
    } else if (type == 'D') {
        item = new Dress();
    } else {
        cout << "Loai quan ao khong hop le!" << endl;
        return;
    }

    if (item != nullptr) {
        item->ReadInput();
        addClothes(item);
    }
}

void ClothesManager::Sort_ByID() {
    list.Sort(); 
}