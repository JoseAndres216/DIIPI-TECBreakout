#include <iostream>
#include "./Logic/GameManager.h"
#include "DataStructures/Matrix/Matrix.h"
#include "Socket/SocketServer.h"

using namespace std;

SocketServer* server;
string input;
int port;

void * runServer(void *){
    try{
        server->run(port);
    }catch(string ex){
        cout << ex << endl;
    }
    pthread_exit(NULL);
}

int main() {

    cout << "Por favor escriba el puerto en el que quiere escuchar" << endl;
    getline(cin, input);
    port = stoi(input);
    server = new SocketServer;
    pthread_t socketThread;
    pthread_create(&socketThread, 0, runServer, NULL);
    pthread_detach(socketThread);

    string json = "Hola desde el servidor";
    while(1){
        string msg;
        cin >> msg;
        if(msg == "salir")
            break;
        server->setMessage(json.c_str());
    }
    delete server;
    return 0;
}