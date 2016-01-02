#include					<iostream>
#include					"System/window.h"
#include					"GameEngine/OnLevel.h"
#include 					"GameEngine/ISocket.h"

#include					"System/Animation.h"
#include					"System/ResourcesBank.h"

void                        sendUdp(World *world)
{
	std::cout << "send udp" << std::endl;
	ISocket *udpServer 		= ISocket::getServer(4242, "TCP");

	Snapshot *s = world->getSnapshot();

	udpServer->writePacket(Packet::pack(*s));
}

void                        updGameHandler(ISocket *server)
{
//	World *world = GameData::getInstance()->world;
//
//	Packet *packet;
//	Snapshot *snap;
//
//	//get packet
//	while ((packet = server->readPacket()) != NULL) {
//
//		if (packet->getType() == Packet::Snap)
//		{
//			if ((snap = packet->unpack<Snapshot>()) != NULL) {
//
//				world->loadSnapshot(snap);
//				delete snap;
//			}
//		}
//		delete packet;
//	}
}

int							main()
{
	Window					window("R-Type");
	OnLevel					gameplay;
	Level					level("../Data/level1.xml");
	ISocket					*tcpServer = ISocket::getServer(4242, "TCP");
	ISocket 				*udpServer = ISocket::getServer(4243, "UDP");

	if (tcpServer->start() == -1 ||
		udpServer->start() == -1)
		std::cout << "Failed to start servers!" << std::endl;
	try
	{
		srand(time(NULL));
		gameplay.loadLevel(&level);
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