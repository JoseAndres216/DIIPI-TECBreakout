//
// Created by keyner on 9/12/21.
//
#include "SocketServer.h"

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

    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (descriptor < 0)
        cout << "Error al crear el servidor" << endl;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port = htons(port);
    memset(&info.sin_zero, 0, sizeof(info.sin_zero));


    if ((bind(descriptor, (sockaddr *) &info, (socklen_t) sizeof(info))) < 0)
        cout << "Error al crear el servidor" << endl;
    listen(descriptor, 4);

    while (true) {
        socketData data;
        socklen_t t = sizeof(data.info);
        cout << "Esperando cliente" << endl;
        data.descriptor = accept(descriptor, (sockaddr *) &data.info, &t);
        if (data.descriptor < 0) {
            cout << "Error al aceptar el cliente" << endl;
            break;
        } else {
            clients.push_back(data.descriptor);
            cout << "Cliente conectado" << endl;
            pthread_t thread;
            pthread_create(&thread, 0, clientController, (void *) &data);
            pthread_detach(thread);
        }
    }
    close(descriptor);
}

void *SocketServer::clientController(void *obj) {

    socketData *data = (socketData *) obj;
    while (true) {
        string message;
        char buffer[8192];
        while (1) {
            memset(buffer, 0, 8192);
            int bytes = recv(data->descriptor, buffer, 8192, 0);
            message = string(buffer, 0, bytes);
            if (bytes <= 0) {
                close(data->descriptor);
                pthread_exit(NULL);
            }
            if (bytes < 8192) {
                break;
            }
        }
        cout << message << endl;
    }
    close(data->descriptor);
    pthread_exit(NULL);
}

void SocketServer::sendMessage(const char *msg) {

    for (int i = 0; i < clients.size(); i++) {
        send(clients[i], msg, strlen(msg), 0);
    }
}