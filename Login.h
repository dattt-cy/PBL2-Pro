#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include "LinkedList.h"
#include "Admin.h"
#include "Admin_Manage.h"
using namespace std;



void drawInterface();

bool isValidCharacter(char ch);

string getInput_admin(int x, int y, bool hide = false);

string getInput(int x, int y, bool hide = false);

int login(Admin_Manage& n);
int createAccount(Admin_Manage& n);


#endif // LOGIN_H