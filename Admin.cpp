#include "Admin.h"
#include "Admin_Manage.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

int Admin::count = 0;

Admin::Admin() : Person(), dayofWork({0, 0, 0}) {}

Admin::~Admin() {}

void Admin::setDayofwork(int day, int month, int year) {
    dayofWork.day = day;
    dayofWork.month = month;
    dayofWork.year = year;
}

string Admin::getDayofwork() {
    return dayofWork.toString();
}

void Admin::Show() const{
    ostringstream birthDate;
    birthDate << setfill('0') << setw(2) << birthDay.day << "/"
              << setfill('0') << setw(2) << birthDay.month << "/"
              << birthDay.year;

    ostringstream workDate;
    workDate << setfill('0') << setw(2) << dayofWork.day << "/"
             << setfill('0') << setw(2) << dayofWork.month << "/"
             << dayofWork.year;

    cout << "| " << left << setw(17) << ID
              << "| " << setw(22) << name
              << "| " << setw(11) << gender
              << "| " << setw(16) << birthDate.str()
              << "| " << setw(19) << numberPhone
              << "| " << setw(31) << address
              << "| " << setw(16) << workDate.str() << "|\n";
}
