#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include "support.h"
#include "Order.h"
#include "LinkedList.h"
#include "ClothesManager.h"
#include <string>
#include <iomanip>
#include "Admin_Manage.h"

using namespace std;

class OrderManager {
private:
    LinkedList<Order*> orders;

public:
    void createOrder(ClothesManager& clothesManager);
    void checkoutOrder(Order* order);
    static int generateRandomOrderNumber();
    void generateStatistics(int day, int month, int year, const std::string& filterType);
    LinkedList<Order*> getOrders() const;
    void readOrdersFromFile(const string& filename);
    void clearOrders();
    bool readInvoiceFromFile(const string& id);
};

#endif // ORDERMANAGER_H