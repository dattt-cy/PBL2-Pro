#ifndef VARIANT_H
#define VARIANT_H

#include <string>
using namespace std;
class Variant {
private:
    std::string size;
    std::string color;
    int quantity;

public:
    Variant(const string& size, const string& color, int quantity);
    string getSize() const;
    string getColor() const;
    int getQuantity() const;
    void setQuantity(int quantity);
};

#endif // VARIANT_H