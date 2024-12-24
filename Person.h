// Person.h
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;
struct Date {
    int day, month, year;

    string toString() const {
        stringstream ss;
        ss << day << "/"
           << month << "/"
           << year;
        return ss.str();
    }
};
class Person {
protected:
    string ID;
    string name;
    string passWord;
    string gender;
    string numberPhone;
    string address;
    Date birthDay;

public:
    Person();
    Person(const string& id,const string& passWord,const string& name, const string& gender,
           const string& phone, const string& address, const Date& birthDay);
    virtual ~Person(); 

    void setID(const string& id);
    void setPassWord(const string& passWord);
    void setName(const string& name);
    void setGender(const string& gender);
    void setNumberPhone(const string& phone);
    void setAddress(const string& address);
    void setBirthDay(int day, int month, int year);

    string getID() const;
    string getPassWord() const;
    string getName() const;
    string getGender() const;
    string getNumberPhone() const;
    string getAddress() const;
    string getBirthDay() const;

    virtual void Show() const = 0; 
    virtual void ShowByID() const = 0;
    bool checkLogin(const string& username, const string& password);
};

#endif
