//
// Created by keyner on 9/12/21.
//
#include "SocketServer.h"
#include "../Logic/GameManager.h"


SocketServer *SocketServer::unique_instance{nullptr};
mutex SocketServer::mutex_;

SocketServer::SocketServer() {}

SocketServer::~SocketServer() {}

SocketServer *SocketServer::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr) { unique_instance = new SocketServer(); }
    return unique_instance;
}


void SocketServer::InitServer(int port) {

    socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd < 0)
        cout << "Error al crear el servidor" << endl;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));


    if ((bind(socketFd, (sockaddr *) &addr, (socklen_t) sizeof(addr))) < 0)
        cout << "Error al crear el servidor" << endl;
    listen(socketFd, 4);

    cout << "Esperando cliente" << endl;
    while (true) {
        Client client;
        socklen_t t = sizeof(client.clientAddr);
        client.clientFd = accept(socketFd, (sockaddr *) &client.clientAddr, &t);
        if (client.clientFd < 0) {
            cout << "Error al aceptar el cliente" << endl;
            break;
        } else {
            client_fd = client.clientFd;
            cout << "Cliente conectado" << endl;
            pthread_t thread;
            pthread_create(&thread, 0, clientController, (void *)&client);
            pthread_detach(thread);
        }
    }
    close(socketFd);
}

void *SocketServer::clientController(void *obj) {

    Client *client = (Client *) obj;
    while (true) {
        string message;
        string firstTime;
        string collision;
        string x;
        string y;
        char buffer[8192];
        while (1) {
            memset(buffer, 0, 8192);
            int bytes = recv(client->clientFd, buffer, 8192, 0);
            message = string(buffer, 0, bytes);
            if (bytes <= 0) {
                close(client->clientFd);
                pthread_exit(NULL);
            }
            if (bytes < 8192) {
                break;
            }
        }
        firstTime = JSON_Management::GetJSONString("FirstTime", message);
        collision = JSON_Management::GetJSONString("Collision", message);
        x = JSON_Management::GetJSONString("X", message);
        y = JSON_Management::GetJSONString("Y", message);
        if(firstTime == "TRUE"){
            GameManager::getInstance()->initializeComponents();
            sendMessage(GameManager::getInstance()->getMatrix().matrixToString().c_str());
        }
        else if(collision == "TRUE"){
            GameManager::getInstance()->getMatrix().deleteElement(stoi(x),stoi(y));
            sendMessage(GameManager::getInstance()->getMatrix().matrixToString().c_str());
        }
        cout << message << endl;
    }
}

void SocketServer::sendMessage(const char *msg) {

    int res = send(client_fd, msg, strlen(msg), 0);
    if (res==-1)
        cout << "Error al enviar mensaje" << endl;
}