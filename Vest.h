
#ifndef VEST_H
#define VEST_H

#include "Clothes.h"

class Vest : public Clothes {
public:
    void ReadFile(std::istream& filein) override;
    void ReadInput() override;
};

#endif 