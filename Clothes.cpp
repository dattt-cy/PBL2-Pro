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

    filein >> price; 
    filein.ignore(); 

    string size, color;
    int quantity;
    while (filein.peek() != '\n' && filein.peek() != EOF) {
        getline(filein, size, ',');
        filein.ignore(); 
        getline(filein, color, ',');
        filein.ignore(); 
        filein >> quantity;
        filein.ignore(); 
        variants.emplace_back(size, color, quantity);
    }
}
void Clothes::ReadInput(){}

void Clothes::Print() {
    cout << "ID: " << clothesID << ", Name: " << name << ", Price: " << price << endl;
    for (const auto& variant : variants) {
        cout << "  Size: " << variant.getSize() << ", Color: " << variant.getColor() << ", Quantity: " << variant.getQuantity() << endl;
    }
}

string Clothes::getID() {
    return clothesID;
}
void Clothes::setID(string id) {
    clothesID = id;
}
void Clothes::decrementHighestID(char prefix) {
    if (highestIDMap.find(prefix) != highestIDMap.end() && highestIDMap[prefix] > 0) {
        highestIDMap[prefix]--;
    }
}
void Clothes::setVariant(const Variant& variant) {
    variants.push_back(variant);
}
const vector<Variant>& Clothes::getVariants() const {
    return variants;
}