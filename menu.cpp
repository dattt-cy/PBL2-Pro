#include "menu.h"
#include <iostream>

using namespace std;

void menu(ClothesManager& manager) {
    manager.readClothesFromFile("CLOTHES.txt");

    while (true) {
        cout << "\n\n\t\t===== MENU =====";
        cout << "\n1. Xem toan bo san pham";
        cout << "\n2. Xem san pham Dress";
        cout << "\n3. Xem san pham Vest";
        cout << "\n4. Them san pham moi";
        cout << "\n5. Ghi vao file";
        cout << "\n6. Xoa san pham theo ID"; 
        cout << "\n0. Thoat";
        cout << "\n\n\t\t================";
        
        int choice;
        cout << "\nNhap lua chon: ";
        cin >> choice;

        if (choice == 1) {
            manager.printAllClothes();  
        } else if (choice == 2) {
            manager.printByType("Dress");  
        } else if (choice == 3) {
            manager.printByType("Vest");  
        } else if (choice == 4) {
            manager.addClothesManually();  
            manager.Sort_ByID();
        } else if (choice == 5) {
            manager.writeClothesToFile("CLOTHES.txt");
        } else if (choice == 6) { 
            string id;
            cout << "Nhap ID san pham can xoa: ";
            cin >> id;
            manager.removeClothesByID(id);
        } else if (choice == 0) {
            break;  
        } else {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
}