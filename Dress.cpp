#include "Dress.h"
#include <iostream>
#include <sstream>

using namespace std;
Dress::Dress(const string& id, const string& name, double price, const string& size, const string& color, int quantity)
    : Clothes(id, name) {
    this->price = price;
    variants.push_back(new Variant(size, color, quantity));
}

void Dress::ReadFile(istream& filein) {
    Clothes::ReadFile(filein);
}

void Dress::WriteFile(ostream& fileout) const {
    Clothes::WriteFile(fileout);
}

void Dress::ReadInput() {
    char prefix = 'D';
    highestIDMap[prefix]++; 
    clothesID = prefix + to_string(highestIDMap[prefix]); 
    cout << "Ma quan ao (tu dong): " << clothesID << endl;
    cout << "Nhap ten quan ao: ";
    getline(cin, name);
    cout << "Nhap gia: ";
    cin >> price;
    cin.ignore();
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