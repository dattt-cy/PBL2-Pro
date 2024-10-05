#include "Vest.h"
#include <iostream>
#include <sstream>

Vest::Vest(const string& id, const string& name, double price, const string& size, const string& color, int quantity)
    : Clothes(id, name) {
    this->price = price;
    variants.push_back(new Variant(size, color, quantity));
}

void Vest::ReadFile(istream& filein) {
    Clothes::ReadFile(filein);
}

void Vest::WriteFile(ostream& fileout) const {
    Clothes::WriteFile(fileout);
}

void Vest::ReadInput() {
    char prefix = 'V';
    highestIDMap[prefix]++; 
    clothesID = prefix + to_string(highestIDMap[prefix]); 
    cout << "Ma quan ao (tu dong): " << clothesID << endl;
    cout << "Nhap ten quan ao: ";
    getline(cin, name);
    cout << "Nhap gia: ";
    cin >> price;
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
        variants.push_back(new Variant(size, color, quantity));

        cout << "Ban co muon them bien the khac cho san pham nay khong? (y/n): ";
        cin >> addMore;
        cin.ignore();
    } while (addMore == 'y' || addMore == 'Y');
}
