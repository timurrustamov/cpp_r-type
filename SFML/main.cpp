#include <iostream>
#include "InfoMenu.h"

void getInfos()
{
    InfoMenu menu;
    int      i = 0;
    int      a = 0;

    menu.init();
    while (42)
    {
        if (i == 0)
        {
            menu.showIpForm(0);
            i = 1;
        }
        if (menu.cutIP() == 0 || i == 2)
        {
            i = 2;
            std::cout << "IP : " << menu.getIP() << std::endl;
            std::cout << "PORT : " << menu.getPort() << std::endl;
            if (a == 0)
                menu.showUserForm(0);
            if (menu.getUsername() == "nicolas")
            {
                std::cout << "lol" << std::endl;
                menu.getNext();
                return;
            }
            else
            {
                std::cout << "IN" << std::endl;
                menu.showUserForm(1);
                std::cout << "OUT" << std::endl;
                a = 1;
            }
        }
        else if (i == 1)
        {
            i = 1;
            menu.showIpForm(1);
        }
    }
}

int main()
{
    getInfos();
    return 0;
}