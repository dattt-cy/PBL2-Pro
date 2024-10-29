#include "OrderManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

void OrderManager::createOrder(ClothesManager& clothesManager) {
    int orderID;
    string customerName;
    string customerPhone;

    orderID = generateRandomOrderNumber();
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
            clothesManager.printByType("1");
            break;
        case 2:
            clothesManager.printByType("2");
            break;
        case 3:
            clothesManager.printByType("3");
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

        cout << "<!> Ban co muon tiep tuc them san pham khong? (1: Male, 2: Female, 3: Children, 4: All, 0: Khong): ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            break;
        }
        cout << "==================== CLOTHES MENU ====================" << endl;
        switch (choice) {
            case 1:
                clothesManager.printByType("1");
                break;
            case 2:
                clothesManager.printByType("2");
                break;
            case 3:
                clothesManager.printByType("3");
                break;
            case 4:
                clothesManager.printAllClothes();
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai." << endl;
                continue;
        }
        cout << "======================================================" << endl;
    } while (true);
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
                                    clothesManager.printByType("1");
                                    break;
                                case 2:
                                    clothesManager.printByType("2");
                                    break;
                                case 3:
                                    clothesManager.printByType("3");
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
                                    clothesManager.printByType("1");
                                    break;
                                case 2:
                                    clothesManager.printByType("2");
                                    break;
                                case 3:
                                    clothesManager.printByType("3");
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
                order->restoreItems(clothesManager);
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

void OrderManager::generateStatistics() {
    double totalRevenue = 0.0;
    double totalDiscount = 0.0;
    int totalItemsSold = 0;
    int totalOrders = 0;

    map<string, int> productQuantities;
    map<string, double> productRevenues;

    Node<Order*>* currentOrder = orders.getHead();
    while (currentOrder) {
        totalOrders++;
        totalRevenue += currentOrder->data->getTotalRevenue();
        totalDiscount += currentOrder->data->getDiscountAmount();
        totalItemsSold += currentOrder->data->getTotalItemsSold();

        currentOrder->data->ProductStats(productQuantities, productRevenues);

        currentOrder = currentOrder->next;
    }

    cout << "==================== THONG KE ====================" << endl;
    cout << "Tong so don hang: " << totalOrders << endl;
    cout << "Tong san pham da ban: " << totalItemsSold << endl;
    cout << "Tong tien giam gia: " << totalDiscount << " VND" << endl;
    cout << "Tong doanh thu: " << totalRevenue << " VND" << endl;

    string bestSeller = "", nonSeller = "";
    int maxSales = 0, minSales = INT_MAX;

    for (const auto& entry : productQuantities) {
        if (entry.second > maxSales) {
            maxSales = entry.second;
        }
        if (entry.second < minSales) {
            minSales = entry.second;
        }
    }
    if(maxSales == minSales){
        cout << "<!> San pham ban chay nhat: ";
        for(const auto& entry : productQuantities){
            if(entry.second == maxSales){
                cout << entry.first << " ";
            }
        }
        cout << "voi " << maxSales << " san pham" << endl;
    } else {
        cout << "<!> San pham ban chay nhat: ";
        for(const auto& entry : productQuantities){
            if(entry.second == maxSales){
                cout << entry.first << ", ";
            }
        }
        cout << "voi " << maxSales << " san pham" << endl;
        cout << "<!> San pham ban it nhat: ";
        for(const auto& entry : productQuantities){
            if(entry.second == minSales){
                cout << entry.first << ", ";
            }
        }
        cout << "voi " << minSales << " san pham" << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
    cout << left << setw(20) << "Ten san pham"
         << setw(15) << "So luong"
         << setw(20) << "Doanh thu (VND)"
         << "Phan tram (%)" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (const auto& entry : productQuantities) {
        const string& itemName = entry.first;
        int quantity = entry.second;
        double revenue = productRevenues[itemName];
        double percentRevenue = (totalRevenue > 0) ? (revenue / totalRevenue) * 100 : 0;

        cout << left << setw(20) << itemName
             << setw(15) << quantity
             << setw(20) << fixed << setprecision(0) << revenue
             << fixed << setprecision(2) << percentRevenue << "%" << endl;
    }

    cout << "===================================================" << endl;
}