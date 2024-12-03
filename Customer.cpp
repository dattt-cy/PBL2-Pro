
#include "Customer.h"

Customer::Customer() : Person() {}
Customer::~Customer() {}

void Customer::Show() const {
    ostringstream birthDate;
    birthDate << setfill('0') << setw(2) << birthDay.day << "/"
              << setfill('0') << setw(2) << birthDay.month << "/"
              << birthDay.year;

    cout << "| " << left << setw(17) << ID
              << "| " << setw(22) << name
              << "| " << setw(11) << gender
              << "| " << setw(16) << birthDate.str()
              << "| " << setw(19) << numberPhone
              << "| " << setw(31) << address << "|\n";
}