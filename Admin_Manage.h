#ifndef ADMIN_MANAGE_H
#define ADMIN_MANAGE_H

#include "LinkedList.h"
#include "Person.h"
#include "Admin.h"
#include "Customer.h"
#include <string>

class Admin_Manage {
private:
    LinkedList<Person*> list;

public:
    static string name;
    static string phone;
    static string id;

    void sortByID();
    void UpdateAdminID();
    int AdminID(const string& filename, const string& type);
    string generateNewID(const string& type);
    void ShowAdmin();
    void ShowCustomer();
    void addPerson(Person* person);
    Date parseDate(const string& dateStr);
    void ReadFile(const string& filename);
    void WriteFile(const string& filename);
    void inputPerson(const string& type);
    void DeletePerson(const string& ID);
    bool findPerson(const string& ID);
    LinkedList<Person*> getList();
    int checkLogin(const string& username, const string& password);
    bool createAccount(const string& ID, const string& password, const string& name);
    bool isCustomerInfoComplete(const string& id);
    void updateCustomerInfo(const string& id, const string& dob, const string& address, const string& gender, const string& phone);
    void deleteList();
    Customer* findKhachHang(const string& id);
    void editPerson(const std::string& id);
};

#endif // ADMIN_MANAGE_H