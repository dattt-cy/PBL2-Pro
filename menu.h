#ifndef MENU_H
#define MENU_H

#include "ClothesManager.h"
#include "OrderManager.h" 
static void setTextColor(int color);
static void setTextColor(int color);
void drawInterface(string menuItems[], int numItems, int selectedItem);
int interactiveMenu();
void menu(ClothesManager& manager, OrderManager& orderManager);

#endif