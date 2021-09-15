//
// Created by keyner on 9/12/21.
//

#ifndef SERVERBREAKOUT_SOCKETSERVER_H
#define SERVERBREAKOUT_SOCKETSERVER_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
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

public:

    SocketServer();

    void run(int port);

    void setMessage(const char *msg);

private:

    int descriptor;
    sockaddr_in info;
    vector<int> clients;

    bool createSocket(int port);

    bool linkKernel();

    static void *clientController(void *obj);

};

#endif //SERVERBREAKOUT_SOCKETSERVER_H