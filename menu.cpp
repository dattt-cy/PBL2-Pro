#include "menu.h"
#include <iostream>

using namespace std;

void menu(ClothesManager& manager) {
    manager.readClothesFromFile("CLOTHES.txt");
    manager.Sort_ByID();
    
    while (true) {
        cout << "\n\n\t\t===== MENU =====";
        cout << "\n1. Xem quan ao";
        cout << "\n2. Tim kiem quan ao";
        cout << "\n3. Chinh sua quan ao theo ID";
        cout << "\n4. Xoa quan ao theo ID";
        cout << "\n5. Luu vao file";
        cout << "\n0. Thoat";
        cout << "\n\n\t\t================";
        
        int choice;
        cout << "\nNhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                system("cls");
                cout << "\n\t1. Xem quan ao";
                cout << "\n\t1.1 Xem quan ao dan ong";
                cout << "\n\t1.2 Xem quan ao phu nu";
                cout << "\n\t1.3 Xem quan ao tre em";
                cout << "\n\t1.4 Xem toan bo quan ao";
                cout << "\nChon loai quan ao: ";
                int subChoice;
                cin >> subChoice;

                switch (subChoice) {
                    case 1:
                        manager.printByType("Male");
                        break;
                    case 2:
                        manager.printByType("Female");
                        break;
                    case 3:
                        manager.printByType("Children");
                        break;
                    case 4:
                        manager.printAllClothes(); // Giả sử bạn đã định nghĩa hàm này
                        break;
                    default:
                        cout << "Lua chon khong hop le!" << endl;
                }
                break;
            }
            case 2: {
                system("cls");
                cout << "\n\t2. Tim kiem quan ao";
                cout << "\n\t2.1 Tim theo ten san pham";
                cout << "\n\t2.2 Tim theo thuong hieu";
                cout << "\n\t2.3 Tim theo loai quan ao";
                cout << "\n\t2.4 Tim theo mau sac";
                cout << "\n\t2.5 Tim theo size";
                cout << "\n\t2.6 Tim kiem tong hop"; 
                cout << "\nChon kieu tim kiem: ";
                
                int searchChoice;
                cin >> searchChoice;
                string name, brand, type, color, size;

                switch (searchChoice) {
                    case 1: {
                        cout << "Nhap ten san pham can tim: ";
                        cin.ignore();
                        getline(cin, name);
                        manager.SearchBySubstring(name, "", "", "", "All"); // Tìm kiếm theo tên
                        break;
                    }
                    case 2: {
                        cout << "Nhap thuong hieu can tim: ";
                        cin.ignore();
                        getline(cin, brand);
                        manager.SearchBySubstring("", brand, "", "", "All"); // Tìm kiếm theo thương hiệu
                        break;
                    }
                    case 3: {
                        cout << "Nhap loai quan ao (Male/Female/Children): ";
                        cin.ignore();
                        getline(cin, type);
                        manager.SearchBySubstring("", "", "", "", type); // Tìm kiếm theo loại quần áo
                        break;
                    }
                    case 4: {
                        cout << "Nhap mau sac can tim: ";
                        cin.ignore();
                        getline(cin, color);
                        manager.SearchBySubstring("", "", "color", "", "All"); // Tìm kiếm theo màu sắc
                        break;
                    }
                    case 5: {
                        cout << "Nhap size can tim: ";
                        cin.ignore();
                        getline(cin, size);
                        manager.SearchBySubstring("", "", "", "size", "All"); // Tìm kiếm theo kích thước
                        break;
                    }
                    case 6: { // Chức năng tìm kiếm tổng hợp
                        cout << "Nhap ten san pham (hoac de trong): ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Nhap thuong hieu (hoac de trong): ";
                        getline(cin, brand);
                        cout << "Nhap loai quan ao (Male/Female/Children hoac de trong): ";
                        getline(cin, type);
                        cout << "Nhap mau sac (hoac de trong): ";
                        getline(cin, color);
                        cout << "Nhap size (hoac de trong): ";
                        getline(cin, size);
                        
                        manager.SearchBySubstring(name, brand, color, size, type); // Tìm kiếm tổng hợp
                        break;
                    }
                    default:
                        cout << "Lua chon khong hop le!" << endl;
                }
                break;
            }
            case 3: {
                system("cls");
                string id;
                cout << "Nhap ID san pham can chinh sua: ";
                cin >> id;
                manager.EditClothesByID(id);
                break;
            }
            case 4: { 
                system("cls");
                string id;
                cout << "Nhap ID san pham can xoa: ";
                cin >> id;
                manager.removeClothesByID(id);
                break;
            }
            case 5: {
                system("cls");
                manager.writeClothesToFile("CLOTHES.txt");
                break;
            }
            case 0:
                return;  
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    }
}
