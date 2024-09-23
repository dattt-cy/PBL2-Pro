
#ifndef VEST_H
#define VEST_H

#include "Clothes.h"

class Vest : public Clothes {
public:
    void ReadFile(istream& filein) override;
    void ReadInput() override;
    void WriteFile(ostream& out) const override;
};

#endif 