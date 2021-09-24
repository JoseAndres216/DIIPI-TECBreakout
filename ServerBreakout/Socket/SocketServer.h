//
// Created by keyner on 9/12/21.
//

#ifndef SERVERBREAKOUT_SOCKETSERVER_H
#define SERVERBREAKOUT_SOCKETSERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include <mutex>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include "JsonManagement.h"


using namespace std;
static int client_fd;

struct Client {
    int clientFd;
    sockaddr_in clientAddr;
};

/**
 * This class is the creator of the socket and is in charge for manage the communication with the client.
 */
class SocketServer {

protected:

    /**
     * @brief Class constructor.
     */
    SocketServer();

    /**
     * @brief Class destructor.
     */
    ~SocketServer();

private:

    int socketFd;
    sockaddr_in addr;
    static mutex mutex_;
    static SocketServer *unique_instance;

public:

    void InitServer(int port);

    static SocketServer *getInstance();

    static void sendMessage(const char *msg);

    static void *clientController(void *);



};

#endif //SERVERBREAKOUT_SOCKETSERVER_H