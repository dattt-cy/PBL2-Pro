#ifndef DRESS_H
#define DRESS_H

#include "Clothes.h"

class Dress : public Clothes {
public:
    void ReadFile(istream& filein) override;
    void ReadInput() override;
};

#endif