#ifndef CLIENTBREAKOUT_GAMEWINDOW_H
#define CLIENTBREAKOUT_GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class GameWindow{

private:
    int width = 1600;
    int height = 900;
    string ip;
    string port;
    string playerName;

public:
    GameWindow(string ip, string port, string playerName){
        this->ip = ip;
        this->port = port;
        this->playerName = playerName;

        cout << "IP: " << this->ip << " Port: " << this->port << " Player: " << this->playerName;
    }

    int start(){
        sf::RenderWindow window(sf::VideoMode(width, height), "Crazy Breakout");

        sf::Texture gameBackground;
        if (!gameBackground.loadFromFile(
                "../Resources/Images/Backgrounds/MenuBackground.png"))
            return EXIT_FAILURE;
        sf::Sprite gameBackgroundSprite(gameBackground);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.key.code == sf::Keyboard::Escape) { //Escape binding to close program
                    window.close();
                }
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(gameBackgroundSprite);
            window.display();
        }
    }

};

#endif //CLIENTBREAKOUT_GAMEWINDOW_H
