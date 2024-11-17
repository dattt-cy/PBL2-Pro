#ifndef MALE_H
#define MALE_H

#include "Clothes.h"
#include "support.h"
#include "Variant.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

class Male : public Clothes {
public:
    Male(const string &id, const string &name, double price, const string &branch, const string &size, const string &color, int quantity);
    void ReadFile(istream &filein) override;
    void WriteFile(ostream& fileout) const override;
    bool ReadInput() override;
};

#endif // MALE_H