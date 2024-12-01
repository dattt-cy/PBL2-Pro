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
    customerName = Admin_Manage::name;
    customerPhone = Admin_Manage::phone;


    Order* order = new Order(orderID, customerName, customerPhone);

    cout << "Ban quan tam den san pham nao? (1. Male, 2. Female, 3. Children, 4. All): ";
    string product;
    getline(cin, product);
    if(isCharacter(product)){
        cout << "Lua chon khong hop le. Vui long thu lai." << endl;
        return;
    }
    int productType = atoi(product.c_str());
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
        if(order->getItems().isEmpty()){
            cout << "<!> GIO HANG CUA BAN DANG TRONG. VUI LONG THEM SAN PHAM VAO GIO HANG." << endl;
            break;
        }
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
                    order->saveOrderToFile("DoanhThu.txt");
                    order->writeInvoiceToFile(Admin_Manage::id, Admin_Manage::name, Admin_Manage::phone);
                    orders.addNode(order);
                break;
            }
            case 2: {
                system("cls");
                if(order->getItems().isEmpty()){
                    cout << "<!> GIO HANG CUA BAN DANG TRONG. VUI LONG THEM SAN PHAM VAO GIO HANG." << endl;
                    break;
                }
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
                            do{
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
                            }while(productType != 1 && productType != 2 && productType != 3 && productType != 4);
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

void OrderManager::generateStatistics(int day, int month, int year, const string& filterType) {
  
    double totalRevenue = 0.0;
    int totalItemsSold = 0;
    double totalSales = 0.0;

    map<string, double> orderCount;
    map<string, int> productQuantities;
    map<string, double> productRevenues;

    Node<Order*>* currentOrder = orders.getHead();
    while (currentOrder) {
        if (currentOrder->data->containsItemsMatching(day, month, year, filterType)) {
            Node<OrderItem*>* currentItem = currentOrder->data->getItems().getHead();
            while (currentItem) {
                const Datee& orderDate = currentItem->data->orderDate;
                bool includeOrder = false;
           
                if (filterType == "day" && orderDate.day == day && orderDate.month == month && orderDate.year == year) {
                    includeOrder = true;
                } else if (filterType == "month" && day == 0 && orderDate.month == month && orderDate.year == year) {
                    includeOrder = true;
                } else if (filterType == "year" && orderDate.year == year) {
                    includeOrder = true;
                }

                if (includeOrder) {
                    orderCount[currentItem->data->getOrderID2()]+=currentItem->data->price * currentItem->data->quantity;
                    totalRevenue += currentItem->data->price * currentItem->data->quantity;
                    totalItemsSold += currentItem->data->quantity;

                    productQuantities[currentItem->data->itemName] += currentItem->data->quantity;
                    productRevenues[currentItem->data->itemName] += currentItem->data->price * currentItem->data->quantity;
                }

                currentItem = currentItem->next;
            }
        }

        currentOrder = currentOrder->next;
    }
    int totalOrder = orderCount.size();
    for(const auto& entry : orderCount){
        if(entry.second >= 1000000){
            totalSales += entry.second * 0.15;
        }
        else if(totalSales >= 500000){
            totalSales += entry.second * 0.1;
        }
    }
    if(totalOrder == 0){
        cout << "***--------------------------------------------------***" << endl;
        cout << "   <!> KHONG CO DON HANG NAO TRONG THOI GIAN NAY. " << endl;
        cout << "***--------------------------------------------------***" << endl;
        return;
    }
    cout << "===================================== THONG KE ================================" << endl;
    cout << "Tong so don hang: " << totalOrder << endl;
    cout << "Tong san pham da ban: " << totalItemsSold << endl;
    cout << "Tong so tien da giam gia: " << fixed << setprecision(0) << formatMoney(totalSales) << " VND" << endl;
    cout << "Tong so tien truoc khi giam gia: " << fixed << setprecision(0) << formatMoney(totalRevenue) << " VND" << endl;
    cout << "Tong doanh thu: " << fixed << setprecision(0) << formatMoney(totalRevenue - totalSales) << " VND" << endl;
    
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
    if (maxSales == minSales) {
        cout << "<!> San pham ban chay nhat: ";
        for (const auto& entry : productQuantities) {
            if (entry.second == maxSales) {
                cout << entry.first << " ";
            }
        }
        cout << "voi " << maxSales << " san pham" << endl;
    } else {
        cout << "<!> San pham ban chay nhat: ";
        for (const auto& entry : productQuantities) {
            if (entry.second == maxSales) {
                cout << entry.first << ", ";
            }
        }
        cout << "voi " << maxSales << " san pham" << endl;
        cout << "<!> San pham ban it nhat: ";
        for (const auto& entry : productQuantities) {
            if (entry.second == minSales) {
                cout << entry.first << ", ";
            }
        }
        cout << "voi " << minSales << " san pham" << endl;
    }
cout << "--------------------------------------------------------------------------------" << endl;
cout << left << setw(30) << "Ten san pham"
     << "|" << setw(15) << "So luong"
     << "|" << setw(20) << "Doanh thu (VND)"
     << "|" << "Phan tram (%)" << endl;
cout << "--------------------------------------------------------------------------------" << endl;
    for (const auto& entry : productQuantities) {
        const string& itemName = entry.first;
        int quantity = entry.second;
        double revenue = productRevenues[itemName];
        double percentRevenue = (totalRevenue > 0) ? (revenue / totalRevenue) * 100 : 0;

 cout << left << setw(30) << itemName
         << "|" << setw(15) << quantity
         << "|" << setw(20) << fixed << setprecision(0) << formatMoney(revenue)
         << "|" << fixed << setprecision(2) << percentRevenue << "%" << endl;
    }

    cout << "================================================================================" << endl;
}

void OrderManager::readOrdersFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Khong the mo file de doc hoa don!" << std::endl;
        return;
    }

    while (inFile.good()) {
        Order* order = new Order(0, "", ""); 
        order->readFromFile(inFile);
        if (order->getID() != "0") { 
            orders.push_back(order);
        } else {
            delete order; 
        }
    }

    inFile.close();
}
void OrderManager::clearOrders() {
    orders.clear();
}
bool OrderManager::readInvoiceFromFile(const string& id){
    Admin_Manage KH;
    KH.ReadFileCustomer("Customerr.txt");
    Admin* kh = KH.findKhachHang(id);
    if(kh == nullptr){
        cout << "<!> KHONG TIM THAY KHACH HANG CO ID " << id << endl;
         system("pause");
        return false;
    }
    string tenFile = id + "_" + kh->getName() + ".txt";
    ifstream inFile(tenFile);
    if (!inFile.is_open()) {
         system("pause");
        return false;
    }
    string line;
    while(getline(inFile, line)){
        cout << line << endl;
    }
    inFile.close();
    KH.deleteList();
      system("pause");
    return true;
}
