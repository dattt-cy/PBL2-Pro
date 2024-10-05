#ifndef LOGIN_H
#define LOGIN_H

#include <string>
using namespace std;
void gotoXY(int x, int y);

void setTextColor(int color);

void drawBox(int x, int y, int width, int height);

void drawInterface();

bool isValidCharacter(char ch);

string getInput_admin(int x, int y, bool hide = false);

string getInput(int x, int y, bool hide = false);

int login();

#endif // LOGIN_H
