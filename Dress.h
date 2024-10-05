#ifndef DRESS_H
#define DRESS_H

#include "Clothes.h"
using namespace std;
class Dress : public Clothes {
public:
    Dress(const string &id, const string &name, double price, const string &size, const string &color, int quantity);
    void ReadFile(istream &filein) override;
    void WriteFile(ostream& fileout) const override;
    void ReadInput() override;
};

#endif // DRESS_H