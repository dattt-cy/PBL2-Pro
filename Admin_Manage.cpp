#include "Admin_Manage.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include "Admin.h"
#include "support.h"
using namespace std;
string Admin_Manage::phone = ""; 
string Admin_Manage::name = ""; 
string Admin_Manage::id = "";
void Admin_Manage::sortByID() {
    list.Sort();
}

void Admin_Manage::UpdateAdminID() {
    Node<Person*>* current = list.getHead();
    int adminCnt = 1;
    int customerCnt = 1;

    while (current != nullptr) {
        Admin* admin = dynamic_cast<Admin*>(current->data);
        Customer* customer = dynamic_cast<Customer*>(current->data);

        if (admin) {
            string currentID = admin->getID();
            if (currentID.find("AD") == 0) {
                string newID = "AD" + string((adminCnt < 10 ? "00" : (adminCnt < 100 ? "0" : ""))) + to_string(adminCnt);
                admin->setID(newID);
                adminCnt++;
            }
        } else if (customer) {
            string currentID = customer->getID();
            if (currentID.find("KH") == 0) {
                string newID = "KH" + string((customerCnt < 10 ? "00" : (customerCnt < 100 ? "0" : ""))) + to_string(customerCnt);
                customer->setID(newID);
                customerCnt++;
            }
        }

        current = current->next;
    }
}

int Admin_Manage::AdminID(const string& filename, const string& type) {
    ifstream file(filename);  
    if (!file.is_open()) { 
        cerr << "Khong the mo file: " << filename << endl;
        return 0;
    }
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty() && line.find(type) == 0) { 
            count++;
        }
    }
    file.close();  
    return count;
}

string Admin_Manage::generateNewID(const string& type) {
    stringstream ss;
    if (type == "AD") {
        ss << "AD" << setw(3) << setfill('0') << AdminID("Data.txt", "AD") + 1;
    } else if (type == "KH") {
        ss << "KH" << setw(3) << setfill('0') << AdminID("Data.txt", "KH") + 1;
    }
    return ss.str();
}
void Admin_Manage::ShowAdmin() {
    Node<Person*>* current = list.getHead();
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
    cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        | Ngay vao lam    |" << endl;
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
    while (current != nullptr) {
        Admin* admin = dynamic_cast<Admin*>(current->data);
        if (admin) {
            admin->Show();
        }
        current = current->next;
    }
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
}

void Admin_Manage::ShowCustomer() {
    Node<Person*>* current = list.getHead();
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
    cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        |" << endl;
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
    while (current != nullptr) {
        Customer* customer = dynamic_cast<Customer*>(current->data);
        if (customer) {
            customer->Show();
        }
        current = current->next;
    }
    cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
}

void Admin_Manage::addPerson(Person* person) {
    list.push_back(person);
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
void Admin_Manage::ReadFile(const string& filename) {
    ifstream filein(filename);
    if (!filein.is_open()) {
        cerr << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        string token;

        if (!getline(ss, token, ',')) continue;
        string id = token;

        Person* person = nullptr;
        if (id.find("AD") == 0) {
            person = new Admin();
        } else if (id.find("KH") == 0) {
            person = new Customer();
        }
        if (person) {
            person->setID(id);
            if (getline(ss, token, ',')) person->setPassWord(token);
            if (getline(ss, token, ',')) person->setName(token);
            if (getline(ss, token, ',')) person->setGender(token);
            if (getline(ss, token, ',')) {
                Date birthDate = parseDate(token);
                person->setBirthDay(birthDate.day, birthDate.month, birthDate.year);
            }
            if (getline(ss, token, ',')) person->setNumberPhone(token);
            if (getline(ss, token, ',')) person->setAddress(token);

            if (Admin* admin = dynamic_cast<Admin*>(person)) {
                if (getline(ss, token, ',')) {
                    Date workDate = parseDate(token);
                    admin->setDayofwork(workDate.day, workDate.month, workDate.year);
                }
            }
            addPerson(person);
        }
    }

    filein.close();
}
void Admin_Manage::WriteFile(const string& filename) {
    ofstream fileout(filename, ios::out); 
    if (!fileout.is_open()) {
        cout << "Khong the mo file de ghi!" << endl;
        return;
    }

    Node<Person*>* current = list.getHead();

    while (current != nullptr) {
        Admin* admin = dynamic_cast<Admin*>(current->data);
        Customer* customer = dynamic_cast<Customer*>(current->data);

        if (admin) {
            string birthday = admin->getBirthDay();
            string dayofwork = admin->getDayofwork();
            Date birthDate = parseDate(birthday); 
            Date workDate = parseDate(dayofwork);

            fileout << admin->getID() << ","
                    << admin->getPassWord() << ","
                    << admin->getName() << ","
                    << admin->getGender() << ",";

            fileout << birthDate.day << "/"
                    << birthDate.month << "/"
                    << birthDate.year << ",";

            fileout << admin->getNumberPhone() << ","
                    << admin->getAddress() << ",";

            fileout << workDate.day << "/"
                    << workDate.month << "/"
                    << workDate.year << "\n";
        } else if (customer) {
            string birthday = customer->getBirthDay();
            Date birthDate = parseDate(birthday);

            fileout << customer->getID() << ","
                    << customer->getPassWord() << ","
                    << customer->getName() << ","
                    << customer->getGender() << ",";

            fileout << birthDate.day << "/"
                    << birthDate.month << "/"
                    << birthDate.year << ",";

            fileout << customer->getNumberPhone() << ","
                    << customer->getAddress() << "\n";
        }

        current = current->next;
    }
    fileout.close();
}
void Admin_Manage::inputPerson(const string& type) {
    Person* person = nullptr;
    if (type == "Admin") {
        person = new Admin();
        person->setID(generateNewID("AD"));
    } else if (type == "Customer") {
        person = new Customer();
        person->setID(generateNewID("KH"));
    } else {
        cout << "Loai nguoi dung khong hop le!" << endl;
        return;
    }

    string input;
    int day, month, year;
    string gt;

    cout << "***-----MOI BAN NHAP THONG TIN " << type << "-----***" << endl;
    cout << "ID cua ban la: " << person->getID() << endl;

    while (true) {
        cout << "Nhap ten " << type << " moi (nhap 0 de huy): ";
        getline(cin, input);
        if (input == "0") return;
        if (!input.empty()) {
            person->setName(input);
            break;
        }
        cout << "Ten khong duoc de trong. Vui long nhap lai." << endl;
    }

    while (true) {
        cout << "Nhap mat khau (nhap 0 de huy): ";
        getline(cin, input);
        if (input == "0") return;
        if (!input.empty()) {
            person->setPassWord(input);
            break;
        }
        cout << "Mat khau khong duoc de trong. Vui long nhap lai." << endl;
    }

    while (true) {
        cout << "Nhap gioi tinh " << type << " (1: Nam, 0: Nu, nhap 0 de huy): ";
        getline(cin, gt);
        if (gt == "0") return;
        if (gt == "1") {
            person->setGender("Nam");
            break;
        } else if (gt == "0") {
            person->setGender("Nu");
            break;
        } else {
            cout << "Nhap sai! Vui long nhap lai!" << endl;
        }
    }

    while (true) {
        cout << "Nhap ngay sinh (dd/mm/yyyy, nhap 0 de huy): ";
        getline(cin, input);
        if (input == "0") return;
        if (isDate(input)) {
            Date birthDate = parseDate(input);
            person->setBirthDay(birthDate.day, birthDate.month, birthDate.year);
            break;
        } else {
            cout << "Ngay sinh khong hop le! Vui long nhap lai." << endl;
        }
    }

    while (true) {
        cout << "Nhap so dien thoai (nhap 0 de huy): ";
        getline(cin, input);
        if (input == "0") return;
        if (input.length() == 10 && input[0] == '0' && all_of(input.begin() + 1, input.end(), ::isdigit)) {
            person->setNumberPhone(input);
            break;
        } else {
            cout << "So dien thoai khong hop le! Vui long nhap lai." << endl;
        }
    }

    cout << "Nhap dia chi (nhap 0 de huy): ";
    getline(cin, input);
    if (input == "0") return;
    person->setAddress(input);

    if (type == "Admin") {
        Admin* admin = dynamic_cast<Admin*>(person);
        Date birthDate = parseDate(admin->getBirthDay());
        Date workDate;

        while (true) {
            cout << "Nhap ngay vao lam (dd/mm/yyyy, nhap 0 de huy): ";
            getline(cin, input);
            if (input == "0") return;

            if (!isDate(input)) {
                cout << "Ngay vao lam khong hop le! Vui long nhap lai." << endl;
                continue;
            }

            workDate = parseDate(input);

            if (workDate.year < birthDate.year ||
                (workDate.year == birthDate.year && workDate.month < birthDate.month) ||
                (workDate.year == birthDate.year && workDate.month == birthDate.month && workDate.day <= birthDate.day)) {
                cout << "Ngay vao lam phai lon hon ngay sinh! Vui long nhap lai." << endl;
            } else {
                break;
            }
        }

        admin->setDayofwork(workDate.day, workDate.month, workDate.year);
    }

    addPerson(person);
    cout << "Da them " << type << " thanh cong!" << endl;
    WriteFile("Data.txt");
    if (type == "Admin") {
        ShowAdmin();
    } else {
        ShowCustomer();
    }
}
void Admin_Manage::editPerson(const string& id) {
    Node<Person*>* current = list.getHead();

    cout << "-----------------------------------------------------------" << endl;
    cout << "[!] Nhap 0 o vi tri bat ky de huy qua trinh sua." << endl;
    cout << "-----------------------------------------------------------" << endl;

    while (current != nullptr) {
        if (current->data->getID() == id) {
            Person* person = current->data;
            string input;

            cout << "Nhap ten moi (de trong neu khong thay doi): ";
            getline(cin, input);
            if (input == "0") {
                cout << "Da huy qua trinh sua." << endl;
                return;
            }
            if (!input.empty()) person->setName(input);

            cout << "Nhap mat khau moi (de trong neu khong thay doi): ";
            getline(cin, input);
            if (input == "0") {
                cout << "Da huy qua trinh sua." << endl;
                return;
            }
            if (!input.empty()) person->setPassWord(input);

            // Nhập giới tính
            do {
                cout << "Nhap gioi tinh moi (1: Nam, 0: Nu, de trong neu khong thay doi): ";
                getline(cin, input);
                if (input == "0") {
                    cout << "Da huy qua trinh sua." << endl;
                    return;
                }
                if (input.empty()) break; // Người dùng không muốn thay đổi
                if (input == "1") {
                    person->setGender("Nam");
                    break;
                } else if (input == "0") {
                    person->setGender("Nu");
                    break;
                } else {
                    cout << "Nhap khong hop le. Vui long nhap lai.\n";
                }
            } while (true);

            do {
                cout << "Nhap ngay sinh moi (dd/mm/yyyy, de trong neu khong thay doi): ";
                getline(cin, input);
                if (input == "0") {
                    cout << "Da huy qua trinh sua." << endl;
                    return;
                }
                if (input.empty()) break; // Người dùng không muốn thay đổi
                if (isDate(input)) {
                    Date birthDate = parseDate(input);
                    person->setBirthDay(birthDate.day, birthDate.month, birthDate.year);
                    break;
                } else {
                    cout << "Ngay sinh khong hop le. Vui long nhap lai.\n";
                }
            } while (true);

            cout << "Nhap so dien thoai moi (de trong neu khong thay doi): ";
            getline(cin, input);
            if (input == "0") {
                cout << "Da huy qua trinh sua." << endl;
                return;
            }
            if (!input.empty()) person->setNumberPhone(input);

            cout << "Nhap dia chi moi (de trong neu khong thay doi): ";
            getline(cin, input);
            if (input == "0") {
                cout << "Da huy qua trinh sua." << endl;
                return;
            }
            if (!input.empty()) person->setAddress(input);

            if (Admin* admin = dynamic_cast<Admin*>(person)) {
                do {
                    cout << "Nhap ngay vao lam moi (dd/mm/yyyy, de trong neu khong thay doi): ";
                    getline(cin, input);
                    if (input == "0") {
                        cout << "Da huy qua trinh sua." << endl;
                        return;
                    }
                    if (input.empty()) break; 
                    if (isDate(input)) {
                        Date workDate = parseDate(input);
                        Date birthDate = parseDate(admin->getBirthDay());
                        if (workDate.year > birthDate.year ||
                            (workDate.year == birthDate.year && workDate.month > birthDate.month) ||
                            (workDate.year == birthDate.year && workDate.month == birthDate.month && workDate.day > birthDate.day)) {
                            admin->setDayofwork(workDate.day, workDate.month, workDate.year);
                            break;
                        } else {
                            cout << "Ngay vao lam phai lon hon ngay sinh! Vui long nhap lai.\n";
                        }
                    } else {
                        cout << "Ngay vao lam khong hop le. Vui long nhap lai.\n";
                    }
                } while (true);
            }

            cout << "Thong tin da duoc cap nhat." << endl;
            WriteFile("Data.txt");
            return;
        }
        current = current->next;
    }
    cout << "Khong tim thay nguoi dung voi ID: " << id << endl;
}

void Admin_Manage::DeletePerson(const string& ID) {
    while (true) {
        cout << "Nhap ID cua nguoi dung ban muon xoa (nhap 0 de huy): ";
        string id;
        getline(cin, id);
        if (id == "0") return;

        if (list.removeById(id)) {
            cout << "Nguoi dung co ID " << id << " da duoc xoa." << endl;
            WriteFile("Data.txt");

            if (id.find("AD") == 0) {
                cout << "Danh sach Admin sau khi xoa:" << endl;
                ShowAdmin();
            } else if (id.find("KH") == 0) {
                cout << "Danh sach Customer sau khi xoa:" << endl;
                ShowCustomer();
            }
            break;
        } else {
            cout << "Nguoi dung co ID " << id << " khong ton tai. Vui long nhap lai." << endl;
        }
    }
}
bool Admin_Manage::findPerson(const string& ID) {
    Node<Person*>* current = list.getHead();  
    while (current != nullptr) {
        if (current->data != nullptr && current->data->getID() == ID) {
            Admin* admin = dynamic_cast<Admin*>(current->data);
            Customer* customer = dynamic_cast<Customer*>(current->data);

            if (admin) {
                cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
                cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        | Ngay vao lam    |" << endl;
                cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;

                admin->Show();
                cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+-----------------+" << endl;
            } else if (customer) {
                cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
                cout << "| ID               | Ten                   | Gioi tinh  | Ngay sinh       | So dien thoai      | Dia chi                        |" << endl;
                cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;

                customer->Show();
                cout << "+------------------+-----------------------+------------+-----------------+--------------------+--------------------------------+" << endl;
            }

            return true;  
        }
        current = current->next; 
    }
    return false;
}

LinkedList<Person*> Admin_Manage::getList() {
    return list;
}

int Admin_Manage::checkLogin(const string& username, const string& password) {
    Node<Person*>* current = list.getHead();
    while (current != nullptr) {
        if (current->data->checkLogin(username, password)) {
            name = current->data->getName();
            phone = current->data->getNumberPhone();
            id = current->data->getID();

            Admin* admin = dynamic_cast<Admin*>(current->data);
            if (admin) {
                return 1; // Admin login successful
            }

            Customer* customer = dynamic_cast<Customer*>(current->data);
            if (customer) {
                return 2; // Customer login successful
            }
        }
        current = current->next;
    }
    return 0;
}
bool Admin_Manage::createAccount(const string& ID, const string& password, const string& name) {
    Node<Person*>* current = list.getHead();
    while (current != nullptr) {
        if (current->data->getID() == ID) {
            return false; 
        }
        current = current->next;
    }
    Customer* customer = new Customer();
    customer->setID(ID);
    customer->setPassWord(password);
    customer->setName(name);
    list.push_back(customer);
    return true;
}
bool Admin_Manage::isCustomerInfoComplete(const std::string& id) {
    Node<Person*>* current = list.getHead();
    while (current != nullptr) {
        Customer* customer = dynamic_cast<Customer*>(current->data);
        if (customer && customer->getID() == id) {
            return !customer->getBirthDay().empty() &&
                   !customer->getAddress().empty() && !customer->getGender().empty() &&
                   !customer->getNumberPhone().empty();
        }
        current = current->next;
    }
    return false;
}

void Admin_Manage::updateCustomerInfo(const string& id, const string& dob, const string& address, const string& gender, const string& phone) {
    Node<Person*>* current = list.getHead();
    while (current != nullptr) {
        Customer* customer = dynamic_cast<Customer*>(current->data);
        if (customer && customer->getID() == id) {
            if (!dob.empty()) {
                Date birthDate = parseDate(dob);
                customer->setBirthDay(birthDate.day, birthDate.month, birthDate.year);
            }
            if (!address.empty()) {
                customer->setAddress(address);
            }
            if (!gender.empty()) {
                customer->setGender(gender);
            }
            if (!phone.empty()) {
                customer->setNumberPhone(phone);
            }
            break;
        }
        current = current->next;
    }
    WriteFile("Data.txt");
}
void Admin_Manage::deleteList() {
    list.clear();
}
Customer* Admin_Manage::findKhachHang(const string& id) {
    Node<Person*>* current = list.getHead();
    while (current != nullptr) {
        Customer* customer = dynamic_cast<Customer*>(current->data);
        if (customer && customer->getID() == id) {
            return customer;
        }
        current = current->next;
    }
    return nullptr;
}
