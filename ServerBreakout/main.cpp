#include <iostream>
#include "DataStructures/Matrix/Matrix.h"
#include "Socket/SocketServer.h"
#include <thread>

using namespace std;

string input;
int port;

void RunServer(int port) {
    SocketServer::getInstance()->InitServer(port);
}

int main() {

    cout << "Por favor escriba el puerto en el que quiere escuchar" << endl;
    getline(cin, input);
    port = stoi(input);
    thread socket(RunServer, port);
    socket.join();
    return 0;
}