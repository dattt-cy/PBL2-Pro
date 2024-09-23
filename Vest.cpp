// Vest.cpp
#include "Vest.h"
#include <iostream>
#include <sstream>

void Vest::ReadFile(std::istream& filein) {
    Clothes::ReadFile(filein);
}

void Vest::ReadInput() {
    char prefix = 'V';
    highestIDMap[prefix]++; 
    clothesID = prefix + to_string(highestIDMap[prefix]);
    std::cout << "Ma quan ao (tu dong): " << clothesID << std::endl;
    std::cout << "Nhap ten quan ao: ";
    std::getline(cin, name);
    std::cout << "Nhap kich co (S, M, L, XL, ...): ";
    std::getline(cin, size);
    std::cout << "Nhap mau sac: ";
    std::getline(cin, color);
    std::cout << "Nhap gia: ";
    std::cin >> price;
    std::cout << "Nhap so luong: ";
    std::cin >> quantity;
    std::cin.ignore(); 
    std::cout << "-----------------------------------------" << std::endl;
}