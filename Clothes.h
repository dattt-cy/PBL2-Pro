#ifndef CLOTHES_H
#define CLOTHES_H

#include <string>
#include <map>
#include "Variant.h"
#include "LinkedList.h"

using namespace std;

class Clothes {
protected:
    string clothesID;
    string name;
    LinkedList<Variant*> variants; 
    double price;
    static int highestID;
    static map<char, int> highestIDMap; 
public:
    virtual void ReadFile(istream& filein);
    virtual void WriteFile(ostream& out) const;
    virtual void ReadInput() = 0;
    virtual void Print() const;
    Clothes(const string &id, const string &name);
    virtual string getID() const;
    string getName() const;
    virtual void setID(const string &id);
    static void updateHighestID(const string& id);
    static void decrementHighestID(char prefix);
    const LinkedList<Variant*>& getVariants() const;
    void addVariant(Variant* variant);
    virtual ~Clothes(); 
};

#endif // CLOTHES_H