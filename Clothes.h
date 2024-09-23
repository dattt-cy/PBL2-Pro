#ifndef CLOTHES_H
#define CLOTHES_H
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Clothes {
protected:
    string clothesID;
    string name;
    string size;
    string color;
    double price;
    int quantity;
    static int highestID;
    static map<char, int> highestIDMap; 

public:
    virtual void ReadFile(istream& filein);
    virtual void ReadInput() = 0;
    virtual void Print();
    virtual string getID();
    virtual void setID(string id);
    static void updateHighestID(const std::string& id);
};

#endif
