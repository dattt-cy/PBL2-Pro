#include "menu.h"
#include <iostream>
#define byte win_byte_override
#include <windows.h>
#undef byte
#include <cstddef>
#include <conio.h>
#include "Admin_Manage.h"
#include "Admin.h"
#include "Login.h"
#include "Set.h"

using namespace std;


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
                system("cls");
                orderManager.createOrder(manager);
                system("pause");
                break;
            }
            case 5: {
                system("cls");
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
void chooseMenuPerson(Admin_Manage& Manager) {
    Manager.sortByID();
    setTextColor(6);
    cout << "^-^ CHAO MUNG BAN DEN VOI HE THONG QUAN LY CUA HANG GAU GAU ^-^" << endl;
    setTextColor(15);
    while (true){
    cout << "ADMIN: " << endl;
    cout << "1. Xem danh sach Admin" << endl;
    cout << "2. Them Admin moi" << endl;
    cout << "3. Xoa Admin theo ID" << endl;
    cout << "4. Tim kiem Admin theo ID" << endl;
    cout << "==============================" << endl;
    cout << "CUSTOMER: " << endl;
    cout << "5. Xem danh sach Khach hang" << endl;
    cout << "6. Them Khach hang moi" << endl;
    cout << "7. Xoa Khach hang theo ID" << endl;
    cout << "8. Tim kiem Khach hang theo ID" << endl;
    cout << "9. Thoat" << endl;

    int choice;
    string filename, id, ngay, thang, nam;
    int a,b,c;
    Admin* newAdmin;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                Manager.ShowAdmin();
                system("pause");
                break;
            case 2:
                system("cls");
                Manager.inputAdmin();
                system("pause");
                break;
            
            case 3:
                system("cls");
                cout << "Nhap ID cua Admin ban muon xoa: ";
                cin >> id;
                Manager.DeleteAdmin(id);
                system("pause");
                break;
            
            case 4:
                system("cls");
                cout << "Nhap ID cua Admin ban muon tim kiem: ";
                cin >> id;
                Manager.searchByID(id);
                system("pause");
                break;
            case 5:
                system("cls");
                Manager.ShowCustomer();
                system("pause");
                break;
            case 6:
                system("cls");
                Manager.inputCustomer();
                system("pause");
                break;
            
            case 7:
                system("cls");
                cout << "Nhap ID cua Khach hang ban muon xoa: ";
                cin >> id;
                Manager.DeleteCustomer(id);
                system("pause");
                break;
            
            case 8:
                system("cls");
                cout << "Nhap ID cua Khach hang ban muon tim kiem: ";
                cin >> id;
                Manager.findCustomer(id);
                system("pause");
                break;
            case 9:
                setTextColor(5);
                cout << "Chao tam biet! Hen gap lai ban vao lan sau nhe ^-^" << endl;
                return;
            default:
                cout << "Moi ban nhap lua chon cua minh!!!" << endl;
        }
    }
    system("pause");

}

void chooseMenu(Admin_Manage& Manager, ClothesManager& manager, OrderManager& orderManager) {
    setTextColor(15);
    system("cls");
    cout <<" ^^^^^^ HAVE A NICE DAY ^^^^^^" << endl;
    cout << "1. Xem muc quan ly Admin va Khach hang. " << endl;
    cout << "2. Quan ly Shop quan ao. " << endl;
    cout << "========================================" << endl;
    cout << "Hay nhap lua chon cua ban: ";
    int choice;
    cin >> choice;
    switch (choice){
        case 1:
            chooseMenuPerson(Manager);
            break;
        case 2:
            menu(manager, orderManager);
            cout << "" << endl;
            break;
        default:
            cout << "Lua chon khong hop le" << endl;
    }
    system("pause");
}