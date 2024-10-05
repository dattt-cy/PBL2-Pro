#include "Clothes.h"
#include <iostream>
#include <sstream>


using namespace std;

int Clothes::highestID = 0;
map<char, int> Clothes::highestIDMap;

Clothes::Clothes(const string& id, const string& name)
    : clothesID(id), name(name), price(0.0) {}

string Clothes::getID() const {
    return clothesID;
}

string Clothes::getName() const {
    return name;
}

void Clothes::setID(const string& newID) {
    clothesID = newID;
}

void Clothes::updateHighestID(const string& id) {
    char prefix = id[0];
    int numericID = stoi(id.substr(1));
    if (highestIDMap.find(prefix) == highestIDMap.end() || numericID > highestIDMap[prefix]) {
        highestIDMap[prefix] = numericID;
    }
}
void Clothes::decrementHighestID(char prefix) {
    if (highestIDMap.find(prefix) != highestIDMap.end() && highestIDMap[prefix] > 0) {
        highestIDMap[prefix]--;
    }
}

const LinkedList<Variant*>& Clothes::getVariants() const {
    return variants;
}

void Clothes::addVariant(Variant* variant) {
    variants.push_back(variant);
}

void Clothes::Print() const {
    cout << "ID: " << clothesID << ", Ten: " << name << ", Gia: " << price << endl;
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        if(current->data->getSize() != "" && current->data->getColor() != "" && current->data->getQuantity() != 0)
        {
        cout << "  Size: " << current->data->getSize()
             << ", Mau: " << current->data->getColor()
             << ", So luong: " << current->data->getQuantity() << endl;
        }
        current = current->next;
    }
}
void Clothes::ReadFile(istream& filein) {
    string line;
    if (getline(filein, line)) {
        stringstream ss(line);
        getline(ss, clothesID, ',');
        getline(ss, name, ',');
        ss >> price;
        ss.ignore();

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
void Clothes::WriteFile(ostream& fileout) const {
    fileout << clothesID << "," << name << "," << price;
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        // Kiểm tra các giá trị của Variant trước khi ghi vào tệp
        if (!current->data->getSize().empty() && 
            !current->data->getColor().empty() && 
            current->data->getQuantity() != 0) {
            fileout << "," << current->data->getSize() << "," << current->data->getColor() << "," << current->data->getQuantity();
        }
        current = current->next;
    }
    fileout << endl;
}

Clothes::~Clothes() {
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        delete current->data;
        current = current->next;
    }
}