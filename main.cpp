#include <iostream>

#include "View\TextUI.h"

int main()
{
    TextUI ui;
    ui.displayMenu();
    ui.processCommand();
    return 0;
}