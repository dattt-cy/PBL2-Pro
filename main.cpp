#include "menu.h"
#include "login.h"
#include "ClothesManager.h"
int main() {
    ClothesManager manager;
    manager.readClothesFromFile("CLOTHES.txt");
    OrderManager orderManager;
    Admin_Manage KHvaAD;
    chooseLogin(KHvaAD, manager, orderManager);
    return 0;
}