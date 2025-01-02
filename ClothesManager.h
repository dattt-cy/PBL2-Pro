#ifndef CLOTHESMANAGER_H
#define CLOTHESMANAGER_H
#include "support.h"
#include "Clothes.h"
#include "LinkedList.h"
#include <string>
#include <iostream>

using namespace std;
class OrderManager;
class Order;
class ClothesManager {
private:
    LinkedList<Clothes*> list;

public:
    void addClothes(Clothes* clothes);
    void printAllClothes() const;
    void printByType(const string& type) const;
    Clothes* findByID(const string& id) const;
    void readClothesFromFile(const string& filename);
    bool addClothesManually();
    void Sort_ByID();
    void writeClothesToFile(const string& filename);
    bool removeClothesByID(const string& id);
    void updateAllIDsFromID(const std::string& deletedID);
    bool EditClothesByID(const string& id);
    void PrintClothesByID(const string& id) const;
    void SearchBySubstring(const string& sub = "", const string& brand = "", const string& color = "", const string& size = "", const string& type = "All") const;
    bool checkColor(Clothes* cloth, const string& color) const;
    bool checkSize(Clothes* cloth, const string& size) const;
    double getPriceByID(const string& itemID) const;
    void clearClothes();
     friend class OrderManager;
     
};

#endif // CLOTHESMANAGER_H