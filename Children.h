#ifndef CHILDREN_H
#define CHILDREN_H

#include "Clothes.h"
#include "Variant.h"
#include <string>
#include <vector>
#include "support.h"
using namespace std;

class Children : public Clothes {
public:
    Children(const string &id, const string &name, double price, const string &branch, const string &size, const string &color, int quantity);
    void ReadFile(istream &filein) override;
    void WriteFile(ostream &fileout) const override;
    void ReadInput() override;
};

#endif // CHILDREN_H