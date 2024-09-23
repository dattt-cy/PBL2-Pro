#ifndef CLOTHES_H
#define CLOTHES_H

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

public:
    virtual void ReadFile(istream& filein);
    virtual void Print();
    string getID();
};

class Vest : public Clothes {
public:
    void ReadFile(istream& filein) override;
};

class Dress : public Clothes {
public:
    void ReadFile(istream& filein) override;
};

#endif
