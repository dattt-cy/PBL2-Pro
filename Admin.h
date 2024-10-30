#include <iostream>
#include <sstream>
#include <string.h>
#include "LinkedList.h"
#pragma once

#define ADMIN_H
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

class Admin {
    private:
        string numberPhone;
        string ID;
        string passWord;
        string name;
        string gender;
        string address;
        Date birthDay;
        Date dayofWork;
        
    public:
        static int count;
        Admin();
        ~Admin();
        void setnumberPhone(string phone);
        void setID(string id);
        void setpassWord(string pass);
        void setName(string n);
        void setGender(string g);
        void setAddress(string addr); 
        void setbirthDay(int day, int month, int year);
        void setDayofwork(int day, int month, int year);
       
        string getAddress();
        string getGender();
        string getName();
        string getpassWord();
        string getID();
        string getbirthDay();
        string getnumberPhone();
        string getDayofwork();
        
        void Show();
        bool checkLogin(const string& username, const string& password); 
        void ShowC();
};