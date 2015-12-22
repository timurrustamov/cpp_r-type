#include "GameEngine/LinuxSocket.h"

void            recvHandler2(ISocket *client)
{
    Packet *p = client->readPacket();

    if (p != NULL)
        std::cout << *(p->unpack<std::string>()) << std::endl;
    //std::cout << "Received 2" << std::endl;
}

void            recvHandler(ISocket *client)
{
    std::cout << "Received" << std::endl;
}

int             main(int ac, char **av)
{
    ISocket *servTcp = ISocket::getClient("127.0.0.1", 4242, "TCP");
    ISocket *servUdp = ISocket::getClient("127.0.0.1", 4343, "UDP");

    servTcp->attachOnReceive(recvHandler);
    servUdp->attachOnReceive(recvHandler2);

    if ((servTcp->start()) == -1)
        std::cout << "TCP failed" << std::endl;
    if ((servUdp->start()) == -1)
        std::cout << "UDP failed" << std::endl;

    std::string s;
    while (s != "quit") {

        std::getline(std::cin, s);
        servTcp->writePacket(Packet::pack<std::string>(s));
        //servUdp->writePacket(Packet::pack<std::string>(s));
    }
    servTcp->cancel();
    sleep(1);
    servUdp->cancel();
    sleep(1);
    delete servTcp;
    delete servUdp;
    return (0);
}