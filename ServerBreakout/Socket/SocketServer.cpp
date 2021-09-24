//
// Created by keyner on 9/12/21.
//
#include "SocketServer.h"
#include "../Logic/GameManager.h"


SocketServer *SocketServer::unique_instance{nullptr};
mutex SocketServer::mutex_;

/**
 * @brief Constructor of the class.
 */
SocketServer::SocketServer() {}

/**
 * @brief Destructor of the class.
 */
SocketServer::~SocketServer() {}


/**
 * @brief Method for get the instance of the current unique instance.
 * @return SocketServer
 */
SocketServer *SocketServer::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr) { unique_instance = new SocketServer(); }
    return unique_instance;
}

/**
 * @brief This method create a create a socket and search for possible client connection.
 * @param port
 */
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

/**
 * @brief This method runs in a thread and is in charge of read and call the sendMessage function.
 * @param obj
 * @return
 */
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
            auto firstTimeMessage = new TypeMessage();
            firstTimeMessage->setMatrix(GameManager::getInstance()->getMatrix().matrixToString());
            firstTimeMessage->setScore(to_string(GameManager::getInstance()->getPlayer().getScore()));
            //firstTimeMessage->setBallMovement(to_string(GameManager::getInstance()));
            firstTimeMessage->setBarSize(to_string(GameManager::getInstance()->getBar().getSize()));
            firstTimeMessage->setDepth(to_string(GameManager::getInstance()->getBall().getDepth()));
            firstTimeMessage->setLives(to_string(GameManager::getInstance()->getPlayer().getLives()));
            string json = JSON_Management::TypeMessageToJSON(firstTimeMessage);
            sendMessage(json.c_str());
        }
        else if(collision == "TRUE"){

            GameManager::getInstance()->getMatrix().deleteElement(stoi(x),stoi(y));
            auto collisionMessage = new TypeMessage();
            collisionMessage->setMatrix(GameManager::getInstance()->getMatrix().matrixToString());
            collisionMessage->setScore(to_string(GameManager::getInstance()->getPlayer().getScore()));
            //collisionMessage->setBallMovement(to_string(GameManager::getInstance()->getBall().getSpeedX()));
            collisionMessage->setBarSize(to_string(GameManager::getInstance()->getBar().getSize()));
            collisionMessage->setDepth(to_string(GameManager::getInstance()->getBall().getDepth()));
            collisionMessage->setLives(to_string(GameManager::getInstance()->getPlayer().getLives()));
            string json = JSON_Management::TypeMessageToJSON(collisionMessage);
            sendMessage(json.c_str());
        }
        cout << message << endl;
    }
}

/**
 *
 * @param msg
 */
void SocketServer::sendMessage(const char *msg) {

    int res = send(client_fd, msg, strlen(msg), 0);
    if (res==-1)
        cout << "Error al enviar mensaje" << endl;
}