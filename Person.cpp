#include "Person.h"

Person::Person() : numberPhone(""), passWord(""), ID(""), name(""), gender(""), address(""), birthDay({0, 0, 0}) {}

Person::Person(const string& id, const string& passWord, const string& name, const string& gender,
               const string& phone, const string& address, const Date& birthDay)
    : ID(id), passWord(passWord), name(name), gender(gender), numberPhone(phone), address(address), birthDay(birthDay) {}


Person::~Person() {}

void Person::setID(const string& id) {
    this->ID = id;
}

void Person::setName(const string& name) {
    this->name = name;
}
void Person::setPassWord(const string& passWord) {
    this->passWord = passWord;
}
void Person::setGender(const string& gender) {
    this->gender = gender;
}

void Person::setNumberPhone(const string& phone) {
    this->numberPhone = phone;
}

void Person::setAddress(const string& address) {
    this->address = address;
}

void Person::setBirthDay(int day, int month, int year) {
    birthDay.day = day;
    birthDay.month = month;
    birthDay.year = year;
}

string Person::getID() const {
    return ID;
}
string Person::getPassWord() const {
    return passWord;
}

string Person::getName() const {
    return name;
}

string Person::getGender() const {
    return gender;
}

string Person::getNumberPhone() const {
    return numberPhone;
}

string Person::getAddress() const {
    return address;
}

string Person::getBirthDay() const {
    return birthDay.toString();
}
bool Person::checkLogin(const string& username, const string& password) {
    return ID == username && passWord == password;
}
