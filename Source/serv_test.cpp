#include "GameEngine/RTypeServer.hpp"

int             main(int ac, char **av)
{
    RTypeServer *server = RTypeServer::getInstance();

    std::string s = "";
    while (s != "quit") {

        std::getline(std::cin, s);
    }
    delete server;
    return (0);
}