#include "OrderManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void OrderManager::createOrder(ClothesManager& clothesManager) {
    int orderID;
    string customerName;
    string customerPhone;

    orderID = generateRandomOrderNumber();
    cin.ignore();
    cout << "Nhap ten khach hang: ";
    getline(cin, customerName);

    cout << "Nhap so dien thoai khach hang: ";
    getline(cin, customerPhone);

    Order* order = new Order(orderID, customerName, customerPhone);

    cout << "Ban quan tam den san pham nao? (1. Male, 2. Female, 3. Children, 4. All): ";
    int productType;
    cin >> productType;
    cin.ignore();
    cout << "==================== CLOTHES MENU ====================" << endl;
    switch (productType) {
        case 1:
            clothesManager.printByType("Male");
            break;
        case 2:
            clothesManager.printByType("Female");
            break;
        case 3:
            clothesManager.printByType("Children");
            break;
        case 4:
            clothesManager.printAllClothes();
            break;
        default:
            cout << "Lua chon khong hop le. Vui long thu lai." << endl;
            return;
    }
    cout << "======================================================" << endl;

    bool continueOrdering = true;
    int choice;
    do {
        continueOrdering = order->addClothesItem(clothesManager);

        if (!continueOrdering) {
            break;
        }

        cout << "<!> Ban co muon them san pham khong? (1: Co, 0: Khong): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 1);

    do {
        system("cls");
        order->displayOrder();
        cout << "\nBAN CO CHAC CHAN MUON THANH TOAN KHONG?" << endl;
        cout << "\n1. XAC NHAN THANH TOAN." << endl;
        cout << "\n2. CHINH SUA GIO HANG." << endl;
        cout << "\n0. HUY DON HANG." << endl;
        cout << "\nNhap lua chon cua ban: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                    clothesManager.writeClothesToFile("clothes.txt");
                    clothesManager.readClothesFromFile("clothes.txt");
                    system("cls");
                    checkoutOrder(order);
                    orders.addNode(order);
                    system("pause");
                break;
            }
            case 2: {
                system("cls");
                order->displayOrder();
                int subChoice;
                do {
                    cout << "\n2.1 CHINH SUA SAN PHAM." << endl;
                    cout << "\n2.2 THEM SAN PHAM VAO DON HANG." << endl;
                    cout << "\n2.3 XOA SAN PHAM KHOI DON HANG." << endl;
                    cout << "\n0. QUAY LAI MENU CHINH." << endl;
                    cout << "\nNhap lua chon cua ban: ";
                    cin >> subChoice;
                    cin.ignore();
                    string productTypee;
                    string productTypeee;
                    string itemID;
                    switch (subChoice) {
                        case 1: {
                            cout << "<!> Ban muon chinh sua san pham thuoc the loai nao? (1: Male, 2: Female, 3: Children, 4: All): ";
                            cin >> productType;
                            cin.ignore();
                            cout << "==================== CLOTHES MENU ====================" << endl;
                            switch (productType) {
                                case 1:
                                    clothesManager.printByType("Male");
                                    break;
                                case 2:
                                    clothesManager.printByType("Female");
                                    break;
                                case 3:
                                    clothesManager.printByType("Children");
                                    break;
                                case 4:
                                    clothesManager.printAllClothes();
                                    break;
                                default:
                                    cout << "Lua chon khong hop le. Vui long thu lai." << endl;
                                    break;
                            }
                            cout << "======================================================" << endl;
                            order->editItem(clothesManager);
                            system("pause");
                            break;
                        }
                        case 2:
            
                            cout << "<!> Ban muon them san pham thuoc the loai nao? (1: Male, 2: Female, 3: Children, 4: All): ";
                            cin >> productType;
                            cin.ignore();
                            cout << "==================== CLOTHES MENU ====================" << endl;
                            switch (productType) {
                                case 1:
                                    clothesManager.printByType("Male");
                                    break;
                                case 2:
                                    clothesManager.printByType("Female");
                                    break;
                                case 3:
                                    clothesManager.printByType("Children");
                                    break;
                                case 4:
                                    clothesManager.printAllClothes();
                                    break;
                                default:
                                    cout << "Lua chon khong hop le. Vui long thu lai." << endl;
                                    break;
                            }
                            cout << "======================================================" << endl;
                            order->addClothesItem(clothesManager);
                            system("pause");
                            break;
                        case 3: {
                            cout << "Nhap ma san pham can xoa: ";
                            cin >> itemID;
                            cin.ignore();
                            itemID = nameStr(itemID);
                            int check = order->removeItem(itemID, clothesManager);
                            if (check == 1) {
                                cout << "<!> XOA SAN PHAM THANH CONG." << endl;
                            }
                            system("pause");
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "LUA CHON KHONG HOP LE VUI LONG THU LAI." << endl;
                            system("pause");
                            break;
                    }
                    system("cls");
                    order->displayOrder();
                } while (subChoice != 0);
                break;
            }
            case 0:
                delete order;
                cout << "<!> THONG BAO DON HANG DA BI HUY." << endl;
                system("pause");
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai." << endl;
                system("pause");
                break;
        }
    } while (choice != 1 && choice != 0);
}



void OrderManager::checkoutOrder(Order* order) {
    order->printInvoice();
}
int OrderManager::generateRandomOrderNumber() {
    srand(time(NULL));  
    return rand() % 900 + 100;  
}

