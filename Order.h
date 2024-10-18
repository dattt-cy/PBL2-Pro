#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "LinkedList.h"
#include "ClothesManager.h"

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
    static double total;

public:
    Order(int id, const string& name, const string& phone);
    string getID() const { return to_string(orderID); }
    void addItem(OrderItem* item);
    bool removeItem(const string& itemID, ClothesManager& clothesManager);
    void editItem(ClothesManager& clothesManager);
    static double calculateTotal();
    void displayOrder() const;
    void printInvoice() const;
    LinkedList<OrderItem*> getItems() const;
    bool addClothesItem(ClothesManager& clothesManager);
};

#endif // ORDER_H