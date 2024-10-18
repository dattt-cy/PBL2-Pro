#include "menu.h"
#include <iostream>

using namespace std;

void menu(ClothesManager& manager, OrderManager& orderManager) {
    manager.readClothesFromFile("CLOTHES.txt");
    manager.Sort_ByID();
    
    while (true) {
        system("cls");
        cout << "\n==================^^SHOP QUAN AO GAU GAU^^==================="<<endl;
        cout << "\n 1. XEM QUAN AO";
        cout << "\n 2. TIM KIEM QUAN AO";
        cout << "\n 3. CHINH SUA QUAN AO THEO ID";
        cout << "\n 4. XOA QUAN AO THEO ID";
        cout << "\n 5. LUU VAO FILE";
        cout << "\n 6. DAT HANG";
        cout << "\n 0. THOAT";
        cout << endl;
         cout << "\n===========================WELCOME===========================" << endl;
        int choice;
        cout << "\nNhap lua chon: ";
        cin >> choice;
        switch (choice) {
        case 1: {
        system("cls");
         int subChoice = 0;
        while (subChoice != 5) { // Bắt đầu vòng lặp
            cout << "\n 1.1 XEM QUAN AO DANH CHO NAM";
            cout << "\n 1.2 XEM QUAN AO DANH CHO NU";
            cout << "\n 1.3 XEM QUAN AO DANH CHO TRE EM";
            cout << "\n 1.4 XEM TAT CA QUAN AO";
            cout << "\n 1.5 THOAT";
            cout << "\nChon loai quan ao: ";
           
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
                    manager.printAllClothes();
                    break;
                case 5: 
                    break; // Hoặc dùng break; để thoát ra ngoài case 1
                default:
                    cout << "<!> Lua chon khong hop le!" << endl;
            }
        }
             break;
        }

            case 2: {
                system("cls");
                cout << "\n 2.1 TIM KIEM THEO TEN QUAN AO";
                cout << "\n 2.2 TIM KIEM THEO THUONG HIEU QUAN AO";
                cout << "\n 2.3 TIM KIEM THEO THE LOAI QUAN AO";
                cout << "\n 2.4 TIM KIEM THEO MAU SAC QUAN AO";
                cout << "\n 2.5 TIM KIEM THEO SIZE QUAN AO";
                cout << "\n 2.6 TIM KIEM KET HOP"; 
                cout << "\n[!] Chon kieu tim kiem: ";
                int searchChoice;
                cin >> searchChoice;
                string name, brand, type, color, size;
                switch (searchChoice) {
                    case 1: {
                        system("cls");
                        cout << "<!> Nhap mot phan hoac toan bo ten san pham can tim: ";
                        cin.ignore();
                        getline(cin, name);
                        manager.SearchBySubstring(name, "", "", "", "All"); // Tìm kiếm theo tên
                        system("pause");
                        break;
                    }
                    case 2: {
                        system("cls");
                        cout << "<!> Nhap mot phan hoac toan bo ten thuong hieu can tim: ";
                        cin.ignore();
                        getline(cin, brand);
                        manager.SearchBySubstring("", brand, "", "", "All"); // Tìm kiếm theo thương hiệu
                        system("pause");
                        break;
                    }
                    case 3: {
                        system("cls");
                        cout << "<!> Nhap mot the loai quan ao (Male/Female/Children): ";
                        cin.ignore();
                        getline(cin, type);
                        manager.SearchBySubstring("", "", "", "", type); // Tìm kiếm theo loại quần áo
                        system("pause");
                        break;
                    }
                    case 4: {
                        system("cls");
                        cout << "<!> Nhap mot phan hoac toan bo mau sac quan ao can tim: ";
                        cin.ignore();
                        getline(cin, color);
                        manager.SearchBySubstring("", "", color, "", "All"); // Tìm kiếm theo màu sắc
                        system("pause");
                        break;
                    }
                    case 5: {
                        system("cls");
                        cout << "<!> Nhap mot phan hoac toan bo size can tim: ";
                        cin.ignore();
                        getline(cin, size);
                        manager.SearchBySubstring("", "", "", size, "All"); 
                        system("pause");
                        break;
                    }
                    case 6: { 
                        system("cls");
                        cout << "<!> Nhap mot phan hoac toan bo ten san pham (hoac de trong): ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "<!> Nhap mot phan hoac toan bo ten thuong hieu (hoac de trong): ";
                        getline(cin, brand);
                        cout << "<!> Nhap loai quan ao (Male/Female/Children hoac de trong): ";
                        getline(cin, type);
                        cout << "<!> Nhap mot phan hoac toan bo mau sac (hoac de trong): ";
                        getline(cin, color);
                        cout << "<!> Nhap mot phan hoac toan bo size (hoac de trong): ";
                        getline(cin, size);
                        
                        manager.SearchBySubstring(name, brand, color, size, type); 
                        system("pause");
                        break;
                    }
                    default:
                        cout << "<!> Lua chon khong hop le!" << endl;
                }
                break;
            }
            case 3: {
                system("cls");
                string id;
                cout << "<!> Nhap ma ID quan ao can chinh sua: ";
                cin >> id;
                manager.EditClothesByID(id);
                break;
                system("pause");
            }
            case 4: { 
                system("cls");
                string id;
                cout << "<!> Nhap ma ID quan ao can xoa: ";
                cin >> id;
                manager.removeClothesByID(id);
                break;
            }
            case 5: {
                system("cls");
                manager.writeClothesToFile("CLOTHES.txt");
                cout << "<!> Da luu danh sach quan ao vao file CLOTHES.txt" << endl;
                break;
            }
            case 6:{
                orderManager.createOrder(manager);
                break;
            }
            case 0:
                return;  
            default:
                cout << "<!> Lua chon khong hop le!" << endl;
        }
    }
}
