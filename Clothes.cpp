#include "Clothes.h"

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
}

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

void Vest::ReadFile(istream& filein) {
    Clothes::ReadFile(filein);
}

void Dress::ReadFile(istream& filein) {
    Clothes::ReadFile(filein);
}
