#include "ClothesManager.h"
#include "Dress.h"
#include "Vest.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

void ClothesManager::addClothes(Clothes* clothes) {
    list.addNode(clothes);
}

void ClothesManager::printAllClothes() const {
    Node<Clothes*>* current = list.getHead();
    std::cout << "+----------------+----------------+--------+--------+----------+-----------+" << std::endl;
    std::cout << "| ID             | Ten            | Size   | Mau    | Gia      | So luong  |" << std::endl;
    std::cout << "+----------------+----------------+--------+--------+----------+-----------+" << std::endl;
    while (current != nullptr) {
        current->data->Print();
        current = current->next;
    }
    std::cout << "+----------------+----------------+--------+--------+----------+-----------+" << std::endl;
}

void ClothesManager::printByType(const std::string& type) const {
    Node<Clothes*>* current = list.getHead();
    std::cout << "+----------------+----------------+--------+--------+----------+-----------+" << std::endl;
    std::cout << "| ID             | Ten            | Size   | Mau    | Gia      | So luong  |" << std::endl;
    std::cout << "+----------------+----------------+--------+--------+----------+-----------+" << std::endl;
    while (current != nullptr) {
        if ((type == "Dress" && dynamic_cast<Dress*>(current->data)) ||
            (type == "Vest" && dynamic_cast<Vest*>(current->data))) {
            current->data->Print();
        }
        current = current->next;
    }
    std::cout << "+----------------+----------------+--------+--------+----------+-----------+" << std::endl;
}

Clothes* ClothesManager::findByID(const std::string& id) const {
    return list.findByID(id);
}

void ClothesManager::readClothesFromFile(const std::string& filename) {
    std::ifstream filein(filename);
    if (!filein.is_open()) {
        std::cerr << "Không thể mở file!" << std::endl;
        return;
    }

    std::string line;
    Clothes* item = nullptr;

    while (getline(filein, line)) {
        if (line[0] == 'V') {
            item = new Vest();
        } else if (line[0] == 'D') {
            item = new Dress();
        } 

        if (item != nullptr) {
            std::stringstream ss(line);
            item->ReadFile(ss);
            addClothes(item);
            Clothes::updateHighestID(item->getID()); 
        }
    }

    filein.close();
}

void ClothesManager::addClothesManually() {
    char type;
    std::cout << "Nhap loai quan ao (V: Vest, D: Dress): ";
    std::cin >> type;
    std::cin.ignore(); 

    Clothes* item = nullptr;

    if (type == 'V') {
        item = new Vest();
    } else if (type == 'D') {
        item = new Dress();
    } else {
        std::cout << "Loại quần áo không hợp lệ!" << std::endl;
        return;
    }

    if (item != nullptr) {
        item->ReadInput();
        addClothes(item);
    }
}