#ifndef CLIENTBREAKOUT_MENUWINDOW_H
#define CLIENTBREAKOUT_MENUWINDOW_H

#include <SFML/Graphics.hpp>
#include "GameSettingsWindow.h"
#include <iostream>

using namespace std;

class MenuWindow{

private:
    int width = 1600;
    int height = 900;

public:
    int start(){
        //Creation of the window
        sf::RenderWindow window(sf::VideoMode(width, height), "Crazy Breakout");

        //Load of the background image
        sf::Texture menuBackground;
        if (!menuBackground.loadFromFile(
                "../Resources/Images/Backgrounds/MenuBackground.png"))
            return EXIT_FAILURE;
        sf::Sprite menuBackgroundSprite(menuBackground);

        //Load of the fonts
        sf::Font Atarifont;
        if (!Atarifont.loadFromFile(
                "../Resources/Fonts/AtariFont.ttf")) {
            window.close();
        }
        sf::Font AtariClassic;
        if (!AtariClassic.loadFromFile(
                "../Resources/Fonts/AtariClassic.ttf")) {
            window.close();
        }

        //Text of the title
        sf::Text breakoutText;
        breakoutText.setFont(Atarifont);
        breakoutText.setString("CRAZY BREAKOUT");
        breakoutText.setCharacterSize(110);
        breakoutText.setFillColor(sf::Color::White);
        breakoutText.setOutlineColor(sf::Color::Black);
        breakoutText.setOutlineThickness(10);
        breakoutText.setPosition(65, 160);

        //Text of the creators
        sf::Text creatorsText;
        creatorsText.setFont(AtariClassic);
        creatorsText.setString("by KeynerG & JoseAndres216");
        creatorsText.setCharacterSize(25);
        creatorsText.setFillColor(sf::Color::White);
        creatorsText.setOutlineColor(sf::Color::Black);
        creatorsText.setOutlineThickness(5);
        creatorsText.setPosition(450, 400);

        //Text of the play binding
        sf::Text playText;
        playText.setFont(AtariClassic);
        playText.setString("Press any key to start!");
        playText.setCharacterSize(35);
        playText.setFillColor(sf::Color::White);
        playText.setOutlineColor(sf::Color::Black);
        playText.setOutlineThickness(5);
        playText.setPosition(400, 750);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Escape) { //Escape binding to close program
                        window.close();
                    }else{ // Any key binding to start the game
                        window.close();
                        GameSettingsWindow *window = new GameSettingsWindow();
                        window->start();
                    }
                }
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            //Drawing of the background image
            window.draw(menuBackgroundSprite);

            //Drawing of the title text
            window.draw(breakoutText);

            //Drawing of the creators text
            window.draw(creatorsText);

            //Drawing of the play text
            window.draw(playText);

            window.display();
        }
    }
};

#endif //CLIENTBREAKOUT_MENUWINDOW_H