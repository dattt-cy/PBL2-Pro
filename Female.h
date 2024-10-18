#ifndef FEMALE_H
#define FEMALE_H

#include "Clothes.h"

class Female : public Clothes {
public:
    Female(const string &id, const string &name, double price, const string &branch, const string &size, const string &color, int quantity);
    void ReadFile(istream &filein) override;
    void WriteFile(ostream& fileout) const override;
    void ReadInput() override;
};

#endif // FEMALE_H