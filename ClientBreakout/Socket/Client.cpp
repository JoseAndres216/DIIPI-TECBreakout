//
// Created by keyner on 9/13/21.
//

#include "Client.h"

Client *Client::unique_instance{nullptr};
mutex Client::mutex_;

Client::Client() {}

Client::~Client() {}

/**
 * @brief Getter for the unique instance of the client
 * @return the client instance
 */
Client *Client::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr) { unique_instance = new Client(); }
    return unique_instance;
}

void Client::Send(const char *msg) {
    int sendRes = send(clientSocket, msg, strlen(msg), 0);
    if (sendRes == -1) {
        std::cout << "SEND MESSAGE FAILED " << std::endl;
    }
}

int Client::InitClient(int newPort, string ip) {

    if (clientSocket == -1) {
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(newPort);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    int connectRes = connect(clientSocket, (sockaddr *) &addr, sizeof(addr));
    if (connectRes == 0) {
        cout << "You have connect to server !" << endl;
    }

    auto Connect_sms = new TypeMessage();
    Connect_sms->setFirstTime("TRUE");
    string newjson = JSON_Management::TypeMessageToJSON(Connect_sms);
    Send(newjson.c_str());


    if (connectRes == -1) {
        return 1;
    }
    char buf[4096];
    string userInput;


    do {

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1) {
            cout << "There was an error getting response from server\r\n";
        } else {
            //		Display response
            server_response = string(buf, bytesReceived);
        }

    } while (true);

}

string Client::ReadString() {
    return server_response;
}

string Client::setResponse(string newresponse) {
    server_response = newresponse;
}