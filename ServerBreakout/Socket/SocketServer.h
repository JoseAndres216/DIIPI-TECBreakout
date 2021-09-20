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

using namespace std;

struct socketData {
    int descriptor;
    sockaddr_in info;
};

class SocketServer {

protected:

    SocketServer();

    ~SocketServer();

public:

    void InitServer(int port);

    static SocketServer *getInstance();

    void sendMessage(const char *msg);

    static void *clientController(void *);

private:

    int descriptor;
    sockaddr_in info;
    vector<int> clients;
    static mutex mutex_;
    static SocketServer *unique_instance;

};

#endif //SERVERBREAKOUT_SOCKETSERVER_H