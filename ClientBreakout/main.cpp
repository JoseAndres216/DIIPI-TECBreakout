#include <iostream>
#include <SFML/Graphics.hpp>
#include "Views/MenuWindow.h"


void runGUI(){
    MenuWindow *window = new MenuWindow();
    window->start();
}

int main()
{
    runGUI();

    return 0;
}

