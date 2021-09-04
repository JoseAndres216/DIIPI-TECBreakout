//
// Created by keyner on 9/3/21.
//
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include <iostream>
#ifndef CLIENTBREAKOUT_MENUWINDOW_H
#define CLIENTBREAKOUT_MENUWINDOW_H

using namespace std;

class MenuWindow{

private:

    int width = 1600;
    int height = 900;
    string ip;
    string port;
    string name;

public:

    int start(){
        sf::RenderWindow window(sf::VideoMode(1600, 900), "Crazy Breakout");

        sf::Texture menuBackground;
        if (!menuBackground.loadFromFile(
                "../Resources/Images/MainWindowBackgorund.png"))
            return EXIT_FAILURE;
        sf::Sprite menuBackgroundSprite(menuBackground);

        sf::Font font;
        if (!font.loadFromFile(
                "../Resources/Fonts/AtariFont.ttf")) {
            window.close();
        }

        sf::Text BreakoutText;
        BreakoutText.setFont(font);
        BreakoutText.setString("CRAZY BREAKOUT");
        BreakoutText.setCharacterSize(100);
        BreakoutText.setFillColor(sf::Color::White);
        BreakoutText.setOutlineColor(sf::Color::Black);
        BreakoutText.setOutlineThickness(5);
        BreakoutText.setPosition(110, 160);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Enter) { //A binding to go to next window
                        window.close();
                        GameWindow *window = new GameWindow();
                        window->start();
                    }else if (event.key.code == sf::Keyboard::Escape) { //Escape binding to close program
                        window.close();
                    }
                }
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(menuBackgroundSprite);
            window.draw(BreakoutText);
            window.display();
        }
    }

};



#endif //CLIENTBREAKOUT_MENUWINDOW_H
