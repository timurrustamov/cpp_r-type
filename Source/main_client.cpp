#include					<iostream>
#include                    "GameEngine/LinuxSocket.h"
#include					"System/window.h"
#include					"GameEngine/OnLevel.h"
#include                    "GameEngine/ISocket.h"

#include					"System/Animation.h"
#include					"System/ResourcesBank.h"

static ISocket *                     getClient(int port, const std::string &ip, const std::string &proto)
{
    static std::map<std::string, ISocket *> map;

    if (map.find(proto) != map.end())
        return (map[proto]);
    map[proto] = LinuxSocket::getClient(ip, port, proto);
    return (map[proto]);
}

void                        sendUdp(World *world)
{
    static bool ok = false;

    if (!ok) {
        ISocket *udp = getClient(4242, "127.0.0.1", "TCP");
        Instruction i(Instruction::GETALLROOMNAMES);
        udp->writePacket(Packet::pack(i));
        ok = true;
    }
    return;
}

void                        udpGameHandler(ISocket *server)
{
    std::cout << "popopo" << std::endl;
    World *world = GameData::getInstance()->world;

    if (world == NULL)
        return;
    Packet *packet;
    Snapshot *snap;

    //get packet
    while ((packet = server->readPacket()) != NULL) {

        if (packet->getType() == Packet::Snap)
        {
            if ((snap = packet->unpack<Snapshot>()) != NULL) {

                world->loadSnapshot(snap);
                delete snap;
            }
        }
        delete packet;
    }
}

int							main()
{
    Window					window("R-Type");
    OnLevel					gameplay;
    Level					level("../Data/level1.xml");

    ISocket *tcpClient = getClient(4444, "127.0.0.1", "TCP");

    tcpClient->attachOnReceive(udpGameHandler);

    if (tcpClient->start() == -1)
        std::cout << "Failed to start servers!" << std::endl;
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