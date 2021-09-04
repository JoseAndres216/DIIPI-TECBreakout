//
// Created by keyner on 9/3/21.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef CLIENTBREAKOUT_GAMEWINDOW_H
#define CLIENTBREAKOUT_GAMEWINDOW_H

using namespace std;

class GameWindow{

private:

    int width = 1600;
    int height = 900;
    string ip;
    string port;
    string name;

public:

    int start(){
        sf::RenderWindow window(sf::VideoMode(1600, 900), "Crazy Breakout");

        sf::Texture gameBackground;
        if (!gameBackground.loadFromFile(
                "../Resources/Images/MainWindowBackgorund.png"))
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
