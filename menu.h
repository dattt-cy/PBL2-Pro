#ifndef MENU_H
#define MENU_H

#include "ClothesManager.h"
#include "OrderManager.h" 
#include "Admin_Manage.h"

void drawInterface(string menuItems[], int numItems, int selectedItem);
int interactiveMenu();
void menu(ClothesManager& manager, OrderManager& orderManager);
void chooseMenu(Admin_Manage& Manager, ClothesManager& manager, OrderManager& orderManager);
void chooseMenuPerson(Admin_Manage& Manager);

#endif