#include "Dress.h"
#include <iostream>
#include <sstream>

void Dress::ReadFile(std::istream& filein) {
    Clothes::ReadFile(filein);
}

void Dress::ReadInput() {
    char prefix = 'D';
    highestIDMap[prefix]++; 
    clothesID = prefix + std::to_string(highestIDMap[prefix]); 
    std::cout << "Ma quan ao (tu dong): " << clothesID << std::endl;
    std::cout << "Nhap ten quan ao: ";
    std::getline(std::cin, name);
    std::cout << "Nhap kich co (S, M, L, XL, ...): ";
    std::getline(std::cin, size);
    std::cout << "Nhap mau sac: ";
    std::getline(std::cin, color);
    std::cout << "Nhap gia: ";
    std::cin >> price;
    std::cout << "Nhap so luong: ";
    std::cin >> quantity;
    std::cin.ignore(); 
    std::cout << "-----------------------------------------" << std::endl;
}