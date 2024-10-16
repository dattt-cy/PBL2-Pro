#include "Male.h"
#include <iostream>
#include <sstream>

using namespace std;

Male::Male(const string &id, const string &name, double price, const string &branch, const string &size, const string &color, int quantity)
    : Clothes(id, name, branch) {
    this->price = price;
    addVariant(new Variant(size, color, quantity));
}

void Male::ReadFile(istream &filein) {
    string line;
    if (getline(filein, line)) {
        stringstream ss(line);
        getline(ss, clothesID, ',');
        getline(ss, name, ',');
        ss >> price;
        ss.ignore();
        getline(ss, branch, ','); // Đọc branch

        string size, color;
        int quantity;
        while (getline(ss, size, ',')) {
            getline(ss, color, ',');
            ss >> quantity;
            ss.ignore();
            if (!size.empty() && !color.empty() && quantity != 0) {
                variants.push_back(new Variant(size, color, quantity));
            }
        }
    }
}

void Male::WriteFile(ostream& fileout) const {
    fileout << clothesID << "," << name << "," << price << "," << branch;
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        if (!current->data->getSize().empty() && 
            !current->data->getColor().empty() && 
            current->data->getQuantity() != 0) {
            fileout << "," << current->data->getSize() << "," << current->data->getColor() << "," << current->data->getQuantity();
        }
        current = current->next;
    }
    fileout << endl;
}

void Male::ReadInput() {
    char prefix = 'M';
    highestIDMap[prefix]++; 
    clothesID = prefix + to_string(highestIDMap[prefix]); 
    cout << "Ma quan ao (tu dong): " << clothesID << endl;
    cout << "Nhap ten quan ao: ";
    getline(cin, name);
    cout << "Nhap gia: ";
    cin >> price;
    cin.ignore();
    cout << "Nhap ten thuong hieu: ";
    getline(cin, branch);

    string size, color;
    int quantity;
    cout << "Nhap size: ";
    getline(cin, size);
    cout << "Nhap mau: ";
    getline(cin, color);
    cout << "Nhap so luong: ";
    cin >> quantity;
    cin.ignore();
    addVariant(new Variant(size, color, quantity));

    char addMore;
    do {
        cout << "Ban co muon them bien the khac cho san pham nay khong? (y/n): ";
        cin >> addMore;
        cin.ignore();
        if (addMore == 'y' || addMore == 'Y') {
            cout << "Nhap size: ";
            getline(cin, size);
            cout << "Nhap mau: ";
            getline(cin, color);
            cout << "Nhap so luong: ";
            cin >> quantity;
            cin.ignore();
            addVariant(new Variant(size, color, quantity));
        }
    } while (addMore == 'y' || addMore == 'Y');
}