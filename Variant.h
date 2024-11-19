#ifndef VARIANT_H
#define VARIANT_H

#include <string>

using namespace std;

class Variant {
private:
    string color;
    string size;
    int quantity;
public:
    Variant(const string& color, const string& size, int quantity);
    string getColor() const;
    string getSize() const;
    int getQuantity() const;
    void setQuantity(int quantity);
    void setColor(const string& color);
    void setSize(const string& size);
};

#endif // VARIANT_H