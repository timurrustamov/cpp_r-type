#include <iostream>
#include "InfoMenu.h"

void getInfos()
{
    InfoMenu menu;

    menu.init();
    menu.showUserForm();
    if (menu.cutIP() == 0)
    {
        std::cout << "IP : " << menu.getIP() << std::endl;
        std::cout << "PORT : " << menu.getPort() << std::endl;
        menu.getNext();
        return;
    }
    else
        menu.showIpForm(1);
}

int main()
{
    getInfos();
    return 0;
}