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
#include "support.h"
#include "Set.h"

using namespace std;


void drawInterface(string menuItems[], int numItems, int selectedItem) {
    system("cls");

    int boxWidth = 54;
    int boxHeight = numItems + 5;
    int boxX = 34;
    int boxY = 0;
    setTextColor(11);
    drawBox(boxX, boxY, boxWidth, boxHeight);

    // Tiêu đề shop ở giữa khung lớn
    int titlePos = boxX + 4;
    gotoXY(titlePos, 1);
    setTextColor(14);  // Màu vàng cho tiêu đề
    cout << "=============^^SHOP QUAN AO GAU GAU^^=============";

    

    // Hiển thị các mục menu bên trong hộp nhỏ
    int menuPos = boxX +1;
    for (int i = 0; i < numItems; ++i) {
        gotoXY(menuPos, 2 + i);
        if (i == selectedItem) {
            setTextColor(11);  // Màu xanh dương cho mục được chọn
            cout << ">> " << menuItems[i];
        } else {
            setTextColor(15);  // Màu trắng cho các mục khác
            cout << "   " << menuItems[i];
        }
    }

    setTextColor(7);  // Đặt lại màu mặc định
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
        "2.7 TIM KIEM QUAN AO THEO ID",
        "2.8 THOAT"  
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
void Statistics(OrderManager& orderManager) {
    string menuItems[] = {
        "1. THONG KE NGAY HOM NAY",
        "2. THONG KE THEO NGAY",
        "3. THONG KE THEO THANG",
        "4. THONG KE THEO NAM",
        "5. TRO VE MENU CHINH"
    };
    int numItems = sizeof(menuItems) / sizeof(menuItems[0]);
    int choice;
    orderManager.clearOrders();
    do {
        choice = interactiveMenu(menuItems, numItems);
      
        switch (choice) {
            case 0: {
                system("cls");
                orderManager.readOrdersFromFile("Doanhthu.txt");
                time_t now = time(0);
                tm* ltm = localtime(&now);
                int day = ltm->tm_mday;
                int month = ltm->tm_mon + 1;
                int year = ltm->tm_year + 1900;
                orderManager.generateStatistics(day, month, year, "day");
                orderManager.clearOrders();
                system("pause");
                break;
            }
            case 1: {
                system("cls");
                string dateStr;
                int day, month, year;
                orderManager.readOrdersFromFile("Doanhthu.txt");
                cout << "Nhap ngay (dd/mm/yyyy): ";
                getline(cin, dateStr);
                if (parseDate(dateStr, day, month, year)) {
                    orderManager.generateStatistics(day, month, year, "day");
                } else {
                    cout << "<!> Ngay khong hop le!" << endl;
                }
                orderManager.clearOrders();
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                string dateStr;
                int day = 1, month, year;
                orderManager.readOrdersFromFile("Doanhthu.txt");
                cout << "Nhap thang va nam (mm/yyyy): ";
                getline(cin, dateStr);
                if (parseDate("01/" + dateStr, day, month, year)) { 
                    orderManager.generateStatistics(0, month, year, "month");
                } else {
                    cout << "<!> Thang hoac nam khong hop le!" << endl;
                }
                orderManager.clearOrders();
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                string dateStr;
                orderManager.readOrdersFromFile("Doanhthu.txt");
                int day = 1, month = 1, year;
                cout << "Nhap nam (yyyy): ";
                getline(cin, dateStr);
                if (parseDate("01/01/" + dateStr, day, month, year)) { 
                    orderManager.generateStatistics(0, 0, year, "year");
                } else {
                    cout << "<!> Nam khong hop le!" << endl;
                }
                orderManager.clearOrders();
                system("pause");
                break;
            }
            case 4: {
                break;
            }
            default: {
                cout << "<!> Lua chon khong hop le!" << endl;
                system("pause");
                break;
            }
        }
    } while (choice != 4); 
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
            "7. XEM HOA DON KHACH HANG",
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
                    string name, brand, type, color, size, ID;
                    switch (subChoice) {
                        case 0:
                            system("cls");
                            cout << "[!] LUU Y CO THE VIET THUONG HOAC VIET HOA THONG TIN CAN TIM." << endl;
                            cout << "<!> Nhap mot phan hoac toan bo ten san pham can tim: ";
                            getline(cin, name);
                            name = nameStr(name);
                            manager.SearchBySubstring(name, "", "", "", "4");
                            break;
                        case 1:
                            system("cls");
                            cout << "[!] LUU Y CO THE VIET THUONG HOAC VIET HOA THONG TIN CAN TIM." << endl;
                            cout << "<!> Nhap mot phan hoac toan bo ten thuong hieu can tim: ";
                            getline(cin, brand);
                            brand = nameStr(brand);
                            manager.SearchBySubstring("", brand, "", "", "4");
                            break;
                        case 2:
                            system("cls");
                            cout << "[!] LUU Y CO THE VIET THUONG HOAC VIET HOA THONG TIN CAN TIM." << endl;
                            cout << "<!> Nhap the loai (1: Male, 2: Female, 3: Children): ";
                            getline(cin, type);
                            type = nameStr(type);
                            manager.SearchBySubstring("", "", "", "", type);
                            break;
                        case 3:
                            system("cls");
                            cout << "[!] LUU Y CO THE VIET THUONG HOAC VIET HOA THONG TIN CAN TIM." << endl;
                            cout << "<!> Nhap mot phan hoac toan bo mau sac can tim: ";
                            getline(cin, color);
                            color = nameStr(color);
                            manager.SearchBySubstring("", "", color, "", "4");
                            break;
                        case 4:
                            system("cls");
                            cout << "[!] LUU Y CO THE VIET THUONG HOAC VIET HOA THONG TIN CAN TIM." << endl;
                            cout << "<!> Nhap size can tim: ";
                            getline(cin, size);
                            size = nameStr(size);
                            manager.SearchBySubstring("", "", "", size, "4");
                            break;
                        case 5:
                            system("cls");
                            cout << "[!] LUU Y CO THE VIET THUONG HOAC VIET HOA THONG TIN CAN TIM. CO THE BO TRONG THONG TIN KHONG CAN TIM !" << endl;
                            cout << "[!] CO THE NHAP TOAN BO HOAC 1 PHAN THONG TIN DUOI DAY !!" << endl;
                            cout << "<!> Nhap ten quan ao muon tim: ";
                            getline(cin, name);
                            name = nameStr(name);
                            cout << "<!> Nhap ten thuong hieu muon tim: ";
                            getline(cin, brand);
                            brand = nameStr(brand);
                            cout << "<!> Nhap the loai (1: Male, 2: Female, 3: Children, 4: ALL): ";
                            getline(cin, type);
                            cout << "<!> Nhap mau sac muon tim: ";
                            getline(cin, color);
                            color = nameStr(color);
                            cout << "<!> Nhap size muon tim: ";
                            getline(cin, size);
                            size = nameStr(size);
                            manager.SearchBySubstring(name, brand, color, size, type);
                            break;
                        case 6:
                            system("cls");
                            cout << "<!> Nhap chinh xac ma ID quan ao can tim: ";
                            getline(cin, ID);
                            manager.PrintClothesByID(ID);
                            break;
                        case 7:
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
                            if(manager.addClothesManually()){
                                manager.Sort_ByID();
                                manager.printAllClothes();
                            }
                            break;
                          case 1: {
                            system("cls");
                            cout << "<!> LUU Y CO THE VIET THUONG HOAC VIET HOA ID CAN SUA." << endl;
                            cout << "<!> Nhap the loai quan ao can sua (1: Male, 2: Female, 3: Children, 4: All): ";
                            string type;
                            getline(cin, type);
                            if (type == "1" || type == "2" || type == "3" || type == "4") {
                                manager.printByType(type);
                                cout << "<!> Nhap ma ID quan ao can sua: ";
                                getline(cin, id);
                                id = nameStr(id);
                                manager.PrintClothesByID(id);
                                if(manager.EditClothesByID(id)){
                                    manager.printByType(type);
                                }
                            } else {
                                cout << "<!> Lua chon khong hop le !!" << endl;
                            }
                            break;
                        }
                        case 2:
                            system("cls");
                            cout << "<!> LUU Y CO THE VIET THUONG HOAC HOA ID CAN XOA." << endl;
                            cout << "<!> Nhap the loai quan ao can xoa (1: Male, 2: Female, 3: Children, 4: All): ";
                            getline(cin, type);
                            if (type == "1" || type == "2" || type == "3" || type == "4") {
                                manager.printByType(type);
                                cout << "<!> Nhap ma ID quan ao can xoa: ";
                                getline(cin, id);
                                id = nameStr(id);
                                if(manager.removeClothesByID(id)){
                                    cout << "<!> DA XOA QUAN AO THANH CONG." << endl;
                                    system("pause");
                                    manager.printByType(type);
                                } else {
                                    cout << "<!> KHONG TIM THAY AO QUAN VOI " << id << endl;
                                    cout << "<!> VUI LONG KIEM TRA LAI." << endl;
                                    system("pause");
                                }
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
                Statistics(orderManager);
                break;
            }
            case 6: {
                system("cls");
                string nameFile;
                string ID;
                cout << "---------------------------------------------------------" << endl;
                cout << "<!> Nhap ID cua khach hang can xem hoa don: ";
                getline(cin, ID);
                if(!orderManager.readInvoiceFromFile(ID)){
                    cout << "<!> KHONG TIM THAY HOA DON CUA KHACH HANG NAY!" << endl;
                }
                break;
                system("pause");
                cout << "---------------------------------------------------------" << endl;
            }
            case 7: {
                return;
        }
        }
    }
}
void menuForCustomer(ClothesManager& manager, OrderManager& orderManager) {
    manager.readClothesFromFile("CLOTHES.txt");
    manager.Sort_ByID();
    
    while (true) {
        string mainMenuItems[] = {
            "1. XEM QUAN AO",
            "2. TIM KIEM QUAN AO",
            "3. DAT HANG",
            "4. XEM HOA DON CUA BAN",
            "5. THOAT"
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
                            manager.printByType("4");
                            cout << "---------------------------------------------------------" << endl;
                            cout << "<!> Nhap ten san pham can tim: ";
                            getline(cin, name);
                            manager.SearchBySubstring(name, "", "", "", "All");
                            system("pause");
                            break;
                        case 1:
                            system("cls");
                            manager.printByType("4");
                            cout << "---------------------------------------------------------" << endl;
                            cout << "<!> Nhap thuong hieu can tim: ";
                            getline(cin, brand);
                            manager.SearchBySubstring("", brand, "", "", "All");
                            break;
                        case 2:
                            system("cls");
                             manager.printByType("4");
                            cout << "---------------------------------------------------------" << endl;
                            cout << "<!> Nhap the loai (1. Male/3. Female/3. Children/ 4. ALL): ";
                            getline(cin, type);
                            manager.SearchBySubstring("", "", "", "", type);
                            break;
                        case 3:
                            system("cls");
                            manager.printByType("4");
                            cout << "---------------------------------------------------------" << endl;
                            cout << "<!> Nhap mau sac can tim: ";
                            getline(cin, color);
                            manager.SearchBySubstring("", "", color, "", "All");
                            break;
                        case 4:
                            system("cls");
                            manager.printByType("4");
                            cout << "---------------------------------------------------------" << endl;
                            cout << "<!> Nhap size can tim: ";
                            getline(cin, size);
                            manager.SearchBySubstring("", "", "", size, "All");
                            break;
                        case 5:
                            system("cls");
                            manager.printByType("4");
                            cout << "---------------------------------------------------------" << endl;
                            cout << "<!> CO THE NHAP TOAN BO HOAC 1 PHAN THONG TIN DUOI DAY" << endl;
                            cout << "<!> Nhap ten quan ao muon tim: ";
                            getline(cin, name);
                            cout << "<!> Nhap ten thuong hieu muon tim: ";
                            getline(cin, brand);
                            cout << "<!> Nhap the loai (1. Male/2. Female/3. Children/ 4. All): ";
                            getline(cin, type);
                            cout << "<!> Nhap mau sac muon tim: ";
                            getline(cin, color);
                            cout << "<!> Nhap size muon tim: ";
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
                system("cls");
                orderManager.createOrder(manager);
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                string ID = Admin_Manage::id;
                if(!orderManager.readInvoiceFromFile(ID)){
                    cout << "<!> HIEN TAI BAN CHUA CO DON HANG NAO. HAY NHANH TAY DAT HANG NHE ^_^!" << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                setTextColor(7);
                system("cls");
                cout << "***------------------------------------------------------------***" << endl;
                cout << "        CHAO TAM BIET! HEN GAP LAI BAN VAO LAN SAU NHE ^-^" << endl;
                cout << "    !SHOP QUAN AO GAU GAU XIN CHAN THANH CAM ON BAN RAT NHIEU!     " << endl;
                system("pause");
                return;
            }
        }
    }
}
void chooseMenuPerson(Admin_Manage& Manager) {
    Manager.sortByID();
    cout << "^-^ CHAO MUNG BAN DEN VOI HE THONG QUAN LY CUA HANG GAU GAU ^-^" << endl;

    string mainMenuItems[] = {
        "1. XEM DANH SACH",
        "2. TIM KIEM THEO ID",
        "3. CHINH SUA THONG TIN",
        "4. THEM MOI",
        "5. XOA THEO ID",
        "6. THOAT"
    };
    int numMainItems = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);

    while (true) {
        int choice = interactiveMenu(mainMenuItems, numMainItems);

        switch (choice) {
            case 0: { // XEM DANH SACH
                string subMenuItems[] = {
                    "1.1 XEM DANH SACH ADMIN",
                    "1.2 XEM DANH SACH CUSTOMER",
                    "1.3 QUAY LAI MENU CHINH"
                };
                int numSubItems = sizeof(subMenuItems) / sizeof(subMenuItems[0]);
                while (true) {
                    int subChoice = interactiveMenu(subMenuItems, numSubItems);
                    if (subChoice == 0) {
                        system("cls");
                        Manager.ShowAdmin();
                        system("pause");
                    } else if (subChoice == 1) {
                        system("cls");
                        Manager.ShowCustomer();
                        system("pause");
                    } else if (subChoice == 2) {
                        break;
                    } else {
                        cout << "LUA CHON KHONG HOP LE!" << endl;
                        system("pause");
                    }
                }
                break;
            }

            case 1: { // TIM KIEM
                string subMenuItems[] = {
                    "2.1 TIM KIEM ADMIN THEO ID",
                    "2.2 TIM KIEM CUSTOMER THEO ID",
                    "2.3 QUAY LAI MENU CHINH"
                };
                int numSubItems = sizeof(subMenuItems) / sizeof(subMenuItems[0]);
                while (true) {
                    int subChoice = interactiveMenu(subMenuItems, numSubItems);
                    if (subChoice == 0 || subChoice == 1) {
                        string id;
                        cout << "NHAP ID BAN MUON TIM KIEM: ";
                        cin >> id;
                        Manager.findPerson(id);
                        system("pause");
                    } else if (subChoice == 2) {
                        break;
                    } else {
                        cout << "LUA CHON KHONG HOP LE!" << endl;
                        system("pause");
                    }
                }
                break;
            }

            case 2: { // CHINH SUA
                string subMenuItems[] = {
                    "3.1 CHINH SUA THONG TIN ADMIN",
                    "3.2 CHINH SUA THONG TIN CUSTOMER",
                    "3.3 QUAY LAI MENU CHINH"
                };
                int numSubItems = sizeof(subMenuItems) / sizeof(subMenuItems[0]);
                while (true) {
                    int subChoice = interactiveMenu(subMenuItems, numSubItems);
                    if (subChoice == 0 || subChoice == 1) {
                        string id;
                        if (subChoice == 0) Manager.ShowAdmin();
                        else Manager.ShowCustomer();
                        cout << "NHAP ID BAN MUON CHINH SUA: ";
                        cin >> id;
                        cin.ignore();
                        Manager.editPerson(id);
                        system("pause");
                    } else if (subChoice == 2) {
                        break;
                    } else {
                        cout << "LUA CHON KHONG HOP LE!" << endl;
                        system("pause");
                    }
                }
                break;
            }

            case 3: { // THEM MOI
                string subMenuItems[] = {
                    "4.1 THEM CUSTOMER MOI",
                    "4.2 QUAY LAI MENU CHINH"
                };
                int numSubItems = sizeof(subMenuItems) / sizeof(subMenuItems[0]);
                while (true) {
                    int subChoice = interactiveMenu(subMenuItems, numSubItems);
                    if (subChoice == 0) {
                        string type = "Customer";
                        Manager.inputPerson(type);
                        Manager.ShowCustomer();
                        system("pause");
                    } else if (subChoice == 1) {
                        break;
                    } else {
                        cout << "LUA CHON KHONG HOP LE!" << endl;
                        system("pause");
                    }
                }
                break;
            }

            case 4: { // XOA
                string subMenuItems[] = {
                    "5.1 XOA CUSTOMER THEO ID",
                    "5.2 QUAY LAI MENU CHINH"
                };
                int numSubItems = sizeof(subMenuItems) / sizeof(subMenuItems[0]);
                while (true) {
                    int subChoice = interactiveMenu(subMenuItems, numSubItems);
                    if (subChoice == 0) {
                        string id;
                        system("cls");
                        Manager.ShowCustomer();
                        cout << "NHAP ID BAN MUON XOA: ";
                        cin >> id;
                        Manager.DeletePerson(id);
                        system("pause");
                    } else if (subChoice == 1) {
                        break;
                    } else {
                        cout << "LUA CHON KHONG HOP LE!" << endl;
                        system("pause");
                    }
                }
                break;
            }

            case 5:
                system("cls");
                cout << "CHAO TAM BIET! HEN GAP LAI BAN VAO LAN SAU NHE ^-^" << endl;
                system("pause");
                return;

            default:
                cout << "LUA CHON KHONG HOP LE, VUI LONG NHAP LAI!" << endl;
                system("pause");
                break;
        }
    }
}
void chooseMenu(Admin_Manage& Manager, ClothesManager& manager, OrderManager& orderManager) {
    string menuItems[] = {
        "1. QUAN LI ADMIN VA KHACH HANG",
        "2. QUAN LI SHOP QUAN AO",
        "3. Thoat"
    };

    while (true) {
        int choice = interactiveMenu(menuItems, 3);
        switch (choice) {
            case 0:
                chooseMenuPerson(Manager);
                break;
            case 1:
                menu(manager, orderManager);
                break;
            case 2:  
                return;
            default:
                cout << "Lua chon khong hop le" << endl;
        }
        system("pause");
    }
}
void chooseLogin(Admin_Manage& KHvaAD, ClothesManager& manager, OrderManager& orderManager) {
    KHvaAD.ReadFile("Data.txt");

    string menuItems[] = {"1. DANG NHAP", "2. DANG KI", "3. THOAT"};
    int choice;

    while (true) {
        // Hiển thị menu động
        choice = interactiveMenu(menuItems, 3);

        if (choice == 0) {  // DANG NHAP
            int loginResult = login(KHvaAD);  
            if (loginResult == 1) {
                chooseMenu(KHvaAD, manager, orderManager);  
            } else if (loginResult == 2) {
                menuForCustomer(manager, orderManager); 
            }
        } else if (choice == 1) {  // DANG KI
            createAccount(KHvaAD);
        } else if (choice == 2) {  // THOAT
            break;
        }
    }
}