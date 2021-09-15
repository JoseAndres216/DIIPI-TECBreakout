//
// Created by keyner on 9/13/21.
//

#include "SocketClient.h"

SocketClient::SocketClient() {}


void SocketClient::connect(int port, string ip) {

    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(descriptor < 0)
        cout << "Error al conectar con servidor" << endl;

    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr(ip.c_str());
    info.sin_port = htons(port);
    memset(&info.sin_zero, 0, sizeof(info.sin_zero));

    if((::connect(descriptor, (sockaddr*)&info, (socklen_t) sizeof(info))) < 0){
        cout << "Error al conectar con servidor" << endl;
    }
    cout << "Conectado al servidor" << endl;

    pthread_t thread;
    pthread_create(&thread, 0, SocketClient::controller, (void*)this);
    pthread_detach(thread);
}

void * SocketClient::controller(void *obj) {

    SocketClient* client = (SocketClient*)obj;
    while(true){
        string message;
        char buffer[1024] = {0};
        while(1){
            memset(buffer, 0, 1024);
            int bytes = recv(client->descriptor, buffer, 1024, 0);
            message.append(buffer, bytes);
            if(bytes <= 0){
                close(client->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 1024){
                break;
            }
        }
        cout << message << endl;
    }
    close(client->descriptor);
    pthread_exit(NULL);
}

void SocketClient::setMessage(const char *msg) {

    send(descriptor, msg, strlen(msg), 0);

}