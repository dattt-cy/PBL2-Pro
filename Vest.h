
#ifndef VEST_H
#define VEST_H

#include "Clothes.h"

class Vest : public Clothes {
public:
    void ReadFile(std::istream& filein) override;
    void WriteFile(std::ostream& fileout) const override;
    void ReadInput() override;
};

#endif 