#include "menu.h"
#include "login.h"
#include "ClothesManager.h"
int main() {
    ClothesManager manager;
    OrderManager orderManager;
    Admin_Manage Managerr;
    Managerr.ReadFileCustomer("Customerr.txt");
    Managerr.ReadFileAdmin("Admin.txt");
    if(login(Managerr) == 1){
    chooseMenu(Managerr, manager, orderManager);
    }
    return 0;
}