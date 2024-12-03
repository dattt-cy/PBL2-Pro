#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "LinkedList.h"
#include "Person.h"

class Customer : public Person {
public:
    static int countKH;
    Customer();
    ~Customer();
    void Show() const override; 
};

#endif
