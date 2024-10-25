#include "menu.h"
#include <iostream>
#define byte win_byte_override
#include <windows.h>
#undef byte
#include <cstddef>
#include <conio.h>

using namespace std;

static void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

static void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawInterface(string menuItems[], int numItems, int selectedItem) {
    system("cls");

    int titlePos = 35;
    gotoXY(titlePos, 1);
    setTextColor(14);
    cout << "==================^^SHOP QUAN AO GAU GAU^^===================";

    int menuPos = 52;
    for (int i = 0; i < numItems; ++i) {
        gotoXY(menuPos, 3 + i);
        if (i == selectedItem) {
            setTextColor(11);
            cout << ">> " << menuItems[i];
        } else {
            setTextColor(15);
            cout << "   " << menuItems[i];
        }
    }
}

int interactiveMenu(string menuItems[], int numItems) {
    int selectedItem = 0;

    drawInterface(menuItems, numItems, selectedItem);

    while (true) {
        char ch = _getch();

        if (ch == -32) {
            ch = _getch();
            if (ch == 72) {
                selectedItem = (selectedItem - 1 + numItems) % numItems;
            } else if (ch == 80) {
                selectedItem = (selectedItem + 1) % numItems;
            }
        } else if (ch == 13) {
            return selectedItem;
        }

        drawInterface(menuItems, numItems, selectedItem);
    }
}

int subMenuCase0() {
    string menuItems[] = {
        "1.1 XEM QUAN AO DANH CHO NAM",
        "1.2 XEM QUAN AO DANH CHO NU",
        "1.3 XEM QUAN AO DANH CHO TRE EM",
        "1.4 XEM TAT CA QUAN AO",
        "1.5 THOAT"
    };
    int numItems = sizeof(menuItems) / sizeof(menuItems[0]);

    return interactiveMenu(menuItems, numItems);
}

int subMenuCase1() {
    string menuItems[] = {
        "2.1 TIM KIEM THEO TEN QUAN AO",
        "2.2 TIM KIEM THEO THUONG HIEU QUAN AO",
        "2.3 TIM KIEM THEO THE LOAI QUAN AO",
        "2.4 TIM KIEM THEO MAU SAC QUAN AO",
        "2.5 TIM KIEM THEO SIZE QUAN AO",
        "2.6 TIM KIEM KET HOP",
        "2.7 THOAT"  
    };
    int numItems = sizeof(menuItems) / sizeof(menuItems[0]);

    return interactiveMenu(menuItems, numItems);
}
int subMenuCase2() {
    string menuItems[] = {
        "3.1 THEM QUAN AO",
        "3.2 SUA QUAN AO THEO ID",
        "3.3 XOA QUAN AO THEO ID",
        "3.4 THOAT"
    };
    int numItems = sizeof(menuItems) / sizeof(menuItems[0]);

    return interactiveMenu(menuItems, numItems);
}

void menu(ClothesManager& manager, OrderManager& orderManager) {
    manager.readClothesFromFile("CLOTHES.txt");
    manager.Sort_ByID();
    
    while (true) {
        string mainMenuItems[] = {
            "1. XEM QUAN AO",
            "2. TIM KIEM QUAN AO",
            "3. THEM, SUA, XOA QUAN AO",
            "4. LUU VAO FILE",
            "5. DAT HANG",
            "6. THONG KE DOANH THU",
            "0. THOAT"
        };
        int numMainItems = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);

        int choice = interactiveMenu(mainMenuItems, numMainItems);

        switch (choice) {
            case 0: {
                bool exitSubMenu = false; 
                while (!exitSubMenu) {  
                    int subChoice = subMenuCase0();
                    switch (subChoice) {
                        case 0:
                            manager.printByType("1");
                            break;
                        case 1:
                            manager.printByType("2");
                            break;
                        case 2:
                            manager.printByType("3");
                            break;
                        case 3:
                            manager.printAllClothes();
                            break;
                        case 4:
                            exitSubMenu = true;  
                            break;
                    }
                }
                break;  
            }
            case 1: {
                bool exitSubMenu = false;  
                while (!exitSubMenu) {  
                    int subChoice = subMenuCase1();
                    string name, brand, type, color, size;
                    switch (subChoice) {
                        case 0:
                            system("cls");
                            cout << "<!> Nhap ten san pham can tim: ";
                            getline(cin, name);
                            manager.SearchBySubstring(name, "", "", "", "All");
                            system("pause");
                            break;
                        case 1:
                            system("cls");
                            cout << "<!> Nhap thuong hieu can tim: ";
                            getline(cin, brand);
                            manager.SearchBySubstring("", brand, "", "", "All");
                            break;
                        case 2:
                            system("cls");
                            cout << "<!> Nhap the loai (Male/Female/Children): ";
                            getline(cin, type);
                            manager.SearchBySubstring("", "", "", "", type);
                            break;
                        case 3:
                            system("cls");
                            cout << "<!> Nhap mau sac can tim: ";
                            getline(cin, color);
                            manager.SearchBySubstring("", "", color, "", "All");
                            break;
                        case 4:
                            system("cls");
                            cout << "<!> Nhap size can tim: ";
                            getline(cin, size);
                            manager.SearchBySubstring("", "", "", size, "All");
                            break;
                        case 5:
                            system("cls");
                            cout << "<!> Nhap thong tin ket hop: ";
                            getline(cin, name);
                            getline(cin, brand);
                            getline(cin, type);
                            getline(cin, color);
                            getline(cin, size);
                            manager.SearchBySubstring(name, brand, color, size, type);
                            break;
                        case 6:
                            exitSubMenu = true;  
                            break;
                    }
                }
                break;  
            }
            case 2: {
                bool exitSubMenu = false;  
                while (!exitSubMenu) {  
                    int subChoice = subMenuCase2();
                    string id;
                    string type;
                    switch (subChoice) {
                        case 0:
                            system("cls");
                            manager.addClothesManually();
                            break;
                          case 1: {
                            system("cls");
                            cout << "<!> Nhap the loai quan ao can sua (1: Male, 2: Female, 3: Children, 4: All): ";
                            string type;
                            getline(cin, type);
                            if (type == "1" || type == "2" || type == "3" || type == "4") {
                                manager.printByType(type);
                                cout << "<!> Nhap ma ID quan ao can sua: ";
                                getline(cin, id);
                                id = nameStr(id);
                                manager.EditClothesByID(id);
                                system("pause");
                            } else {
                                cout << "<!> Lua chon khong hop le !!" << endl;
                                system("pause");
                            }
                            break;
                        }
                        case 2:
                            system("cls");
                            cout << "<!> Nhap the loai quan ao can sua (1: Male, 2: Female, 3: Children, 4: All): ";
                            getline(cin, type);
                            if (type == "1" || type == "2" || type == "3" || type == "4") {
                                manager.printByType(type);
                                cout << "<!> Nhap ma ID quan ao can xoa: ";
                                getline(cin, id);
                                manager.removeClothesByID(id);
                                system("pause");
                            }
                            break;
                        case 3:
                            exitSubMenu = true;  
                            break;
                    }
                }
                break;  
            }
            case 3: {
                manager.writeClothesToFile("CLOTHES.txt");
                cout << "<!> Da luu danh sach quan ao vao file." << endl;
                system("pause");
                break;
            }
            case 4: {
                orderManager.createOrder(manager);
                break;
            }
            case 5: {
                orderManager.generateStatistics();
                system("pause");
                break;
            }
            case 6: {
                return;
            }
        }
    }
}