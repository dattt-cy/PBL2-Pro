#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "LinkedList.h"
#include "ClothesManager.h"
#include "support.h"
using namespace std;
struct Datee {
    int day;
    int month;
    int year;

    Datee() {
        time_t now = time(0);
        tm* t = localtime(&now);
        day = t->tm_mday;
        month = t->tm_mon + 1;
        year = t->tm_year + 1900;
    }

    Datee(int d, int m, int y) : day(d), month(m), year(y) {}
};
struct OrderItem {
    string itemID;
    string itemName;
    string color;
    string size;
    int quantity;
    double price;
    Datee orderDate;
    int orderID2;
    OrderItem(int oid,const string& id, const string& name, const string& col, const string& sz, int qty, double pr, const Datee& date)
        : orderID2(oid),itemID(id), itemName(name), color(col), size(sz), quantity(qty), price(pr), orderDate(date) {}
    string getID() const { return itemID; }
    string getOrderID2() const {return to_string(orderID2);}
};


class Order {
private:
    int orderID;
    string customerName;
    string customerPhone;
    LinkedList<OrderItem*> items;
    double total;
    double finalTotal;

public:
    Order(int id, const string& name, const string& phone);
    string getID() const { return to_string(orderID); }
    void addItem(OrderItem* item);
    bool removeItem(const string& itemID, ClothesManager& clothesManager);
    void editItem(ClothesManager& clothesManager);
    double calculateTotal() const;
    void displayOrder() const;
    void printInvoice();
    LinkedList<OrderItem*>& getItems();
    bool addClothesItem(ClothesManager& clothesManager);
    string InvoiceID() const;
    double getFinalTotal() const;
    double getDiscountAmount() const;
    int getTotalItemsSold() const;
    double getTotalRevenue() const;
    void ProductStats(std::map<std::string, int>& productQuantities, std::map<std::string, double>& productRevenues) const;
    void restoreItems(ClothesManager& clothesManager);
    void writeInvoiceToFile(const string& customerID, const string& customerName, const string& customerPhone);
    void saveOrderToFile(const string& filename);
    void readFromFile(ifstream& inFile);
    bool containsItemsMatching(int day, int month, int year, const std::string& filterType) const;
};

#endif // ORDER_H