#include "Variant.h"

Variant::Variant(const string& size, const string& color, int quantity)
    : size(size), color(color), quantity(quantity) {}


string Variant::getSize() const {
    return size;
}

string Variant::getColor() const {
    return color;
}

int Variant::getQuantity() const {
    return quantity;
}

void Variant::setQuantity(int quantity) {
    this->quantity = quantity;
}
