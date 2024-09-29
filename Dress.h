#ifndef DRESS_H
#define DRESS_H

#include "Clothes.h"

class Dress : public Clothes {
public:
    void ReadFile(std::istream& filein) override;
    void WriteFile(std::ostream& fileout) const override;
    void ReadInput() override;
};

#endif // DRESS_H