#include "Order.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;


Order::Order(int id, const string& name, const string& phone)
    : orderID(id), customerName(name), customerPhone(phone), total(0.0), finalTotal(0.0) {}


void Order::addItem(OrderItem* item) {
    items.push_back(item);
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
    getline(cin, itemID);
    itemID = nameStr(itemID);
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
    string newQuantity2;
    int newQuantity;
    while (true) {
        cout << "\nNhap ma ID san pham moi (nhap 0 de huy): ";
        getline(cin, newItemID);
        if(newItemID.empty()){
            cout << "<!> MA ID KHONG DUOC DE TRONG. VUI LONG NHAP LAI." << endl;
            continue;
        }
        if (newItemID == "0") {
            cout << "<!> QUA TRINH CHINH SUA DA BI HUY!" << endl;
            return;
        }
        newItemID = nameStr(newItemID);
        Clothes* clothes = clothesManager.findByID(newItemID);
        if (clothes == nullptr) {
            cout << "<!> KHONG TIM THAY SAN PHAM VOI MA ID: " << newItemID << ". Vui long nhap lai." << endl;
            continue;
        }
        clothesManager.PrintClothesByID(newItemID);

        newItemName = clothes->getName(); 

        while (true) {
            cout << "\nNhap mau sac moi (nhap 0 de huy): ";
            getline(cin, newColor);
            newColor = nameStr(newColor);
            if(newColor.empty()){
                cout << "<!> MAU SAC KHONG DUOC DE TRONG. VUI LONG NHAP LAI." << endl;
                continue;
            }
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
            if(newSize.empty()){
                cout << "<!> KICH CO KHONG DUOC DE TRONG. VUI LONG NHAP LAI." << endl;
                continue;
            }
            newSize = toUpper(newSize);
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
            getline(cin,newQuantity2);
            if(newQuantity2.empty()){
                cout << "<!> SO LUONG KHONG DUOC DE TRONG. VUI LONG NHAP LAI." << endl;
                continue;
            }
            newQuantity = stringToInt(newQuantity2);
            if (newQuantity == 0) {
                cout << "<!> QUA TRINH CHINH SUA DA BI HUY!" << endl;
                return;
            }
            if(newQuantity < 0){
                cout << "<!> SO LUONG PHAI LA SO DUONG. VUI LONG NHAP LAI" << endl;
                continue;
            }
            if (!clothes->checkQuantity(newColor, newSize, newQuantity)) {
                cout << "<!> SO LUONG NHAP VAO VUOT QUA SO LUONG HIEN CO. VUI LONG NHAP LAI." << endl;
                continue;
            }
            break;
        }


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
    string quantity2;
    int quantity;
    Clothes* clothes = nullptr;
    while (true) {
        cout << "<!> Nhap ma ID quan ao muon mua (nhap 0 de huy): ";
        getline(cin, itemID);
        if (itemID == "0") {
            return false;
        }
        if (itemID == "1") {
            return true;
        }
        itemID = nameStr(itemID);
        clothes = clothesManager.findByID(itemID);
        if (clothes == nullptr) {
            cout << "<!> KHONG TIM THAY SAN PHAM VOI MA ID: " << itemID << ". Vui long nhap lai." << endl;
            continue;
        }
         if (clothes->getTotalQuantity() == 0) {
            cout << "<!> SAN PHAM VOI MA ID: " << itemID << " DA HET HANG. Vui long chon san pham khac." << endl;
            continue;
        }
        break;
    }
    clothesManager.PrintClothesByID(itemID);
    while (true) {
        cout << "<!> Chon mau sac cho san pham " << itemID << ": ";
        getline(cin, color);
        color = nameStr(color);
        if(color.empty()){
            cout << "<!> MAU SAC KHONG DUOC DE TRONG. VUI LONG NHAP LAI." << endl;
            continue;
        }
        if (!clothes->hasColor(color)) {
            cout << "<!> KHONG TIM THAY MAU SAC: " << color << " CHO SAN PHAM VOI MA ID: " << itemID << ". Vui long nhap lai." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "<!> Chon kich co cho san pham " << itemID << ": ";
        getline(cin, size);
        if(size.empty())
        {
            cout << "<!> KICH CO KHONG DUOC DE TRONG. VUI LONG NHAP LAI." << endl;
            continue;
        }
        size = toUpper(size);
        if (!clothes->hasSize(color, size)) {
            cout << "<!> KHONG TIM THAY KICH CO: " << size << " CHO MAU SAC: " << color << " CUA SAN PHAM VOI MA ID: " << itemID << ". Vui long nhap lai." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "<!> Chon so luong cho san pham " << itemID << ": ";
        getline(cin, quantity2);
        if(quantity2.empty())
        {
            cout << "<!> SO LUONG KHONG DUOC DE TRONG. VUI LONG NHAP LAI." << endl;
            continue;
        }
        quantity = stringToInt(quantity2);
        if (!clothes->checkQuantity(color, size, quantity)) {
            cout << "<!> SO LUONG NHAP VAO VUOT QUA SO LUONG HIEN CO. VUI LONG NHAP LAI." << endl;
            continue;
        }
        if(quantity < 0){
            cout << "<!> SO LUONG PHAI LA SO DUONG. VUI LONG NHAP LAI" << endl;
            continue;
        }
        break;
    }
    clothes->UpdateSL(color, size, quantity);
    double price = clothes->getPrice();
    string itemName = clothes->getName(); 
    time_t now = time(0);
    tm* ltm = localtime(&now);
    Datee orderDate(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
    int orderID = items.getHead() ? items.getHead()->data->orderID2 : 0;
    OrderItem* item = new OrderItem(orderID ,itemID, itemName, color, size, quantity, price, orderDate);
    addItem(item);
    cout << "<!> DA THEM SAN PHAM VAO GIO HANG!" << endl;
    return true;
}

double Order::calculateTotal() const {
    double total = 0.0;
    Node<OrderItem*>* current = items.getHead();
    while (current) {
        total += current->data->price * current->data->quantity;
        current = current->next;
    }
    return total;
}


void Order::displayOrder() const {
    cout << "============================ SHOP QUAN AO GAU GAU ===============================\n";
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
             << setw(15) << fixed << setprecision(0) << formatMoney(current->data->price*current->data->quantity)
             << endl;
        current = current->next;
    }

    cout << "--------------------------------------------------------------------------------\n";
    cout << right << setw(62) << "Tong Cong: "
         << fixed << setprecision(0) << formatMoney(calculateTotal()) << " VND\n";
    cout << "================================================================================\n";
} 
void Order::writeInvoiceToFile(const string& customerID, const string& customerName, const string& customerPhone){
    stringstream fileName;
    fileName << customerID << "_" << customerName << ".txt";

    ofstream outFile(fileName.str(), ios::app);
    if (!outFile.is_open()) {
        cerr << "Khong the mo file de ghi hoa don!" << endl;
        return;
    }
    outFile << "============================= SHOP QUAN AO GAU GAU =============================\n";
    double totalAmount = calculateTotal();
    double discount = 0.0;
    if(totalAmount >= 1000000){
        discount =  0.15;
    } else if(totalAmount > 500000){
        discount = 0.1;
    }
    double discountAmount = totalAmount * discount;
    double finalTotall = totalAmount - discountAmount;
    finalTotal = finalTotall;


    outFile << "Ma Hoa Don: " << InvoiceID() << "                K89/3 Dong Ke, Lien Chieu, Tp. Da Nang" << endl;
    time_t now = time(NULL);
    tm* t = localtime(&now);


    outFile << "Time  In: ";
    outFile  << setw(1) << "" << t->tm_mday << "."<< "" << t->tm_mon + 1 << "." << "" << t->tm_year - 100 << " ";
    outFile  << setw(1) << "" << t->tm_hour << ":" << "" << t->tm_min << "                                       SDT: 0372787650" << endl;

    outFile  << "Time Out: ";
    outFile  << setw(1) << "" << t->tm_mday << "." << "" << t->tm_mon + 1 << "." << "" << t->tm_year - 100 << " ";
    outFile  << setw(1) << "" << t->tm_hour << ":" << "" << t->tm_min << endl;
    outFile  << "Ten Khach Hang: " << customerName << endl;
    outFile  << "So Dien Thoai: " << customerPhone << endl;
    outFile  << endl;
    outFile << "                               HOA DON THANH TOAN                                  " << endl;
    outFile << endl;
    outFile << left << setw(20) << "Item"
            << right << setw(20) << "Price"
            << setw(18) << "Quantity"
            << setw(17) << "Total" << endl;

    outFile << "--------------------------------------------------------------------------------\n";

    Node<OrderItem*>* current = items.getHead();
    while (current != nullptr) {
        OrderItem* item = current->data;
        outFile << left << setw(20) << current->data->itemName
             << right << setw(17) << fixed << setprecision(0) << formatMoney(current->data->price) << " VND"
             << right << setw(13) << current->data->quantity
             << right << setw(19) << fixed << setprecision(0) 
             << formatMoney(current->data->price * current->data->quantity) << " VND" << endl;
        current = current->next;
    }

    outFile << "--------------------------------------------------------------------------------\n";
    outFile << "Tong tien: " << fixed << setprecision(0) << formatMoney(totalAmount) << " VND" << endl;
    outFile << "Giam gia: " << discount * 100 << "%" << endl;
    outFile << "Tong tien duoc giam gia: " << fixed << setprecision(0) << formatMoney(discountAmount) << " VND" << endl;
    outFile << "Tong tien sau khi giam gia: " << fixed << setprecision(0) << formatMoney(finalTotall) << " VND" << endl;
    ostringstream oss;
    read_number(finalTotal, oss);
    outFile << oss.str() << "dong" << endl;
    outFile << "================================================================================\n";
}

void Order::printInvoice()  {
    cout << "============================= SHOP QUAN AO GAU GAU =============================\n";
    double totalAmount = calculateTotal();
    double discount = 0.0;
    if(totalAmount >= 1000000){
        discount =  0.15;
    } else if(totalAmount > 500000){
        discount = 0.1;
    }
    double discountAmount = totalAmount * discount;
    double finalTotall = totalAmount - discountAmount;
    finalTotal = finalTotall;
    cout << endl;
    cout << "Ma Hoa Don: " << InvoiceID() << "                K89/3 Dong Ke, Lien Chieu, Tp. Da Nang" << endl;
    time_t now = time(NULL);
    tm* t = localtime(&now);


    cout << "Time  In: ";
    cout << setw(1) << "" << t->tm_mday << "."<< "" << t->tm_mon + 1 << "." << "" << t->tm_year - 100 << " ";
    cout << setw(1) << "" << t->tm_hour << ":" << "" << t->tm_min << "                                       SDT: 0372787650" << endl;

    cout << "Time Out: ";
    cout << setw(1) << "" << t->tm_mday << "." << "" << t->tm_mon + 1 << "." << "" << t->tm_year - 100 << " ";
    cout << setw(1) << "" << t->tm_hour << ":" << "" << t->tm_min << endl;
    cout << "Ten Khach Hang: " << customerName << endl;
    cout << "So Dien Thoai: " << customerPhone << endl;
    cout << endl;
    cout << "                               HOA DON THANH TOAN                                  " << endl;
    cout << endl;
    cout << left << setw(20) << "Item"
         << right << setw(20) << "Price"
         << setw(18) << "Quantity"
         << setw(17) << "Total" << endl;

    cout << "--------------------------------------------------------------------------------\n";

    Node<OrderItem*>* current = items.getHead();
    while (current) {
        cout << left << setw(20) << current->data->itemName
             << right << setw(17) << fixed << setprecision(0) << formatMoney(current->data->price) << " VND"
             << right << setw(13) << current->data->quantity
             << right << setw(19) << fixed << setprecision(0) 
             << formatMoney(current->data->price * current->data->quantity) << " VND" << endl;

        current = current->next;
    }

    cout << "--------------------------------------------------------------------------------\n";
    cout << "Tong tien: " << fixed << setprecision(0) << formatMoney(totalAmount) << " VND" << endl;
    cout << "Giam gia: " << discount * 100 << "%" << endl;
    cout << "Tong tien duoc giam gia: " << fixed << setprecision(0) << formatMoney(discountAmount) << " VND" << endl;
    cout << "Tong tien sau khi giam gia: " << fixed << setprecision(0) << formatMoney(finalTotall) << " VND" << endl;
    ostringstream oss;
    read_number(finalTotal, oss);
    cout << oss.str() << "dong" << endl;
    cout << "================================================================================\n";
}

LinkedList<OrderItem*>& Order::getItems(){
    return items;
}
string Order::InvoiceID() const{
    time_t now = time(NULL);
    tm* t = localtime(&now);

    stringstream ss;
    ss << "INV_"
       << setw(2) << setfill('0') << t->tm_mday
       << setw(2) << setfill('0') << t->tm_mon + 1
       << setw(2) << setfill('0') << t->tm_year % 100 << "_"
       << setw(3) << setfill('0') << orderID;

    return ss.str();
}
double Order::getFinalTotal() const {
    return finalTotal;
}
void Order::ProductStats(std::map<std::string, int>& productQuantities, std::map<std::string, double>& productRevenues) const {
    Node<OrderItem*>* current = items.getHead();
    while (current) {
        string itemName = current->data->itemName;
        int quantity = current->data->quantity;
        double revenue = current->data->price * quantity;

        productQuantities[itemName] += quantity;
        productRevenues[itemName] += revenue;

        current = current->next;
    }
}
double Order::getDiscountAmount() const {
    return calculateTotal() - getFinalTotal();
}

int Order::getTotalItemsSold() const {
    int totalItems = 0;
    Node<OrderItem*>* current = items.getHead();
    while (current) {
        totalItems += current->data->quantity;
        current = current->next;
    }
    return totalItems;
}

double Order::getTotalRevenue() const {
    return getFinalTotal();
}
void Order::restoreItems(ClothesManager& clothesManager) {
    Node<OrderItem*>* current = items.getHead();
    while (current) {
        Clothes* clothes = clothesManager.findByID(current->data->itemID);
        if (clothes != nullptr) {
            clothes->increaseSL(current->data->color, current->data->size, current->data->quantity);
        }
        current = current->next;
    }
}
void Order::saveOrderToFile(const string& filename) {
    ofstream outFile(filename, ios::app);
    if (!outFile.is_open()) {
        cerr << "Khong the mo file de ghi hoa don!" << endl;
        return;
    }
    time_t now = time(NULL);
    tm* t = localtime(&now);
    string orderDate = to_string(t->tm_mday) + "/" + to_string(t->tm_mon + 1) + "/" + to_string(t->tm_year + 1900);
    
    Node<OrderItem*>* current = items.getHead();
    while(current) {
        outFile << orderDate << "," << orderID << "," << current->data->itemID << "," << current->data->itemName << "," << current->data->color << "," << current->data->size << "," << current->data->quantity << "," << current->data->price << endl;
        current = current->next;
    }

    outFile.close();
}


void Order::readFromFile(std::ifstream& inFile) {
    std::string itemID, itemName, color, size;
    int orderID, day, month, year, quantity;
    double price;

    char delimiter;

     while (inFile >> day >> delimiter >> month >> delimiter >> year >> delimiter >> orderID >> delimiter) {
        std::getline(inFile, itemID, ',');
        std::getline(inFile, itemName, ',');
        std::getline(inFile, color, ',');
        std::getline(inFile, size, ',');
        if (!(inFile >> quantity >> delimiter >> price)) break;
        inFile.ignore(); 

        if (itemID.empty() || itemName.empty() || color.empty() || size.empty()) {
            std::cerr << "Loi: Du lieu khong hop le trong file." << std::endl;
            continue; 
        }

        Datee orderDate(day, month, year);
        this->orderID = orderID;
        OrderItem* item = new OrderItem(orderID, itemID, itemName, color, size, quantity, price, orderDate);
        this->addItem(item);

    }
}
bool Order::containsItemsMatching(int day, int month, int year, const string& filterType) const {
    Node<OrderItem*>* currentItem = items.getHead();
    while (currentItem) {
        const Datee& orderDate = currentItem->data->orderDate;

        if (filterType == "day" && orderDate.day == day && orderDate.month == month && orderDate.year == year) {
            return true;
        } else if (filterType == "month" && day == 0 && orderDate.month == month && orderDate.year == year) {
            return true;
        } else if (filterType == "year" && orderDate.year == year) {
            return true;
        }

        currentItem = currentItem->next;
    }
    return false;
}
