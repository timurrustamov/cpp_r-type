#include "GameEngine/LinuxSocket.h"
#include <algorithm>

void            recvHandler2(ISocket *client)
{
    Packet *p = client->readPacket();

    if (p != NULL)
        std::cout << *(p->unpack<std::string>()) << std::endl;
    //std::cout << "Received 2" << std::endl;
}

void            recvHandler(ISocket *client)
{
    Packet *packet;
    Instruction *instruct;

    while ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::Instruct &&
            (instruct = packet->unpack<Instruction>()) != NULL)
        {
            if (instruct->getInstruct() == Instruction::OK)
                std::cout << "OK" << std::endl;
            else if (instruct->getInstruct() == Instruction::KO)
                std::cout << "KO" << std::endl;
            else if (instruct->getInstruct() == Instruction::GETALLUSERNAMES)
            {
                std::cout << "usernames : " << std::endl;
                for (unsigned int i = 0; i < instruct->getNb(); i++)
                    std::cout << (*instruct)[i] << std::endl;
            }
            else if (instruct->getInstruct() == Instruction::GETALLROOMNAMES)
            {
                std::cout << "roomnames : " << std::endl;
                for (unsigned int i = 0; i < instruct->getNb(); i++)
                    std::cout << (*instruct)[i] << std::endl;
            }
            else if (instruct->getInstruct() == Instruction::LEAVE_ROOM)
            {
                std::cout << "ok pas de souci gros" << std::endl;
            }
            else if (instruct->getInstruct() == Instruction::GETALLUSERSINROOM)
            {
                std::cout << "users in room : " << std::endl;
                for (unsigned int i = 0; i < instruct->getNb(); i++)
                    std::cout << (*instruct)[i] << std::endl;
            }
            delete instruct;
        }
        delete packet;
    }
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
    std::string token;
    size_t pos;
    Instruction instruct(Instruction::KO);
    while (s != "quit") {

        instruct.eraseNames();
        std::getline(std::cin, s);

        if ((pos = s.find(" ")) != s.npos)
        {
            token = s.substr(0, pos);
            if (token == "connect")
                instruct.setInstruct(Instruction::CONNEXION);
            else if (token == "join")
                instruct.setInstruct(Instruction::JOIN_ROOM);
            else if (token == "create")
                instruct.setInstruct(Instruction::CREATE_ROOM);
            s.erase(0, pos + 1);
            if (s.size() > 0) {
                instruct.addName(s);
                servTcp->writePacket(Packet::pack(instruct));
            }
        }
        else if (s == "roomusers") {

            instruct.setInstruct(Instruction::GETALLUSERSINROOM);
            servTcp->writePacket(Packet::pack(instruct));
        }
        else if (s == "users")
        {
            instruct.setInstruct(Instruction::GETALLUSERNAMES);
            servTcp->writePacket(Packet::pack(instruct));
        }
        else if (s == "rooms")
        {
            instruct.setInstruct(Instruction::GETALLROOMNAMES);
            servTcp->writePacket(Packet::pack(instruct));
        }
        else if (s == "disconnect")
        {
            instruct.setInstruct(Instruction::DECONNEXION);
            servTcp->writePacket(Packet::pack(instruct));
        }
        else if (s == "leave")
        {
            instruct.setInstruct(Instruction::LEAVE_ROOM);
            servTcp->writePacket(Packet::pack(instruct));
        }
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