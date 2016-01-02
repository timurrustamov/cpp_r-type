#include "GameEngine/RTypeServer.hpp"

void                        sendUdp(World *world)
{
    return;
}

int             main(int ac, char **av)
{
    RTypeServer *server = RTypeServer::getInstance();

    std::cout << ISocket::getServer()->getIp() << " " << ISocket::getServer()->getPort() << std::endl;
    std::string s = "";
    while (s != "quit") {

        std::getline(std::cin, s);
    }
    delete server;
    return (0);
}