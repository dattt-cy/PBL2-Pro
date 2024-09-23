// Vest.cpp
#include "Vest.h"
#include <iostream>
#include <sstream>

using namespace std;

void Vest::ReadFile(istream& filein) {
    Clothes::ReadFile(filein);
}

void Vest::WriteFile(ostream& out) const {
    out << clothesID << ", " << name << ", " << size << ", " << color << ", " << price << ", " << quantity << endl;
}

void Vest::ReadInput() {
    char prefix = 'V';
    highestIDMap[prefix]++; 
    clothesID = prefix + to_string(highestIDMap[prefix]);
    cout << "Ma quan ao (tu dong): " << clothesID << endl;
    cout << "Nhap ten quan ao: ";
    getline(cin, name);
    cout << "Nhap kich co (S, M, L, XL, ...): ";
    getline(cin, size);
    cout << "Nhap mau sac: ";
    getline(cin, color);
    cout << "Nhap gia: ";
    cin >> price;
    cout << "Nhap so luong: ";
    cin >> quantity;
    cin.ignore(); 
    cout << "-----------------------------------------" << endl;
}