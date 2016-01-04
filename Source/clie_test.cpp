#if defined(_WIN32) && !defined(WIN32)
# define _WINSOCKAPI_
# define NOGDI
# include <windows.h>
# include "System/WinSocket.h"
# define WIN32
#else
# include "GameEngine/LinuxSocket.h"
#endif
#include					"System/window.h"
#include					"GameEngine/OnLevel.h"
#include                    "GameEngine/ISocket.h"
#include					"GameEngine/BBException.hpp"

#include					"System/Animation.h"
#include					"System/ResourcesBank.h"

#include					<algorithm>

#pragma comment(lib, "Ws2_32.lib")


void            recvHandler(ISocket *client)
{
    Packet *packet;
    Instruction *instruct;
    Snapshot *snap;

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
        else if (packet->getType() == Packet::Snap && (snap = packet->unpack<Snapshot>()) != NULL)
        {
            GameData::getInstance()->world->loadSnapshot(snap);
            delete snap;
        }
        delete packet;
    }
}

ISocket *                        getClient()
{
    static ISocket *servTcp = NULL;

    if (servTcp == NULL) {
        servTcp = ISocket::getClient("10.45.20.250", 4444, "tcp");
        servTcp->attachOnReceive(recvHandler);
        if ((servTcp->start()) == -1)
            std::cout << "TCP failed" << std::endl;
    }
    return (servTcp);
}

void                            gameUpdateHandler(OnLevel &level)
{
    std::vector<int> vec;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        vec.push_back(static_cast<int>(sf::Keyboard::Left));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        vec.push_back(static_cast<int>(sf::Keyboard::Right));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        vec.push_back(static_cast<int>(sf::Keyboard::Up));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        vec.push_back(static_cast<int>(sf::Keyboard::Down));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        vec.push_back(static_cast<int>(sf::Keyboard::B));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        vec.push_back(static_cast<int>(sf::Keyboard::C));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        vec.push_back(static_cast<int>(sf::Keyboard::Space));

    getClient()->writePacket(Packet::pack(vec));
}

int            game()
{
    Window					window("R-Type CLIENT");
    OnLevel					gameplay(gameUpdateHandler);
    Level					level("../Data/level1.xml");

    try
    {
        srand(time(NULL));
        gameplay.loadLevel(&level);
        gameplay.timer.removeEvent("mobSpawn");
        gameplay.timer.removeEvent("meteoraSpawn");
        window.attachGameplay(dynamic_cast<IGameplay *>(&gameplay));

        window.launchWindow();
        while (window.isOpen())
        {
            window.callGameplay();
            window.draw(gameplay);
        }
    }
    catch (const RTypeException &err)
    {
        std::cerr << "RType Exception: " << err.what() << std::endl;
        system("pause");
        return (1);
    }
    catch (const std::exception &err)
    {
        std::cerr << "std::exception: " << err.what() << std::endl;
        system("pause");
        return (1);
    }
    return (0);
}

int             main(int ac, char **av)
{
	std::string s;
	std::string token;
	size_t pos;
	Instruction instruct(Instruction::KO);
	ISocket *servTcp = getClient();

	/*
	try
	{
		servTcp->attachOnReceive(&recvHandler);
		instruct.setInstruct(Instruction::CONNEXION);
		instruct.addName("fabY");
		servTcp->writePacket(Packet::pack(instruct));
		#ifdef _WIN_32
			Sleep(100);
		#else
			usleep(10000);
		#endif

		instruct.setInstruct(Instruction::CREATE_ROOM);
		servTcp->writePacket(Packet::pack(instruct));
		#ifdef _WIN_32
			Sleep(100);
		#else
			usleep(10000);
		#endif

		instruct.setInstruct(Instruction::START_GAME);
		servTcp->writePacket(Packet::pack(instruct));
		#ifdef _WIN_32
			Sleep(100);
		#else
			usleep(10000);
		#endif

		game();
	}
	catch (BBException &err)
	{
		std::cerr << err.what() << std::endl;
		system("pause");
	}
	*/

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
        else if (s == "start")
        {
            instruct.setInstruct(Instruction::START_GAME);
            servTcp->writePacket(Packet::pack(instruct));
            game();
            break;
        }
        //servUdp->writePacket(Packet::pack<std::string>(s));
    }
    servTcp->cancel();
	#ifdef _WIN_32
		Sleep(1000);
	#else
		sleep(1);
	#endif
    
    delete servTcp;
    return (0);
}