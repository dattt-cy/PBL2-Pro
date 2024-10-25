#include "Clothes.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

int Clothes::highestID = 0;
map<char, int> Clothes::highestIDMap;

Clothes::Clothes(const string& id, const string& name, const string& branch)
    : clothesID(id), name(name), branch(branch), price(0.0) {}

string Clothes::getID() const {
    return clothesID;
}

string Clothes::getName() const {
    return name;
}

string Clothes::getBranch() const {
    return branch;
}
double Clothes::getPrice() const {
    return price;
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
    cout << left << setw(10) << clothesID
         << setw(15) << name
         << setw(15) << branch
         << setw(10) << price;

    stringstream ss;
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        ss << "{Size: " << current->data->getSize()
           << ", Mau: " << current->data->getColor()
           << ", SL: " << current->data->getQuantity() << "} ";
        current = current->next;
    }
    cout << setw(50) << ss.str() << endl;
}

void Clothes::ReadFile(istream& filein) {
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

void Clothes::WriteFile(ostream& fileout) const {
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

void Clothes::Edit(const string& newName, double newPrice, const string& newBranch, const LinkedList<Variant*>& newVariants) {
    name = newName;
    price = newPrice;
    branch = newBranch; // Cập nhật branch
    Node<Variant*>* current = newVariants.getHead();
    while (current != nullptr) {
        variants.push_back(new Variant(current->data->getSize(), current->data->getColor(), current->data->getQuantity()));
        current = current->next;
    }
}

void Clothes::clearVariants() {
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        delete current->data;
        current = current->next;
    }
    variants.clear();
}

Clothes::~Clothes() {
    clearVariants();
}
bool Clothes::hasColor(const string& color) const {
    Node<Variant*>* current = variants.getHead();
    while(current != nullptr)
    {
        if(current->data->getColor() == color){
            return true;
        }
        current = current->next;
    }
    return false;
}
bool Clothes::hasSize(const string& color, const string& size) const {
    Node<Variant*>* current = variants.getHead();
    while(current != nullptr)
    {
        if(current->data->getColor() == color && current->data->getSize() == size){
            return true;
        }
        current = current->next;
    }
    return false;
}
bool Clothes::checkQuantity(const string& color, const string& size, int quantity) const {
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        if (current->data->getColor() == color && current->data->getSize() == size) {
            return quantity <= current->data->getQuantity();
        }
        current = current->next;
    }
    return false;
}
void Clothes::UpdateSL(const string& color, const string& size, int quantity) {
    Node<Variant*>* current = variants.getHead();
    while(current != nullptr)
    {
        if(current->data->getColor() == color && current->data->getSize() == size){
            current->data->setQuantity(current->data->getQuantity() - quantity);
            return;
        }
        current = current->next;
    }
}
void Clothes::increaseSL(const string& color, const string& size, int quantity) {
    Node<Variant*>* current = variants.getHead();
    while (current != nullptr) {
        if (current->data->getColor() == color && current->data->getSize() == size) {
            current->data->setQuantity(current->data->getQuantity() + quantity);
            return;
        }
        current = current->next;
    }
}
int Clothes::getTotalQuantity() const {
    int totalQuantity = 0;
    Node<Variant*>* current = variants.getHead();
    while (current) {
        totalQuantity += current->data->getQuantity();
        current = current->next;
    }
    return totalQuantity;
}