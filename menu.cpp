#include "menu.h"
#include <iostream>

void menu(ClothesManager& manager) {
    manager.readClothesFromFile("CLOTHES.txt");

    while (true) {
        std::cout << "\n\n\t\t===== MENU =====";
        std::cout << "\n1. Xem toan bo san pham";
        std::cout << "\n2. Xem san pham Dress";
        std::cout << "\n3. Xem san pham Vest";
        std::cout << "\n4. Them san pham moi";
        std::cout << "\n5. Ghi vao file";
        std::cout << "\n0. Thoat";
        std::cout << "\n\n\t\t================";
        
        int choice;
        std::cout << "\nNhap lua chon: ";
        std::cin >> choice;

        if (choice == 1) {
            manager.printAllClothes();  
        } else if (choice == 2) {
            manager.printByType("Dress");  
        } else if (choice == 3) {
            manager.printByType("Vest");  
        } else if (choice == 4) {
            manager.addClothesManually();  
            manager.Sort_ByID();
        } else if (choice == 5){
            manager.writeClothesToFile("CLOTHES.txt");

        } else if (choice == 0) {
            break;  
        } else {
            std::cout << "Lua chon khong hop le!" << std::endl;
        }
    }
}