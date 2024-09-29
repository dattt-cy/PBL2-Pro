#ifndef CLOTHES_H
#define CLOTHES_H
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include "Variant.h"
using namespace std;

class Clothes {
protected:
    string clothesID;
    string name;
    vector<Variant> variants;
    double price;
    static int highestID;
    static map<char, int> highestIDMap; 

public:
    virtual void ReadFile(istream& filein);
    virtual void WriteFile(ostream& out) const = 0;
    virtual void ReadInput() = 0;
    virtual void Print();
    virtual string getID();
    virtual void setID(string id);
    static void updateHighestID(const std::string& id);
    static void decrementHighestID(char prefix);
    const vector<Variant>& getVariants() const;
    void setVariant(const Variant& variants);
};

#endif
