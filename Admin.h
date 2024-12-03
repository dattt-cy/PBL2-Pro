#include <iostream>
#include <sstream>
#include <string.h>
#include "LinkedList.h"
#include "Person.h"
#pragma once

#define ADMIN_H

using namespace std;


class Admin: public Person {
    private:
        Date dayofWork;
    public:
        static int count;
        Admin();
        ~Admin();
        void setDayofwork(int day, int month, int year);
        string getDayofwork();
        void Show() const override;
};