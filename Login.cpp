#define byte win_byte_override
#include <windows.h>
#undef byte
#include <cstddef>
#include "login.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Admin.h"
#include "Admin_Manage.h"
#include "Set.h"
#include "menu.h"
#include <sstream>
#include <fstream>
#include "support.h"

using namespace std;

void drawInterface() {
    setTextColor(11);
    drawBox(10, 0, 50, 10);
    gotoXY(28, 2);
    cout << "QUAN LI SHOP QUAN AO";

    setTextColor(15);
    gotoXY(13, 5);
    cout << "ID   ";
    drawBox(23, 4, 30, 1);
    setTextColor(15);
    gotoXY(12, 8);
    cout << "Password ";
    drawBox(23, 7, 30, 1);

    gotoXY(24, 10);
    cout << "[Nhan Tab de hien thi password]";
}
void drawCreateAccountInterface() {
    setTextColor(11);
     drawBox(10, 0, 60, 15);
    gotoXY(28, 2);
    cout << "TAO TAI KHOAN MOI";

    setTextColor(15);
    gotoXY(13, 5);
    cout << "Ho va ten: ";
    drawBox(33, 4, 30, 1);
    setTextColor(15);
    gotoXY(13, 8);
    cout << "Mat khau moi: ";
    drawBox(33, 7, 30, 1);
    setTextColor(15);
    gotoXY(13, 11);
    cout << "Xac nhan mat khau: ";
    drawBox(33, 10, 30, 1);
}
void drawCompleteCustomerInfoInterface() {
    setTextColor(11);
    drawBox(10, 0, 65, 20);
    gotoXY(28, 2);
    cout << "BO SUNG THONG TIN KHACH HANG";

    setTextColor(15);
    gotoXY(13, 5);
    cout << "Ngay sinh: ";
    drawBox(33, 4, 40, 1);
    setTextColor(15);
    gotoXY(13, 8);
    cout << "Dia chi: ";
    drawBox(33, 7, 40, 1);
    setTextColor(15);
    gotoXY(13, 11);
    cout << "1. Nam/0. Nu: ";
    drawBox(33, 10, 40, 1);
    setTextColor(15);
    gotoXY(13, 14);
    cout << "So dien thoai: ";
    drawBox(33, 13, 40, 1);
}

bool isValidCharacter(char ch) {
    if ((ch >= '0' && ch <= '9') || 
        (ch >= 'a' && ch <= 'z') || 
        (ch >= 'A' && ch <= 'Z') || 
        ch == 9 || ch == 8 || ch == ' ' || ch == '/' || ch == ',' || ch == '-') { 
        return true;
    }
    return false;
}
string getInput_admin(int x, int y, bool hide) {
    string input_admin = "";
    char ch;
    gotoXY(x, y);

    while ((ch = _getch()) != 13) {
        if (isValidCharacter(ch)) {
            if (ch == 0 || ch == 224) {
                _getch();
                continue;
            }

            if (ch == 8) {
                if (!input_admin.empty()) {
                    input_admin.resize(input_admin.size() - 1);
                    cout << "\b \b";
                }
            } else if (isprint(ch)) {
                if (input_admin.length() <= 50) {
                    input_admin.push_back(ch);
                    cout << ch;
                }
            }
        }
    }
    return input_admin;
}

string getInput(int x, int y, bool hide) {
    string input = "";
    char ch;
    gotoXY(x, y);

    while ((ch = _getch()) != 13) {
        if (isValidCharacter(ch)) {
            if (ch == 0 || ch == 224) {
                _getch();
                continue;
            }

            if (ch == 8) {
                if (!input.empty()) {
                    input.resize(input.size() - 1);
                    cout << "\b \b";
                }
            } else if (ch == 9) {
                hide = !hide;
                gotoXY(x, y);
                cout << string(input.length(), ' ');
                gotoXY(x, y);
                if (hide) {
                    cout << string(input.length(), '*');
                } else {
                    cout << input;
                }
            } else if (isprint(ch)) {
                if (input.length() <= 8) {
                    input.push_back(ch);
                    cout << '*';
                }
            }
        }
    }
    return input;
}

void completeCustomerInfo(Admin_Manage& n, const string& id) {
    system("cls");
    drawCompleteCustomerInfoInterface();

    setTextColor(15);
    string input;
    string dob = "";
     do {
        gotoXY(34, 5);
        dob = getInput_admin(34, 5, false);
        if (!isDate(dob)) {
            setTextColor(4);
            gotoXY(34, 5);
            cout << "Ngay sinh khong hop le. Hay nhap lai.";
            setTextColor(15);
            gotoXY(34, 5); 
            dob = getInput_admin(34, 5, false);

            gotoXY(34, 5);
            cout << "                                        "; 
        }
    } while (!isDate(dob));

    gotoXY(34, 8);
    input = getInput_admin(34, 8, false);
    string address = input;
    string gender = "";
     do {
        gotoXY(34, 11);
        gender = getInput_admin(34, 11, false);
        if (!isSex(gender)) {
            setTextColor(4);
            gotoXY(34, 11);
            cout << "Gioi tinh khong hop le. Hay nhap lai.";
            setTextColor(15);
            gotoXY(34, 11); 
            gender = getInput_admin(34, 11, false);

            gotoXY(34, 11);
            cout << "                                        "; 
        }
    } while (!isSex(gender));
    string phone = "";
     do {
        gotoXY(34, 14);
        phone = getInput_admin(34, 14, false);
        if (!isPhoneNumber(phone)) {
            setTextColor(4);
            gotoXY(34, 14);
            cout << "So dien thoai phai bao gom 10 chu so.";
            setTextColor(15);
            gotoXY(34, 14); 
            phone = getInput_admin(34, 14, false);

            
            gotoXY(34, 14);
            cout << "                                       "; 
        }
    } while (!isPhoneNumber(phone));
    if(gender == "1"){ 
        gender = "Nam";
    }
    else if(gender == "0"){
        gender = "Nu";
    }
    n.updateCustomerInfo(id, dob, address, gender, phone);

    gotoXY(0, 23);

    cout << "<!> Thong tin da duoc cap nhat thanh cong!" << endl;
    system("pause");
}

int createAccount(Admin_Manage& n) {
    system("cls");
    drawCreateAccountInterface();
    gotoXY(34, 5);
    string username = getInput_admin(34, 5, false);
    gotoXY(34, 8);
    string password = getInput(34, 8, true);
    gotoXY(34, 11);
    string confirmPassword = getInput(34, 11, true);

    if (password != confirmPassword) {
        setTextColor(4);
        gotoXY(34, 14);
        cout << "Mat khau khong khop. Vui long thu lai.";
        system("pause");
        return 0;
    }

    string newID = n.generateNewID();

    gotoXY(15, 17);
    if (n.createAccount(newID, password, username)) {
        setTextColor(2);
        cout << "\nTao tai khoan thanh cong! ID cua ban la: " << newID << "\n";
        system("pause");
        return 1;
    } else {
        setTextColor(4);
        cout << "\nTao tai khoan that bai. Ten dang nhap da ton tai.\n";
        system("pause");
        return 0;
    }
}
int login(Admin_Manage& n) {
    int loginResult = 3; 
    do {
        system("cls"); 
        drawInterface();
        gotoXY(24, 5);
        string id = getInput_admin(24, 5, false); 
        if(id == "0"){
            return 0;
        }
        gotoXY(24, 8);
        string password = getInput(24, 8, true);

        gotoXY(15, 13); 
        loginResult = n.checkLogin(id, password);

        if (loginResult == 1) {
            setTextColor(2); 
            cout << "\nDang nhap thanh cong voi quyen Admin!\n";
            system("pause");
            return 1; 
            
        } else if (loginResult == 2) {
            setTextColor(2); 
            cout << "\nDang nhap thanh cong voi quyen Customer!\n";
            system("pause");
            if (!n.isCustomerInfoComplete(id)) {
                completeCustomerInfo(n, id);
                continue;
            }
            return 2;
        } else {
            setTextColor(4); 
            cout << "\nDang nhap that bai. Vui long thu lai hoac nhap 0 vao o ID de thoat qua trinh dang nhap!!.\n";
            system("pause");
            setTextColor(7); 
        }  
    } while (loginResult != 1 && loginResult != 2); 

    return 0;
}