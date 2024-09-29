// Vest.cpp
#include "Vest.h"
#include <iostream>
#include <sstream>

using namespace std;

void Vest::ReadFile(istream& filein) {
    Clothes::ReadFile(filein);
}

void Vest::WriteFile(ostream& fileout) const {
    fileout << clothesID << "," << name;
    for (const auto& variant : variants) {
        fileout << "," << variant.getSize() << "," << variant.getColor() << "," << variant.getQuantity();
    }
    fileout << "," << price << endl;
}

void Vest::ReadInput() {
    char prefix = 'D';
    highestIDMap[prefix]++; 
    clothesID = prefix + to_string(highestIDMap[prefix]); 
    cout << "Ma quan ao (tu dong): " << clothesID << endl;
    cout << "Nhap ten quan ao: ";
    getline(cin, name);

    char addMore;
    do {
        string size, color;
        int quantity;
        cout << "Nhap kich co (S, M, L, XL, ...): ";
        getline(cin, size);
        cout << "Nhap mau sac: ";
        getline(cin, color);
        cout << "Nhap so luong: ";
        cin >> quantity;
        cin.ignore(); 
        variants.emplace_back(size, color, quantity);

        cout << "Ban co muon them bien the khac cho san pham nay khong? (y/n): ";
        cin >> addMore;
        cin.ignore(); 
    } while (addMore == 'y' || addMore == 'Y');

    cout << "Nhap gia: ";
    cin >> price;
    cin.ignore(); 

    cout << "-----------------------------------------" << endl;
}