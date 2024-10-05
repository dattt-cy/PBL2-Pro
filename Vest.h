
#ifndef VEST_H
#define VEST_H

#include "Clothes.h"

class Vest : public Clothes {
public:
    Vest(const string &id, const string &name, double price, const string &size, const string &color, int quantity);
    void ReadFile(istream &filein) override;
    void WriteFile(ostream& fileout) const override;
    void ReadInput() override;
};

#endif 