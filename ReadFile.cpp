#include "ReadFile.h"
#include "Vest.h"
#include "Dress.h"
#include <fstream>
#include <sstream>
#include <iostream>

void readClothesFromFile(const std::string& filename, LinkedList<Clothes*>& list) {
    std::ifstream filein(filename);
    if (!filein.is_open()) {
        std::cout << "Không thể mở file!" << std::endl;
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
            list.addNode(item);
            Clothes::updateHighestID(item->getID()); 
        }
    }

    filein.close();
}

void addClothesManually(LinkedList<Clothes*>& list) {
    char type;
    std::cout << "Nhap loai quan ao (V: Vest, D: Dress, S: Shirt): ";
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
        list.addNode(item);
    }
}