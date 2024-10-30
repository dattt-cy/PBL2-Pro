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

using namespace std;

void drawBox(int x, int y, int width, int height) {
    gotoXY(x, y);
    cout << '+';
    for (int i = 0; i < width; ++i) cout << '-';
    cout << '+';

    for (int i = 0; i < height; ++i) {
        gotoXY(x, y + i + 1);
        cout << '|';
        gotoXY(x + width + 1, y + i + 1);
        cout << '|';
    }

    gotoXY(x, y + height + 1);
    cout << '+';
    for (int i = 0; i < width; ++i) cout << '-';
    cout << '+';
}

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

bool isValidCharacter(char ch) {
    if ((ch >= '0' && ch <= '9') || 
        (ch >= 'a' && ch <= 'z') || 
        (ch >= 'A' && ch <= 'Z') || 
        ch == 9 || ch == 8) {
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
                if (input_admin.length() <= 16) {
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

int login(Admin_Manage& n) {
    int loginResult = 3; 
    do {
        system("cls"); 
        drawInterface();
        gotoXY(24, 5);
        string username = getInput_admin(24, 5, false); 
        gotoXY(24, 8);
        string password = getInput(24, 8, true);

        gotoXY(15, 13); 
        loginResult = n.checkLogin(username, password);

        if (loginResult == 1) {
            setTextColor(2); 
            cout << "\nDang nhap thanh cong voi quyen Admin!\n";
            system("pause");
            return 1; 
            
        } else if (loginResult == 2) {
            setTextColor(2); 
            cout << "\nDang nhap thanh cong voi quyen Customer!\n";
            system("pause");
            return 2;
        } else {
            setTextColor(12); 
            cout << "\nTen dang nhap hoac mat khau khong hop le! Vui long thu lai.\n";
            system("pause");
        }
    } while (loginResult != 1 && loginResult != 2); 

    return 0;
}