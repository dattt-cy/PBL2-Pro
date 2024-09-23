#include "Clothes.h"

map<char, int> Clothes::highestIDMap;

void Clothes::updateHighestID(const string& id) {
    char prefix = id[0];
    int numericID = stoi(id.substr(1)); 
    if (highestIDMap.find(prefix) == highestIDMap.end() || numericID > highestIDMap[prefix]) {
        highestIDMap[prefix] = numericID;
    }
}
void Clothes::ReadFile(istream& filein) {
    getline(filein, clothesID, ',');
    filein.ignore();
    getline(filein, name, ',');
    filein.ignore();
    getline(filein, size, ',');
    filein.ignore();
    getline(filein, color, ',');
    filein.ignore();
    filein >> price;
    filein.ignore();
    filein >> quantity;
    filein.ignore();
    updateHighestID(clothesID);
}
void Clothes::ReadInput(){}

void Clothes::Print() {
    cout << "| " << setw(14) << left << clothesID << " | "
         << setw(14) << left << name << " | "
         << setw(6) << left << size << " | "
         << setw(6) << left << color << " | "
         << setw(8) << right << fixed << setprecision(0) << price << " | "
         << setw(9) << right << quantity << " |" << endl;
}

string Clothes::getID() {
    return clothesID;
}
void Clothes::setID(string id) {
    clothesID = id;
}