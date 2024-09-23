#include "ReadFile.h"
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
        }
    }

    filein.close();
}
