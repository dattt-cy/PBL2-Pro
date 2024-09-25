#ifndef CLOTHESMANAGER_H
#define CLOTHESMANAGER_H

#include "Clothes.h"
#include "LinkedList.h"
#include <string>
#include <iostream>

using namespace std;

class ClothesManager {
private:
    LinkedList<Clothes*> list;

public:
    void addClothes(Clothes* clothes);
    void printAllClothes() const;
    void printByType(const string& type) const;
    Clothes* findByID(const string& id) const;
    void readClothesFromFile(const string& filename);
    void addClothesManually();
    void Sort_ByID();
    void writeClothesToFile(const string& filename);
    void removeClothesByID(const std::string& id);
    void updateAllIDsFromID(const std::string& deletedID);
};

#endif // CLOTHESMANAGER_H