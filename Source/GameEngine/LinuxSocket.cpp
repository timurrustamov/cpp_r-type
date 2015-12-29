//
// Created by rustam_t on 10/19/15.
//

#include "LinuxSocket.h"

const std::string &
LinuxSocket::getMachineIp()
{
    static std::string ip;

    if (ip.size() == 0) {

        char buffer[128];
        FILE *pipe = popen("hostname -i", "r");

        if (pipe) {
            if (fgets(buffer, 128, pipe) != NULL)
                ip += buffer;
            pclose(pipe);
            //erase whitespace and \n
            ip.erase(std::remove(ip.begin(), ip.end(), '\n'), ip.end());
            ip.erase(std::remove(ip.begin(), ip.end(), ' '), ip.end());
        }
    }

    return (const_cast<const std::string &>(ip));
}

LinuxSocket::~LinuxSocket()
{
    if (this->_status == ISocket::Running)
        this->cancel();
    if (this->_type == ISocket::Server)
    {
        for (std::vector<ISocket *>::iterator it = this->_targets.begin(); it != this->_targets.end(); it++)
            delete (*it);
    }
    usleep(100);
}

void
LinuxSocket::cancel()
{
    IMutex *mutex = (*MutexVault::getMutexVault())["close" + MutexVault::toString(this->_id)];

    if (this->_type == ISocket::Server) {

        std::vector<ISocket *> activeClients = this->getActiveClients();
        std::cout << "disconnecting " << activeClients.size() << " clients" << std::endl;
        for (unsigned int i = 0; i < activeClients.size(); i++)
            activeClients[i]->cancel();
    }
    mutex->lock(true);
    if (this->_socketOpened)
    {
        shutdown(this->_socket, 0);
        close(this->_socket);
        this->_socketOpened = false;
    }
    mutex->unlock();
    this->_status = ISocket::Canceled;
}

void
LinuxSocket::acceptNewClients(unsigned int __attribute__((__unused__)) thread_id, LinuxSocket *server)
{
    struct sockaddr_in    s_in;
    socklen_t clinen = sizeof(s_in);
    LinuxSocket *newclient;

    server->_status = ISocket::Running;
    while (server->_status == ISocket::Running)
    {
        newclient = new LinuxSocket(ISocket::Client);
        if ((newclient->_socket = accept(server->_socket, reinterpret_cast<struct sockaddr *>(&s_in), &clinen)) < 0)
            server->_status = ISocket::Canceled;
        else {

            newclient->_socketOpened = true;
            newclient->_status = ISocket::Ready;
            newclient->_port = s_in.sin_port;
            newclient->_ip = inet_ntoa(s_in.sin_addr);
            server->addNewClient(newclient);
            newclient->_thread = new LinuxThread<void, LinuxSocket *>(LinuxSocket::launchClient);
            (*newclient->_thread)(newclient);
        }
    }
}

void
LinuxSocket::launchClient(unsigned int __attribute__((__unused__)) thread_id, LinuxSocket *client)
{
    struct pollfd ufd[2];
    unsigned char buffer[READ_HEAP];
    int rv;
    ssize_t send_val;
    ssize_t read_val;
    ISocket::EventHandler handler[3];

    MutexVault *vault = MutexVault::getMutexVault();
    client->_status = ISocket::Running;

    ufd[0].fd = (ufd[1].fd = client->_socket);
    ufd[0].events = POLLIN;
    ufd[1].events = POLLOUT;

    IMutex *read = (*MutexVault::getMutexVault())["read" + MutexVault::toString(client->getId())];
    IMutex *write = (*MutexVault::getMutexVault())["write" + MutexVault::toString(client->getId())];

    //if onConnect is attached
    if ((handler[0] = client->getOnConnect()) != NULL)
        handler[0](client);

    while (client->getStatus() != ISocket::Canceled)
    {
        if ((rv = poll(&ufd[0], 1, TIMEOUT)) == -1)
            client->_status = ISocket::Canceled;
        read->lock(true);
        if (rv > 0)
        {
            //begin protected action
            if (client->_read_buffer.size() > MAX_BUFFER_SIZE)
                client->_read_buffer.clear();
            if ((read_val = recv(client->_socket, &buffer[0], READ_HEAP, 0)) == -1)
                client->_status = ISocket::Canceled;
            else if (read_val == 0)
                client->_status = ISocket::Canceled;
            else {
                for (unsigned int i = 0; i < read_val; i++)
                    client->_read_buffer.push_back(buffer[i]);
            }
            //end protected action
        }
        //while protected -> summon onReceive
        if (client->_read_buffer.size() > 0 && (handler[1] = client->getOnReceive()) != NULL)
            handler[1](client);
        read->unlock();


        if ((rv = poll(&ufd[1], 1, TIMEOUT)) == -1)
            client->_status = ISocket::Canceled;
        if (rv > 0)
        {
            //begin protected action
            write->lock(true);
            if (client->_write_buffer.size() > 0) {

                if ((send_val = send(client->_socket, &(client->_write_buffer[0]), client->_write_buffer.size(), 0)) == -1)
                    client->_status = ISocket::Canceled;
                else if (send_val > 0)
                    client->_write_buffer.erase(client->_write_buffer.begin(), client->_write_buffer.begin() + send_val);
            }
            write->unlock();
            //end protected action
        }
        //no event
    }
    client->cancel();
    if ((handler[2] = client->getOnDisconnect()) != NULL)
        handler[2](client);
}

LinuxSocket *
LinuxSocket::getThisClient(struct sockaddr_in &clientinfo)
{
    ISocket *udpClient;
    LinuxSocket *newclient;

    std::string ip = inet_ntoa(clientinfo.sin_addr);
    int port = static_cast<int>(ntohs(clientinfo.sin_port));

    if (this->_proto == "UDP" && ISocket::getServer(this->_port, "TCP")->hasThisIp(ip))
    {
        if ((udpClient = this->hasThisIp(ip)) == NULL)
        {
            newclient = new LinuxSocket(ISocket::Client);
            newclient->_port = port;
            newclient->_ip = ip;
            newclient->_onReceive = this->_onReceive;
            newclient->_status = ISocket::Running;
            newclient->_socketOpened = false;
            this->_targets.push_back(newclient);
            return (newclient);
        }
        return (dynamic_cast<LinuxSocket *>(udpClient));
    }
    return (NULL);
}

void
LinuxSocket::sendUdpBuffer(int socket)
{
    ssize_t send_val;
    struct sockaddr_in clientinfo;
    ISocket *serverTcp = ISocket::getServer(this->_port, "TCP");

    if (this->_write_buffer.size() > 0)
    {
        clientinfo.sin_family = AF_INET;
        clientinfo.sin_port = htons(this->_port);
        clientinfo.sin_addr.s_addr = inet_addr(this->_ip.c_str());
        if ((send_val = sendto(socket, &this->_write_buffer[0], this->_write_buffer.size(), 0, reinterpret_cast<const sockaddr *>(&clientinfo), sizeof(clientinfo))) == -1)
            this->cancel();
        else if (send_val > 0 && this->_write_buffer.size() >= send_val)
            this->_write_buffer.erase(this->_write_buffer.begin(), this->_write_buffer.begin() + send_val);
        else
            this->_write_buffer.clear();
    }
}

void
LinuxSocket::listenUdpClient(unsigned int thread_id, LinuxSocket *server)
{
    struct pollfd ufd[2];
    unsigned char buffer[READ_HEAP];
    struct sockaddr_in clientinfo;
    socklen_t socklen;
    int rv;
    ssize_t send_val;
    ssize_t read_val;
    ISocket::EventHandler handler[3];

    clientinfo.sin_family = AF_INET;
    clientinfo.sin_port = htons(server->_port);
    clientinfo.sin_addr.s_addr = inet_addr(server->_ip.c_str());

    MutexVault *vault = MutexVault::getMutexVault();
    server->_status = ISocket::Running;

    ufd[0].fd = (ufd[1].fd = server->_socket);
    ufd[0].events = POLLIN;
    ufd[1].events = POLLOUT;

    IMutex *read = (*MutexVault::getMutexVault())["read" + MutexVault::toString(server->getId())];
    IMutex *write = (*MutexVault::getMutexVault())["write" + MutexVault::toString(server->getId())];

    while (server->getStatus() != ISocket::Canceled)
    {
        if ((rv = poll(&ufd[0], 1, TIMEOUT)) == -1)
            server->_status = ISocket::Canceled;
        read->lock(true);
        if (rv > 0)
        {
            //begin protected action
            if (server->_read_buffer.size() > MAX_BUFFER_SIZE)
                server->_read_buffer.clear();
            if ((read_val = recvfrom(server->_socket, &buffer[0], READ_HEAP - 1, 0, reinterpret_cast<sockaddr *>(&clientinfo), &socklen)) == -1)
                server->_status = ISocket::Canceled;
            else if (read_val == 0)
                server->_status = ISocket::Canceled;
            else
                for (unsigned int i = 0; i < read_val; i++)
                    server->_read_buffer.push_back(buffer[i]);
            if (server->_read_buffer.size() > 0 && (handler[1] = server->getOnReceive()) != NULL)
                handler[1](server);
            //end protected action
        }
        //while protected -> summon onReceive

        read->unlock();

        if ((rv = poll(&ufd[1], 1, TIMEOUT)) == -1)
            server->_status = ISocket::Canceled;
        if (rv > 0)
        {
            //begin protected action
            write->lock(true);
            if (server->_write_buffer.size() > 0) {

                if ((send_val = sendto(server->_socket, &server->_write_buffer[0], server->_write_buffer.size(), 0, reinterpret_cast<const sockaddr *>(&clientinfo), sizeof(clientinfo))) == -1)
                    server->_status = ISocket::Canceled;
                else if (send_val > 0) {
                    server->_write_buffer.erase(server->_write_buffer.begin(),
                                                server->_write_buffer.begin() + send_val);
                }
            }
            write->unlock();
            //end protected action
        }
        //no event
    }
    server->cancel();
}

void
LinuxSocket::listenUdp(unsigned int __attribute__((__unused__)) thread_id, LinuxSocket *server)
{
    struct pollfd ufd[2];
    unsigned char buffer[READ_HEAP];
    LinuxSocket *client;
    struct sockaddr_in clientinfo;
    socklen_t socklen = sizeof(clientinfo);
    std::vector<ISocket *> activeClients;
    int rv;
    ssize_t send_val;
    ssize_t read_val;
    ISocket::EventHandler handler[3];

    MutexVault *vault = MutexVault::getMutexVault();
    server->_status = ISocket::Running;

    ufd[0].fd = (ufd[1].fd = server->_socket);
    ufd[0].events = POLLIN;
    ufd[1].events = POLLOUT;

    IMutex *read = (*MutexVault::getMutexVault())["read" + MutexVault::toString(server->getId())];
    IMutex *write = (*MutexVault::getMutexVault())["write" + MutexVault::toString(server->getId())];

    while (server->getStatus() != ISocket::Canceled)
    {
        if ((rv = poll(&ufd[0], 1, TIMEOUT)) == -1)
            server->_status = ISocket::Canceled;
        read->lock(true);
        if (rv > 0)
        {
            //begin protected action
            if (server->_read_buffer.size() > MAX_BUFFER_SIZE)
                server->_read_buffer.clear();
            if ((read_val = recvfrom(server->_socket, &buffer[0], READ_HEAP - 1, 0, reinterpret_cast<sockaddr *>(&clientinfo), &socklen)) == -1)
                server->_status = ISocket::Canceled;
            else if (read_val == 0)
                server->_status = ISocket::Canceled;
            else {

                if (client = server->getThisClient(clientinfo)) {

                    for (unsigned int i = 0; i < read_val; i++)
                        client->_read_buffer.push_back(buffer[i]);
                    if (client->_read_buffer.size() > 0 && (handler[1] = client->getOnReceive()) != NULL)
                        handler[1](client);
                }
            }
            //end protected action
        }
        //while protected -> summon onReceive
        read->unlock();


        if ((rv = poll(&ufd[1], 1, TIMEOUT)) == -1)
            server->_status = ISocket::Canceled;
        if (rv > 0)
        {
            //begin protected action
            write->lock(true);

            activeClients = server->getActiveClients();
            for (std::vector<ISocket *>::iterator it = activeClients.begin(); it != activeClients.end(); it++) {

                if ((client = dynamic_cast<LinuxSocket *>(*it)) != NULL) {
                    client->_write_buffer.insert(client->_write_buffer.begin(), server->_write_buffer.begin(),
                                               server->_write_buffer.end());
                    client->sendUdpBuffer(server->_socket);
                }
                server->_write_buffer.clear();
            }
            write->unlock();
            //end protected action
        }
        //no event
    }
    server->cancel();
}

//dummy
LinuxSocket::LinuxSocket(LinuxSocket::Type type) : ISocket(type)
{
    this->_socketOpened = false;
}


//Server
LinuxSocket::LinuxSocket(int port, const std::string &proto) : ISocket(ISocket::Server, LinuxSocket::getMachineIp(), port)
{
    struct protoent       *pe;
    struct sockaddr_in    s_in;

    if ((this->_proto = proto) != "TCP" && this->_proto != "UDP")
        throw BBException("Unknown proto!");
    if (this->_ip.empty())
        throw BBException("No ip detected!");
    this->_status = ISocket::Waiting;
    if ((pe = getprotobyname(proto.c_str())) == NULL)
        throw BBException("getprotobyname failed");
    if (this->_proto == "TCP" && (this->_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
        throw BBException("socket failed");
    else if (this->_proto == "UDP" && (this->_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        throw BBException("socket failed");
    int enable = 1;
    if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0)
        throw BBException("socket failed");
    this->_status = ISocket::Ready;
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(static_cast<uint16_t>(port));
    s_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(this->_socket, reinterpret_cast<struct sockaddr *>(&s_in), sizeof(s_in)) == -1)
        throw BBException("bind failed");
    if (this->_proto == "TCP" && listen(this->_socket, MAX_CLIENTS) == -1)
        throw BBException("listen failed");
    this->_socketOpened = true;
}

int
LinuxSocket::start()
{
    if (this->_status != ISocket::Ready)
        return (0);
    if (this->_type == ISocket::Server) {
        //launch the thread to accept new connections
        if (this->_proto == "TCP") {
            this->_thread = new LinuxThread<void, LinuxSocket *>(LinuxSocket::acceptNewClients);
            (*this->_thread)(this);
        }
        else {

            this->_thread = new LinuxThread<void, LinuxSocket *>(LinuxSocket::listenUdp);
            (*this->_thread)(this);
        }
    }
    else
    {
        struct sockaddr_in    s_in;

        s_in.sin_family = AF_INET;
        s_in.sin_port = htons(static_cast<uint16_t>(this->_port));
        if ((s_in.sin_addr.s_addr = inet_addr(this->_ip.c_str())) == INADDR_NONE ||
            (connect(this->_socket, reinterpret_cast<struct sockaddr *>(&s_in), sizeof(s_in))) == -1) {

            this->cancel();
            return (-1);
        }
        if (this->_proto == "TCP")
            this->_thread = new LinuxThread<void, LinuxSocket *>(LinuxSocket::launchClient);
        else
            this->_thread = new LinuxThread<void, LinuxSocket *>(LinuxSocket::listenUdpClient);
        (*this->_thread)(this);
    }
    return (1);
}

//Client
LinuxSocket::LinuxSocket(const std::string &ip, int port, const std::string &proto) : ISocket(ISocket::Client, ip, port)
{
    struct protoent       *pe;

    if (proto != "TCP" && proto != "UDP")
        throw BBException("Unknown proto!");
    if (proto == "TCP") {
        if ((pe = getprotobyname(proto.c_str())) == NULL)
            throw BBException("getprotobyname failed");
        if ((this->_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
            throw BBException("socket failed");
    }
    else {
        if ((this->_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
            throw BBException("socket failed");
    }
    this->_proto = proto;
    this->_port = port;
    this->_ip = ip;
    this->_socketOpened = true;
    this->_status = ISocket::Ready;
}