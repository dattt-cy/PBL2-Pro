#ifndef ADMIN_MANAGE_H
#define ADMIN_MANAGE_H

#include "LinkedList.h"
#include "Admin.h"
#include <string>

class Admin_Manage {
private:
    LinkedList<Admin*> ListNV;
    LinkedList<Admin*> ListKH;

public:
    void sortByID();
    void WriteFileAdmin(const std::string& filename);
    void ShowAdmin();
    void addAdmin(Admin* admin);
    void ReadFileAdmin(const std::string& filename);
    void DeleteAdmin(std::string ID);
    void UpdateAdminID();
    int AdminID(const string& filename);
    void inputAdmin();
    string generateNewID();
    bool findAdmin(const string& ID);
    void searchByID(const string& ID);
    Date parseDate(const string& date);
    LinkedList<Admin*> getList();
    LinkedList<Admin*> getListKH();
    int checkLogin(const string& username, const string& password);
    void ReadFileCustomer(const string& filename);
    void ShowCustomer();
    void inputCustomer();
    void WriteFileCustomer(const string& filename);
    void DeleteCustomer(string ID);
    void UpdateCustomerID();
    bool findCustomer(const string& ID);
};

#endif // ADMIN_MANAGE_H