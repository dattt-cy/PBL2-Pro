#include "Admin_Manage.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include "Admin.h"

using namespace std;
string Admin_Manage::phone = ""; 
string Admin_Manage::name = ""; 
string Admin_Manage::id = "";
void Admin_Manage::sortByID() {
    ListNV.Sort();
}

void Admin_Manage::UpdateAdminID() {
    Node<Admin*>* current = ListNV.getHead();
    int cnt = 1;

    while (current != nullptr) {
        string currentID = current->data->getID();
        if (currentID.find("AD") == 0) { 
            string newID = "AD" + string((cnt < 10 ? "00" : (cnt < 100 ? "0" : ""))) + to_string(cnt);
            current->data->setID(newID);
            cnt++;
        }
        current = current->next;
    }
}

int Admin_Manage::AdminID(const string& filename) {
    ifstream file(filename);  
    if (!file.is_open()) { 
        cerr << "Khong the mo file: " << filename << endl;
        return 0;
    }
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty() && line.find("KH") == 0) { 
            count++;
        }
    }
    file.close();  
    return count;
}

string Admin_Manage::generateNewID() {
    stringstream ss;
    ss << "KH" << setw(3) << setfill('0') << AdminID("Customerr.txt") + 1;  


    return ss.str();  
}

void Admin_Manage::ShowAdmin() {
    Node<Admin*>* current = ListNV.getHead();
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
    cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        | Ngay vao lam    |" << endl;
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
    while (current != nullptr) {
        current->data->Show();
        current = current->next;
    }

    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
}

void Admin_Manage::ShowCustomer() {
    Node<Admin*>* current = ListKH.getHead();
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
    cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        |" << endl;
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
    while (current != nullptr) {
        current->data->ShowC();
        current = current->next;
    }

    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
}

void Admin_Manage::addAdmin(Admin* admin) {
    ListNV.push_back(admin);
}

Date Admin_Manage::parseDate(const string& dateStr) {
    stringstream ss(dateStr);
    string token;
    Date date;

    try {
       
        getline(ss, token, '/');
        if (token.empty()) throw invalid_argument("Invalid day format");
        date.day = stoi(token);

        
        getline(ss, token, '/');
        if (token.empty()) throw invalid_argument("Invalid month format");
        date.month = stoi(token);

        
        getline(ss, token, '/');
        if (token.empty()) throw invalid_argument("Invalid year format");
        date.year = stoi(token);

    } catch (const invalid_argument& e) {
        cerr << "Loi: Dinh dang ngay thang khong dung - " << e.what() << endl;
        date = {0, 0, 0}; 
    }

    return date;
}


void Admin_Manage::ReadFileAdmin(const string& filename) {
    ifstream filein(filename);
    if (!filein.is_open()) {
        cerr << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        Admin* admin = new Admin();
        string token;
        if (getline(ss, token, ',')) admin->setID(token);

        if(getline(ss, token, ',')) admin->setpassWord(token);
       
        if (getline(ss, token, ',')) admin->setName(token);

        if (getline(ss, token, ',')) admin->setGender(token);

        if (getline(ss, token, ',')){
            Date birthDate = parseDate(token);
            admin->setbirthDay(birthDate.day, birthDate.month, birthDate.year);
        }
        if (getline(ss, token, ',')) admin->setnumberPhone(token);
        
        if (getline(ss, token, ',')) admin->setAddress(token);

        if (getline(ss, token, ',')) {
            Date workDate = parseDate(token);
            admin->setDayofwork(workDate.day, workDate.month, workDate.year);
        }

        addAdmin(admin);
    }

    filein.close();
}

void Admin_Manage::WriteFileAdmin(const string& filename) {
    ofstream fileout(filename, ios::out); 
    if (!fileout.is_open()) {
        cout << "Khong the mo file de ghi!" << endl;
        return;
    }

    Node<Admin*>* current = ListNV.getHead();

    while (current != nullptr) {
        Admin* admin = current->data;

        string birthday = admin->getbirthDay();
        string dayofwork = admin->getDayofwork();
        Date birthDate = parseDate(birthday); 
        Date workDate = parseDate(dayofwork);

        fileout << admin->getID() << ","
                << admin->getpassWord() << ","
                << admin->getName() << ","
                << admin->getGender() << ",";

        fileout << birthDate.day<< "/"
                << birthDate.month << "/"
                << birthDate.year << ",";

        fileout << admin->getnumberPhone() << ","
                << admin->getAddress() << ",";

        fileout << workDate.day <<"/"
                << workDate.month << "/"
                << workDate.year << "\n";

        current = current->next;
    }
    fileout.close();
}

void Admin_Manage::inputAdmin() {
    Admin* admin = new Admin();
    string input;
    int day, month, year;
    int gt;

    admin->setID(generateNewID());
    cout << "***-----MOI BAN NHAP THONG TIN ADMIN-----***" << endl;
    cout << "ID cua ban la: " << generateNewID() << endl;
    admin->setID(generateNewID());
    cout << "Nhap ten Admin moi: ";
    cin.ignore();
    getline(cin, input); 
    admin->setName(input);

    cout << "Nhap mat khau: ";
    cin.ignore();
    getline(cin, input); 
    admin->setpassWord(input);

    while (true) {
        cout << "Nhap gioi tinh Admin (1: Nam, 0: Nu): ";
        cin >> gt;

        if (gt == 1) {
            input = "Nam";
            admin->setGender(input);
            break;  
        } else if (gt == 0) {
            input = "Nu";
            admin->setGender(input);
            break;  
        } else {
            cout << "Nhap sai! Vui long nhap lai!" << endl;
        }
    }
    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    cin.ignore();
    getline(cin, input); 
    Date birthDate = parseDate(input); 
    admin->setbirthDay(birthDate.day, birthDate.month, birthDate.year);

    while (true) {
        cout << "Nhap so dien thoai: ";
        getline(cin, input); 

        if (input.length() != 10 || input[0] != '0') {
            cout << "So dien thoai khong hop le! Vui long nhap lai.\n";
            continue;
        }

        bool valid = true;
        for (int i = 1; i < input.length(); ++i) {
            if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            admin->setnumberPhone(input);
            break; 
        } else {
            std::cout << "So dien thoai chi duoc chua cac chu so. Vui long nhap lai.\n";
            continue;
        }
    }

    cout << "Nhap dia chi: ";
    getline(cin, input); 
    admin->setAddress(input);

    cout << "Nhap ngay vao lam (dd/mm/yyyy): ";
    getline(cin, input); 
    Date workDate = parseDate(input); 
    admin->setDayofwork(workDate.day, workDate.month, workDate.year);

    addAdmin(admin);
    cout << "Da them Admin thanh cong!" << endl;
    WriteFileAdmin("Admin.txt");
    ShowAdmin();
}

void Admin_Manage::DeleteAdmin(string ID) {
    if (ListNV.removeById(ID)) {
        cout << "Admin co ID " << ID << " da duoc xoa." << endl;
        Admin_Manage::UpdateAdminID();
        WriteFileAdmin("Admin.txt");
        cout << "Danh sach Admin sau khi xoa:" << endl;
        ShowAdmin();
    } else {
        cout << "Admin co ID " << ID << " khong ton tai." << endl;
    }   
}

bool Admin_Manage::findAdmin(const string& ID) {
    Node<Admin*>* current = ListNV.getHead();  
    while (current != NULL) {
        if (current->data != NULL && current->data->getID() == ID) {
            cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
            cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        | Ngay vao lam    |" << endl;
            cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;

            cout <<"| " << left << setw(17) << current->data->getID() << "| " <<setw(22) << current->data->getName() << "| " <<setw(11)<< current->data->getGender() << "| " <<setw(16) << current->data->getbirthDay() <<"| " << setw(19) << current->data->getnumberPhone() <<"| " << setw(31) << current->data->getAddress() <<"| " << setw(16) << current->data->getDayofwork()<<  "|"  << endl;
            cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;

            return true;  
        }
        current = current->next; 
    }
    return false;
}

void Admin_Manage::searchByID(const string& ID) {
    if (findAdmin(ID)) {
        cout << "Admin voi ID " << ID << " duoc tim thay!" << endl;
    } else {
        cout << "Khong tim thay Admin voi ID " << ID << "!" << endl;
    }
}

LinkedList<Admin*> Admin_Manage::getList() {
    return ListNV;
}

LinkedList<Admin*> Admin_Manage::getListKH() {
    return ListKH;
}

int Admin_Manage::checkLogin(const string& username, const string& password) {
    Node<Admin*>* current = ListNV.getHead();
    while(current != NULL){
        if (current->data->checkLogin(username, password)) {
            return 1; 
        }
        current = current->next;
    }
    Node<Admin*>* cur = ListKH.getHead();
    while (cur != nullptr) {
        if (cur->data->checkLogin(username, password)) {
            name = cur->data->getName();
            phone = cur->data->getnumberPhone();
            id = cur->data->getID();
            return 2; 
        }
        cur = cur->next;
    }
    return 0; 
}

void Admin_Manage::ReadFileCustomer(const string& filename) {
    ifstream filein(filename);
    if (!filein.is_open()) {
        cerr << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        Admin* customer = new Admin();
        string token;

        if (getline(ss, token, ',')) customer->setID(token);

        if (getline(ss, token, ',')) customer->setpassWord(token);

        if (getline(ss, token, ',')) customer->setName(token);

        if (getline(ss, token, ',')) customer->setGender(token);

        if (getline(ss, token, ',')) {
            Date birthDate = parseDate(token);
            customer->setbirthDay(birthDate.day, birthDate.month, birthDate.year);
        }
        if (getline(ss, token, ',')) customer->setnumberPhone(token);

        if (getline(ss, token, ',')) customer->setAddress(token);

        ListKH.push_back(customer);
    }
    filein.close();
}

void Admin_Manage::inputCustomer() {
    Admin* customer = new Admin();
    string input;
    int day, month, year;
    int gt;

    customer->setID(generateNewID());
    cout << "***-----MOI BAN NHAP THONG TIN KHACH HANG-----***" << endl;

    cout << "ID cua ban la: " << generateNewIDKH() << endl;
    customer->setID(generateNewIDKH());
    
    cout << "Nhap ten Khach hang moi: ";
    cin.ignore();
    getline(cin, input); 
    customer->setName(input);

    cout << "Nhap mat khau: ";
    cin.ignore();
    getline(cin, input); 
    customer->setpassWord(input);

    while (true) {
        cout << "Nhap gioi tinh Khach hang (1: Nam, 0: Nu): ";
        cin >> gt;
        if (gt == 1) {
            input = "Nam";
            customer->setGender(input);
            break; 
        } else if (gt == 0) {
            input = "Nu";
            customer->setGender(input);
            break; 
        } else {
            cout << "Nhap sai! Vui long nhap lai!" << endl;
        }
    }
    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    cin.ignore();
    getline(cin, input); 
    Date birthDate = parseDate(input); 
    customer->setbirthDay(birthDate.day, birthDate.month, birthDate.year);

    while (true) {
        cout << "Nhap so dien thoai: ";
        getline(cin, input); 

        if (input.length() != 10 || input[0] != '0') {
            cout << "So dien thoai khong hop le! Vui long nhap lai.\n";
            continue;
        }
        bool valid = true;
        for (int i = 1; i < input.length(); ++i) {
            if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            customer->setnumberPhone(input);
            break; 
        } else {
            std::cout << "So dien thoai chi duoc chua cac chu so. Vui long nhap lai.\n";
            continue;
        }
    }
    cout << "Nhap dia chi: ";
    getline(cin, input); 
    customer->setAddress(input);

    ListKH.push_back(customer);
    cout << "Da them khach hang thanh cong!" << endl;
    WriteFileCustomer("Customerr.txt");
    ShowCustomer();
}
void Admin_Manage::WriteFileCustomer(const string& filename) {
    ofstream fileout(filename, ios::out); 
    if (!fileout.is_open()) {
        cout << "Khong the mo file de ghi!" << endl;
        return;
    }

    Node<Admin*>* current = ListKH.getHead(); 

    while (current != nullptr) {
        Admin* admin = current->data;
        string birthday = admin->getbirthDay();
        string dayofwork = admin->getDayofwork();
        Date birthDate = parseDate(birthday); 
        Date workDate = parseDate(dayofwork);

        fileout << admin->getID() << ","
                << admin->getpassWord() << ","
                << admin->getName() << ","
                << admin->getGender() << ",";

        fileout << birthDate.day<< "/"
                << birthDate.month << "/"
                << birthDate.year << ",";

        fileout << admin->getnumberPhone() << ","
                << admin->getAddress() << "\n";

        current = current->next;
    }
    fileout.close(); 
}

void Admin_Manage::UpdateCustomerID() {
    Node<Admin*>* current = ListKH.getHead();
    int cnt = 1;

    while (current != nullptr) {
        string currentID = current->data->getID();
        if (currentID.find("KH") == 0) { 
            string newID = "KH" + string((cnt < 10 ? "00" : (cnt < 100 ? "0" : ""))) + to_string(cnt);
            current->data->setID(newID);
            cnt++;
        }
        current = current->next;
    }
}
int Admin_Manage::CustomerID(const string& filename) {
    ifstream file(filename);  
    if (!file.is_open()) { 
        cerr << "Khong the mo file: " << filename << endl;
        return 0;
    }
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty() && line.find("KH") == 0) { 
            count++;
        }
    }
    file.close(); 
     return count; 
}

string Admin_Manage::generateNewIDKH() {
    std::stringstream ss;
    ss << "KH" << std::setw(3) << std::setfill('0') << CustomerID("Customerr.txt") + 1;
    return ss.str();
     }

void Admin_Manage::DeleteCustomer(string ID) {
    if (ListKH.removeById(ID)) {
        cout << "Nhan vien co ID " << ID << " da duoc xoa." << endl;
        Admin_Manage::UpdateCustomerID();
        WriteFileCustomer("Admin.txt");
        cout << "Danh sach nhan vien sau khi xoa:" << endl;
        ShowCustomer();
    } else {
        cout << "Nhan vien co ID " << ID << " khong ton tai." << endl;
    }   
}

bool Admin_Manage::findCustomer(const string& ID) {
    Node<Admin*>* current = ListKH.getHead();  
    while (current != NULL) {
        if (current->data != NULL && current->data->getID() == ID) {
            cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
            cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        |" << endl;
            cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;

            cout <<"| " << left << setw(17) << current->data->getID() << "| " <<setw(22) << current->data->getName() << "| " <<setw(11)<< current->data->getGender() << "| " <<setw(16) << current->data->getbirthDay() <<"| " << setw(19) << current->data->getnumberPhone() <<"| " << setw(31) << current->data->getAddress() <<"| " << setw(16) <<  "|"  << endl;
            cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;

            return true;  
        }
        current = current->next; 
    }
    return false;
}
bool Admin_Manage::createAccount(const string& ID, const string& password, const string& name) {
    Node<Admin*>* current = ListKH.getHead();
    while (current != NULL) {
        if (current->data->getID() == ID) {
            return false; 
        }
        current = current->next;
    }
    Admin* admin = new Admin();
    admin->setID(ID);
    admin->setpassWord(password);
    admin->setName(name);
    ListKH.push_back(admin);
    return true;
}
bool Admin_Manage::isCustomerInfoComplete(const string& id) {
    Node<Admin*>* current = ListKH.getHead();
    while (current != nullptr) {
        if (current->data->getID() == id) {
            return !current->data->getbirthDay().empty() &&
                   !current->data->getAddress().empty() && !current->data->getGender().empty() &&
                   !current->data->getnumberPhone().empty();
        }
        current = current->next;
    }
    return false;
}


void Admin_Manage::updateCustomerInfo(const string& id, const string& dob, const string& address, const string& gender, const string& phone) {
    Node<Admin*>* current = ListKH.getHead();
    while (current != nullptr) {
        if (current->data->getID() == id) {
            if (!dob.empty()) {
                Date birthDate = parseDate(dob);
                current->data->setbirthDay(birthDate.day, birthDate.month, birthDate.year);
            }
            if (!address.empty()) {
                current->data->setAddress(address);
            }
            if (!gender.empty()) {
                current->data->setGender(gender);
            }
            if (!phone.empty()) {
                current->data->setnumberPhone(phone);
            }
            break;
        }
        current = current->next;
    }
    WriteFileCustomer("Customerr.txt");
}
