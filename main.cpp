#include "menu.h"
#include "LinkedList.h"
#include "Clothes.h"

int main() {
    LinkedList<Clothes*> list;
    menu(list);
    return 0;
}
