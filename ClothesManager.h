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
    void removeClothesByID(const string& id);
    void updateAllIDsFromID(const std::string& deletedID);
    void EditClothesByID(const string& id);
    void PrintClothesByID(const string& id) const;
    void SearchBySubstring(const string& sub = "", const string& brand = "", const string& color = "", const string& size = "", const string& type = "All") const;
    bool checkColor(Clothes* cloth, const string& color) const;
    bool checkSize(Clothes* cloth, const string& size) const;
};

#endif // CLOTHESMANAGER_H