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
    string branch;
    static int highestID;
    static map<char, int> highestIDMap; 
public:
    virtual void ReadFile(istream& filein);
    virtual void WriteFile(ostream& out) const;
    virtual bool ReadInput() = 0;
    virtual void Print() const;
    Clothes(const string &id, const string &name, const string &branch);
    virtual string getID() const;
    string getName() const;
    string getBranch() const;
    double getPrice() const;
    virtual void setID(const string &id);
    static void updateHighestID(const string& id);
    static void decrementHighestID(char prefix);
    const LinkedList<Variant*>& getVariants() const;
    void addVariant(Variant* variant);
    void Edit(const string& newName, double newPrice, const string& newBranch, const LinkedList<Variant*>& newVariants);
    void clearVariants();
    virtual ~Clothes(); 
    bool hasColor(const string& color) const;
    bool hasSize(const string& color,const string &size) const;
    bool checkQuantity(const string& color, const string& size, int quantity) const; 
    void UpdateSL(const string& color, const string& size, int quantity);
    void increaseSL(const string& color, const string& size, int quantity);
     int getTotalQuantity() const;
    void copyVariants(const LinkedList<Variant*>& newVariants);
};

#endif // CLOTHES_H