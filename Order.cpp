#include "Order.h"
#include <iostream>
#include <iomanip>

using namespace std;

double Order::total = 0.0; 

Order::Order(int id, const string& name, const string& phone)
    : orderID(id), customerName(name), customerPhone(phone) {}

void Order::addItem(OrderItem* item) {
    items.addNode(item);
    total += item->price * item->quantity; 
}

bool Order::removeItem(const string& itemID, ClothesManager& clothesManager) {
    system("cls");
    displayOrder();
    Node<OrderItem*>* current = items.getHead();
    while (current) {
        if (current->data->itemID == itemID) {
            Clothes* clothes = clothesManager.findByID(itemID);
            if(clothes != nullptr){
                clothes->UpdateSL(current->data->color, current->data->size, -current->data->quantity);
            }
            total -= current->data->price * current->data->quantity; 
            return items.removeById(itemID);
        }
        current = current->next;
    }
    cout << "<!> KHONG TIM THAY SAN PHAM TRONG GIO HANG!" << endl;
    return false;
    system("pause");
}

void Order::editItem(ClothesManager& clothesManager) {
    Node<OrderItem*>* current = items.getHead();
    displayOrder();
    string itemID;
    cout << "Nhap ma ID san pham muon chinh sua: ";
    cin >> itemID;
    cin.ignore();

    bool found = false;
    while (current) {
        if (current->data->itemID == itemID) {
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "<!> KHONG TIM THAY SAN PHAM VOI MA ID: " << itemID << " TRONG GIO HANG. VUI LONG KIEM TRA LAI." << endl;
        system("pause");
        return;
    }

    string newItemID, newColor, newSize, newItemName;
    int newQuantity;
    while (true) {
        cout << "\nNhap ma ID san pham moi (nhap 0 de huy): ";
        getline(cin, newItemID);
        if (newItemID == "0") {
            cout << "<!> QUA TRINH CHINH SUA DA BI HUY!" << endl;
            return;
        }

        Clothes* clothes = clothesManager.findByID(newItemID);
        if (clothes == nullptr) {
            cout << "<!> KHONG TIM THAY SAN PHAM VOI MA ID: " << newItemID << ". Vui long nhap lai." << endl;
            continue;
        }

        newItemName = clothes->getName(); 

        while (true) {
            cout << "\nNhap mau sac moi (nhap 0 de huy): ";
            getline(cin, newColor);
            if (newColor == "0") {
                cout << "<!> QUA TRINH CHINH SUA DA BI HUY!" << endl;
                return;
            }
            if (!clothes->hasColor(newColor)) {
                cout << "<!> KHONG TIM THAY MAU SAC: " << newColor << " CHO SAN PHAM VOI MA ID: " << newItemID << ". Vui long nhap lai." << endl;
                continue;
            }
            break;
        }

        while (true) {
            cout << "\nNhap kich co moi (nhap 0 de huy): ";
            getline(cin, newSize);
            if (newSize == "0") {
                cout << "<!> QUA TRINH CHINH SUA DA BI HUY!" << endl;
                return;
            }
            Clothes* clothes2 = clothesManager.findByID(current->data->itemID);
            clothes2->UpdateSL(current->data->color, current->data->size, -current->data->quantity);
            if (!clothes->hasSize(newColor, newSize)) {
                cout << "<!> KHONG TIM THAY KICH CO: " << newSize << " CHO MAU SAC: " << newColor << " CUA SAN PHAM VOI MA ID: " << newItemID << ". Vui long nhap lai." << endl;
                continue;
            }
            break;
        }
        while (true) {
            cout << "\nNhap so luong moi (nhap 0 de huy): ";
            cin >> newQuantity;
            if (newQuantity == 0) {
                cout << "<!> QUA TRINH CHINH SUA DA BI HUY!" << endl;
                cin.ignore();
                return;
            }
            if (!clothes->checkQuantity(newColor, newSize, newQuantity)) {
                cout << "<!> SO LUONG NHAP VAO VUOT QUA SO LUONG HIEN CO. VUI LONG NHAP LAI." << endl;
                continue;
            }
            break;
        }

        cin.ignore();

        total -= current->data->price * current->data->quantity;

        current->data->itemID = newItemID;
        current->data->itemName = newItemName; 
        current->data->color = newColor;
        current->data->size = newSize;
        current->data->quantity = newQuantity;
        current->data->price = clothes->getPrice();
        clothes->UpdateSL(newColor, newSize, newQuantity);
        total += current->data->price * current->data->quantity;

        cout << "<!> DA CAP NHAT GIO HANG THANH CONG!" << endl;
        return;
    }
}

bool Order::addClothesItem(ClothesManager& clothesManager) {
    string itemID, color, size;
    int quantity;
    Clothes* clothes = nullptr;

    while (true) {
        cout << "\nNhap ma ID quan ao muon mua (nhap 0 de huy): ";
        cin >> itemID;
        if (itemID == "0") {
            return false;
        }
        if (itemID == "1") {
            return true;
        }

        clothes = clothesManager.findByID(itemID);
        if (clothes == nullptr) {
            cout << "<!> KHONG TIM THAY SAN PHAM VOI MA ID: " << itemID << ". Vui long nhap lai." << endl;
            continue;
        }

        cin.ignore();
        break;
    }

    while (true) {
        cout << "Chon mau sac cho san pham " << itemID << ": ";
        getline(cin, color);
        if (!clothes->hasColor(color)) {
            cout << "<!> KHONG TIM THAY MAU SAC: " << color << " CHO SAN PHAM VOI MA ID: " << itemID << ". Vui long nhap lai." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Chon kich co cho san pham " << itemID << ": ";
        getline(cin, size);
        if (!clothes->hasSize(color, size)) {
            cout << "<!> KHONG TIM THAY KICH CO: " << size << " CHO MAU SAC: " << color << " CUA SAN PHAM VOI MA ID: " << itemID << ". Vui long nhap lai." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Chon so luong cho san pham " << itemID << ": ";
        cin >> quantity;

        if (!clothes->checkQuantity(color, size, quantity)) {
            cout << "<!> SO LUONG NHAP VAO VUOT QUA SO LUONG HIEN CO. VUI LONG NHAP LAI." << endl;
            continue;
        }
        break;
    }
    clothes->UpdateSL(color, size, quantity);
    double price = clothes->getPrice();
    string itemName = clothes->getName(); 
    OrderItem* item = new OrderItem(itemID, itemName, color, size, quantity, price);
    addItem(item);
    cout << "<!> DA THEM SAN PHAM VAO GIO HANG!" << endl;
    return true;
}

double Order::calculateTotal() {
    return total;
}


void Order::displayOrder() const {
    cout << "================================= GIO HANG ====================================\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Ten San Pham"
         << setw(15) << "Mau"
         << setw(10) << "Size"
         << setw(12) << "So Luong"
         << setw(15) << "Gia" 
         << endl;

    cout << "--------------------------------------------------------------------------------\n";

    Node<OrderItem*>* current = items.getHead();
    while (current) {
        cout << left << setw(10) << current->data->itemID
             << setw(25) << current->data->itemName  
             << setw(15) << current->data->color
             << setw(10) << current->data->size
             << setw(12) << current->data->quantity
             << setw(15) << fixed << setprecision(0) << current->data->price*current->data->quantity
             << endl;
        current = current->next;
    }

    cout << "--------------------------------------------------------------------------------\n";
    cout << right << setw(62) << "Tong Cong: "
         << fixed << setprecision(0) << calculateTotal() << " VND\n";
    cout << "================================================================================\n";
}


void Order::printInvoice() const {
    cout << "================================= HOA DON ====================================\n";

    time_t now = time(NULL);
    tm* t = localtime(&now);


    cout << "Time  In: ";
    cout << setw(1) << "" << t->tm_mday << "."<< "" << t->tm_mon + 1 << "." << "" << t->tm_year - 100 << " ";
    cout << setw(1) << "" << t->tm_hour << ":" << "" << t->tm_min << endl;

    cout << "Time Out: ";
    cout << setw(1) << "" << t->tm_mday << "." << "" << t->tm_mon + 1 << "." << "" << t->tm_year - 100 << " ";
    cout << setw(1) << "" << t->tm_hour << ":" << "" << t->tm_min << endl;

    cout << left << setw(20) << "Item"
         << right << setw(20) << "Price"
         << setw(18) << "Quantity"
         << setw(17) << "Total" << endl;

    cout << "--------------------------------------------------------------------------------\n";

    Node<OrderItem*>* current = items.getHead();
    while (current) {
        cout << left << setw(20) << current->data->itemName
             << right << setw(17) << fixed << setprecision(0) << current->data->price << " VND"
             << right << setw(13) << current->data->quantity
             << right << setw(19) << fixed << setprecision(0) 
             << current->data->price * current->data->quantity << " VND" << endl;

        current = current->next;
    }

    cout << "--------------------------------------------------------------------------------\n";
    cout << right << setw(63) << "Tong Cong: "
         << fixed << setprecision(0) << calculateTotal() << " VND\n";
    cout << "================================================================================\n";
}

LinkedList<OrderItem*> Order::getItems() const {
    return items;
}