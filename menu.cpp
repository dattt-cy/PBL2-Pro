#include "menu.h"
#include "ReadFile.h"  // Thêm header cho ReadFile

void menu(LinkedList<Clothes*>& list) {
    // Đọc dữ liệu từ file khi bắt đầu
    readClothesFromFile("CLOTHES.txt", list);

    while (true) {
        cout << "\n\n\t\t===== MENU =====";
        cout << "\n1. Xem toan bo san pham";
        cout << "\n2. Xem san pham Dress";
        cout << "\n3. Xem san pham Vest";
        cout << "\n0. Thoat";
        cout << "\n\n\t\t================";
        
        int choice;
        cout << "\nNhap lua chon: ";
        cin >> choice;

        if (choice == 1) {
            list.printList();  // Hiển thị toàn bộ danh sách sản phẩm
        } else if (choice == 2) {
            list.printByType<Dress>();  // Hiển thị sản phẩm Dress
        } else if (choice == 3) {
            list.printByType<Vest>();  // Hiển thị sản phẩm Vest
        } else if (choice == 0) {
            break;  // Thoát khỏi vòng lặp
        } else {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
}
