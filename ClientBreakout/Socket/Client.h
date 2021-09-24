#ifndef CLIENTBREAKOUT_CLIENT_H
#define CLIENTBREAKOUT_CLIENT_H

#include <string>
#include <mutex>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

#include "JsonManagement.h"

using namespace std;

/**
 * @class Class for the connection to server
 */
class Client {

protected:
    Client();

    ~Client();

private:

    static Client *unique_instance;
    static mutex mutex_;
    string server_response;

public:

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    static Client *getInstance();

    int InitClient(int newPort, string ip);

    void Send(const char *msg);

    string getResponse();

    string setResponse(string newresponse);

    void operator=(const Client &) = delete;

    Client(Client &other) = delete;

};

#endif //CLIENTBREAKOUT_CLIENT_H
