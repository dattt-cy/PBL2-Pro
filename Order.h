#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "LinkedList.h"
#include "ClothesManager.h"
#include "support.h"
using namespace std;

struct OrderItem {
    string itemID;
    string itemName;
    string color;
    string size;
    int quantity;
    double price;

    OrderItem(const string& id, const string& name, const string& col, const string& sz, int qty, double pr)
        : itemID(id), itemName(name), color(col), size(sz), quantity(qty), price(pr) {}
    string getID() const { return itemID; }
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
    LinkedList<OrderItem*> getItems() const;
    bool addClothesItem(ClothesManager& clothesManager);
    string InvoiceID() const;
    double getFinalTotal() const;
    double getDiscountAmount() const;
    int getTotalItemsSold() const;
    double getTotalRevenue() const;
    void ProductStats(std::map<std::string, int>& productQuantities, std::map<std::string, double>& productRevenues) const;
    void restoreItems(ClothesManager& clothesManager);
};

#endif // ORDER_H