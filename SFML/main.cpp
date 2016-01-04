#include <iostream>
#include "InfoMenu.h"

void getInfos()
{
    InfoMenu *menu = InfoMenu::getInstance();

    menu->init();
    menu->showIpForm();
    std::cout << "IP : " << menu->getIP() << std::endl;
    std::cout << "PORT : " << menu->getPort() << std::endl;
    menu->getNext();
    while (!MainMenu::getInstance()->exit());
}

int main()
{
    getInfos();
    return 0;
}