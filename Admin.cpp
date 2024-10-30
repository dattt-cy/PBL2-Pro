#include "Admin.h"
#include "Admin_Manage.h"
#include <iostream>
#include <iomanip>

int Admin::count = 0;

Admin::Admin() : numberPhone("h"), passWord("h"), ID("h"), name("h"), gender("h"), address("h"), birthDay({0, 0, 0}), dayofWork({0, 0, 0}) {}

Admin::~Admin() {}

void Admin::setnumberPhone(string phone) {
    numberPhone = phone;
}

void Admin::setID(string id) {
    ID = id;
}

void Admin::setpassWord(string pass) {
    passWord = pass;
}

void Admin::setName(string n) {
    name = n;
}

void Admin::setGender(string g) {
    gender = g;
}

void Admin::setAddress(string addr) {
    address = addr;
}

void Admin::setbirthDay(int day, int month, int year) {
    birthDay.day = day;
    birthDay.month = month;
    birthDay.year = year;
}

void Admin::setDayofwork(int day, int month, int year) {
    dayofWork.day = day;
    dayofWork.month = month;
    dayofWork.year = year;
}

string Admin::getnumberPhone() {
    return numberPhone;
}

string Admin::getID() {
    return ID;
}

string Admin::getpassWord() {
    return passWord;
}

string Admin::getName() {
    return name;
}

string Admin::getGender() {
    return gender;
}

string Admin::getAddress() {
    return address;
}

string Admin::getbirthDay() {
    return birthDay.toString();
}

string Admin::getDayofwork() {
    return dayofWork.toString();
}

void Admin::Show() {
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

void Admin::ShowC() {
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
              << "| " << setw(31) << address << "|\n";
}

bool Admin::checkLogin(const string& username, const string& password) {
    return (username == ID && password == passWord);
}