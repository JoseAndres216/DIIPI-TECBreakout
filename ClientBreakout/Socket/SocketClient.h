//
// Created by keyner on 9/13/21.
//

#ifndef CLIENTBREAKOUT_SOCKETCLIENT_H
#define CLIENTBREAKOUT_SOCKETCLIENT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

class SocketClient {

public:

    SocketClient();

    void connect(int port, string ip);

    void setMessage(const char *msg);

private:

    int descriptor;
    sockaddr_in info;

    static void* controller(void *obj);

};

#endif //CLIENTBREAKOUT_SOCKETCLIENT_H
