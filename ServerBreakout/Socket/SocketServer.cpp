//
// Created by keyner on 9/12/21.
//
#include "SocketServer.h"

SocketServer::SocketServer() {}

bool SocketServer::createSocket(int port) {

    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(descriptor < 0)
        return false;

    info.sin_family = AF_INET;
    info.sin_addr.s_addr =INADDR_ANY;
    info.sin_port = htons(port);
    memset(&info.sin_zero, 0, sizeof(info.sin_zero));
    return true;

}

bool SocketServer::linkKernel() {

    if((bind(descriptor, (sockaddr *)&info, (socklen_t)sizeof(info)))<0)
        return false;
    listen(descriptor, 4);
    return true;
}

void SocketServer::run(int port) {

    if(!createSocket(port))
        throw string("No se pudo crear el servidor");
    if(!linkKernel())
        throw string("No se pudo enlazar el kernel");

    while(true){
        socketData data;
        socklen_t t = sizeof(data.info);
        cout << "Esperando cliente" << endl;
        data.descriptor = accept(descriptor, (sockaddr *)&data.info, &t);
        if(data.descriptor < 0){
            cout << "Error al aceptar el cliente" << endl;
            break;
        }else{
            clients.push_back(data.descriptor);
            cout << "Cliente conectado" << endl;
            pthread_t thread;
            pthread_create(&thread, 0, SocketServer::clientController, (void*)&data);
            pthread_detach(thread);
        }
    }
    close(descriptor);
}

void * SocketServer::clientController(void *obj) {

    socketData* data = (socketData*)obj;
    while(true){
        string message;
        char buffer[1024] = {0};
        while(1){
            memset(buffer, 0, 1024);
            int bytes = recv(data->descriptor, buffer, 1024, 0);
            message.append(buffer, bytes);
            if(bytes <= 0){
                close(data->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 1024){
                break;
            }
        }
        cout << message << endl;
    }
    close(data->descriptor);
    pthread_exit(NULL);
}

void SocketServer::setMessage(const char *msg) {

    for(int i = 0; i< clients.size(); i++){
        send(clients[i], msg, strlen(msg), 0);
    }
}