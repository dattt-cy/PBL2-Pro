#include "menu.h"
#include "ReadFile.h"

void menu(LinkedList<Clothes*>& list) {
    readClothesFromFile("CLOTHES.txt", list);

    while (true) {
        cout << "\n\n\t\t===== MENU =====";
        cout << "\n1. Xem toan bo san pham";
        cout << "\n2. Xem san pham Dress";
        cout << "\n3. Xem san pham Vest";
        cout << "\n4. Them san pham moi";
        cout << "\n0. Thoat";
        cout << "\n\n\t\t================";
        
        int choice;
        cout << "\nNhap lua chon: ";
        cin >> choice;

        if (choice == 1) {
            list.printList();  
        } else if (choice == 2) {
            list.printByType<Dress>();  
        } else if (choice == 3) {
            list.printByType<Vest>();  
        } else if (choice == 4) {
            addClothesManually(list);  
        } else if (choice == 0) {
            break;  
        } else {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
}