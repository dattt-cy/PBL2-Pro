#include "Female.h"
#include <iostream>
#include <sstream>

using namespace std;

Female::Female(const string &id, const string &name, double price, const string &branch, const string &size, const string &color, int quantity)
    : Clothes(id, name, branch) {
    this->price = price;
    addVariant(new Variant(size, color, quantity));
}

void Female::ReadFile(istream &filein) {
    string line;
    if (getline(filein, line)) {
        stringstream ss(line);
        getline(ss, clothesID, ',');
        getline(ss, name, ',');
        ss >> price;
        ss.ignore();
        getline(ss, branch, ','); 

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

void Female::WriteFile(ostream& fileout) const {
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

void Female::ReadInput() {
    char prefix = 'F';
    highestIDMap[prefix]++;
    clothesID = prefix + to_string(highestIDMap[prefix]);
    cout << "<!> Ma quan ao (tu dong): " << clothesID << endl;

    while (true) {
        cout << "<!> Nhap ten quan ao ( nhap 0 de huy ): ";
        getline(cin, name);
        name = nameStr(name);
        if(name == "0") return;
        if (!name.empty()) break;
        cout << "<!> Ten quan ao khong duoc de trong. Vui long nhap lai." << endl;
    }

    while (true) {
        string priceStr;
        cout << "<!> Nhap gia: ";
        getline(cin, priceStr);
          if(isCharacter(priceStr)){
            cout << "<!> Gia phai la so. Vui long nhap lai." << endl;
            continue;
        }
        price = stoi(priceStr);
        if (price <= 0) {
            cout << "<!> Gia phai la so duong. Vui long nhap lai." << endl;
            continue;
        } else {
            break;
        }
    }

    while (true) {
        cout << "<!> Nhap ten thuong hieu: ";
        getline(cin, branch);
        branch = nameStr(branch);
        if (!branch.empty()) break;
        cout << "<!> Ten thuong hieu khong duoc de trong. Vui long nhap lai." << endl;
    }

    string size, color;
    string quantity2;
    int quantity;

    set<string> validSizes = {"XS", "S", "M", "L", "XL", "XXL", "XXXL"};

    while (true) {
        cout << "<!> Nhap size (XS, S, M, L, XL, XXL, XXXL): ";
        getline(cin, size);
        size = toUpper(size);
        if (validSizes.find(size) != validSizes.end()) break;
        cout << "<!> Size khong hop le. Vui long nhap lai." << endl;
    }

    set<string> validColors = {"Red", "Blue", "Green", "Yellow", "Black", "White", "Purple", "Brown", "Pink", "Beige", "Gray", "Orange"};

    while (true) {
        cout << "<!> Nhap mau (Red, Blue, Green, Yellow, Black, White, Purple, Brown, Pink, Beige, Gray, Orange): ";
        getline(cin, color);
        color = nameStr(color);
        if (validColors.find(color) != validColors.end()) break;
        cout << "<!> Mau khong hop le. Vui long nhap lai." << endl;
    }

    while (true) {
        cout << "<!> Nhap so luong: ";
        cin >> quantity2;
        if(isCharacter(quantity2)){
            cout << "<!> So luong phai la so. Vui long nhap lai." << endl;
            continue;
        }
        quantity = stoi(quantity2);
        if (quantity <= 0) {
            cout << "<!> So luong phai la so duong. Vui long nhap lai." << endl;
            continue;
        } else {
            cin.ignore();
            break;
        }
    }
    addVariant(new Variant(size, color, quantity));

    char addMore;
    do {
        cout << "<!> Ban co muon them bien the khac cho san pham nay khong? (y/n): ";
        cin >> addMore;
        cin.ignore();
        if (addMore == 'y' || addMore == 'Y') {
            while (true) {
                cout << "<!> Nhap size (XS, S, M, L, XL, XXL, XXXL): ";
                getline(cin, size);
                size = toUpper(size);
                if (validSizes.find(size) != validSizes.end()) break;
                cout << "<!> Size khong hop le. Vui long nhap lai." << endl;
            }

            while (true) {
                cout << "<!> Nhap mau (Red, Blue, Green, Yellow, Black, White, Purple, Brown, Pink, Beige, Gray, Orange): ";
                getline(cin, color);
                color = nameStr(color);
                if (validColors.find(color) != validColors.end()) break;
                cout << "<!> Mau khong hop le. Vui long nhap lai." << endl;
            }

            while (true) {
             cout << "<!> Nhap so luong: ";
            cin >> quantity2;
            if(isCharacter(quantity2)){
            cout << "<!> So luong phai la so. Vui long nhap lai." << endl;
            continue;
            }
            quantity = stoi(quantity2);
            if (quantity <= 0) {
            cout << "<!> So luong phai la so duong. Vui long nhap lai." << endl;
            continue;
            } else {
            cin.ignore();
            break;
        }
    }
            addVariant(new Variant(size, color, quantity));
        }
    } while (addMore == 'y' || addMore == 'Y');
}