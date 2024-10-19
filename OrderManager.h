#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include "support.h"
#include "Order.h"
#include "LinkedList.h"
#include "ClothesManager.h"
#include <string>

using namespace std;

class OrderManager {
private:
    LinkedList<Order*> orders;

public:
    void createOrder(ClothesManager& clothesManager);
    void checkoutOrder(Order* order);
    static int generateRandomOrderNumber();
};

#endif // ORDERMANAGER_H