#include <windows.h>
#include "Set.h"

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
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
