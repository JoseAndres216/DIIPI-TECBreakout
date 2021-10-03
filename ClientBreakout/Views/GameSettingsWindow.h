#ifndef CLIENTBREAKOUT_GAMESETTINGSWINDOW_H
#define CLIENTBREAKOUT_GAMESETTINGSWINDOW_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

#include "GameWindow.h"

using namespace std;

/**
 * @class Class for the game settings window GUI.
 */
class GameSettingsWindow {

private: // Class' attributes

    int width = 1600;
    int height = 900;
    string ip = "127.0.0.1";
    string port = "8080";
    string playerName = "PLAYER 1";

public: // Class' functions

    /**
     * @brief Server connection function.
     * @param port
     * @param ip
     */
    static void RunClient(string port, string ip) {
        Client::getInstance()->InitClient(stoi(port), ip);
    }

    /**
     * @brief GUI start function.
     * @return 0.
     */
    int start() {
        //Creation of the window
        sf::RenderWindow window(sf::VideoMode(width, height), "Crazy Breakout");

        //Load of the background image
        sf::Texture menuBackground;
        if (!menuBackground.loadFromFile(
                "../Resources/Images/Backgrounds/GameSettingsBackground.png"))
            return EXIT_FAILURE;
        sf::Sprite gameSettingsbackgroundSprite(menuBackground);

        sf::Texture loadingBackground;
        if (!loadingBackground.loadFromFile(
                "../Resources/Images/Backgrounds/LoadingBackground.png"))
            return EXIT_FAILURE;
        sf::Sprite loadingBackgroundSprite(loadingBackground);

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
        sf::Text gameSettingstext;
        gameSettingstext.setFont(Atarifont);
        gameSettingstext.setString("CRAZY BREAKOUT SETTINGS");
        gameSettingstext.setCharacterSize(60);
        gameSettingstext.setFillColor(sf::Color::White);
        gameSettingstext.setOutlineColor(sf::Color::Black);
        gameSettingstext.setOutlineThickness(10);
        gameSettingstext.setPosition(150, 50);

        //Text of the player playerName
        sf::Text playerNametext;
        playerNametext.setFont(AtariClassic);
        playerNametext.setString("Player:");
        playerNametext.setCharacterSize(30);
        playerNametext.setFillColor(sf::Color::White);
        playerNametext.setOutlineColor(sf::Color::Black);
        playerNametext.setOutlineThickness(5);
        playerNametext.setPosition(450, 240);

        sf::Text providedPlayernameText;
        providedPlayernameText.setFont(AtariClassic);
        providedPlayernameText.setString(this->playerName);
        providedPlayernameText.setCharacterSize(30);
        providedPlayernameText.setFillColor(sf::Color::White);
        providedPlayernameText.setOutlineColor(sf::Color::Black);
        providedPlayernameText.setOutlineThickness(5);
        providedPlayernameText.setPosition(420, 310);

        //Text of the ip
        sf::Text ipText;
        ipText.setFont(AtariClassic);
        ipText.setString("IP:");
        ipText.setCharacterSize(30);
        ipText.setFillColor(sf::Color::White);
        ipText.setOutlineColor(sf::Color::Black);
        ipText.setOutlineThickness(5);
        ipText.setPosition(450, 480);

        sf::Text providedIptext;
        providedIptext.setFont(AtariClassic);
        providedIptext.setString(this->ip);
        providedIptext.setCharacterSize(20);
        providedIptext.setFillColor(sf::Color::White);
        providedIptext.setOutlineColor(sf::Color::Black);
        providedIptext.setOutlineThickness(5);
        providedIptext.setPosition(420, 560);

        //Text of the port
        sf::Text portText;
        portText.setFont(AtariClassic);
        portText.setString("Port:");
        portText.setCharacterSize(30);
        portText.setFillColor(sf::Color::White);
        portText.setOutlineColor(sf::Color::Black);
        portText.setOutlineThickness(5);
        portText.setPosition(850, 480);

        sf::Text providedPorttext;
        providedPorttext.setFont(AtariClassic);
        providedPorttext.setString(this->port);
        providedPorttext.setCharacterSize(30);
        providedPorttext.setFillColor(sf::Color::White);
        providedPorttext.setOutlineColor(sf::Color::Black);
        providedPorttext.setOutlineThickness(5);
        providedPorttext.setPosition(830, 550);

        //Text of the play binding
        sf::Text playText;
        playText.setFont(AtariClassic);
        playText.setString("Press B to play!");
        playText.setCharacterSize(35);
        playText.setFillColor(sf::Color::White);
        playText.setOutlineColor(sf::Color::Black);
        playText.setOutlineThickness(5);
        playText.setPosition(520, 800);

        //Text of the rules binding
        sf::Text htpText;
        htpText.setFont(AtariClassic);
        htpText.setString("How to play?");
        htpText.setCharacterSize(50);
        htpText.setFillColor(sf::Color::White);
        htpText.setOutlineColor(sf::Color::Black);
        htpText.setOutlineThickness(5);
        htpText.setPosition(520, 50);

        //Text of the single block binding
        sf::Text singleBlockText;
        singleBlockText.setFont(AtariClassic);
        singleBlockText.setString("1 Hit to destroy");
        singleBlockText.setCharacterSize(20);
        singleBlockText.setFillColor(sf::Color::White);
        singleBlockText.setOutlineColor(sf::Color::Black);
        singleBlockText.setOutlineThickness(5);
        singleBlockText.setPosition(400, 230);

        //Text of the double block block binding
        sf::Text doubleBlockText;
        doubleBlockText.setFont(AtariClassic);
        doubleBlockText.setString("2 Hits to destroy");
        doubleBlockText.setCharacterSize(20);
        doubleBlockText.setFillColor(sf::Color::White);
        doubleBlockText.setOutlineColor(sf::Color::Black);
        doubleBlockText.setOutlineThickness(5);
        doubleBlockText.setPosition(400, 355);

        //Text of the triple block binding
        sf::Text tripleBlockText;
        tripleBlockText.setFont(AtariClassic);
        tripleBlockText.setString("3 Hits to destroy");
        tripleBlockText.setCharacterSize(20);
        tripleBlockText.setFillColor(sf::Color::White);
        tripleBlockText.setOutlineColor(sf::Color::Black);
        tripleBlockText.setOutlineThickness(5);
        tripleBlockText.setPosition(400, 485);

        //Text of the surprise block binding
        sf::Text surpriseBlockText;
        surpriseBlockText.setFont(AtariClassic);
        surpriseBlockText.setString("Gives surprise events");
        surpriseBlockText.setCharacterSize(20);
        surpriseBlockText.setFillColor(sf::Color::White);
        surpriseBlockText.setOutlineColor(sf::Color::Black);
        surpriseBlockText.setOutlineThickness(5);
        surpriseBlockText.setPosition(950, 230);

        //Text of the inside block binding
        sf::Text insideBlockText;
        insideBlockText.setFont(AtariClassic);
        insideBlockText.setString("Destroy it with depth!");
        insideBlockText.setCharacterSize(20);
        insideBlockText.setFillColor(sf::Color::White);
        insideBlockText.setOutlineColor(sf::Color::Black);
        insideBlockText.setOutlineThickness(5);
        insideBlockText.setPosition(950, 355);

        //Text of the depth block binding
        sf::Text depthBlockText;
        depthBlockText.setFont(AtariClassic);
        depthBlockText.setString("Increases ball depth");
        depthBlockText.setCharacterSize(20);
        depthBlockText.setFillColor(sf::Color::White);
        depthBlockText.setOutlineColor(sf::Color::Black);
        depthBlockText.setOutlineThickness(5);
        depthBlockText.setPosition(950, 485);

        //Text of the bar behavior binding
        sf::Text barBehaviorText;
        barBehaviorText.setFont(AtariClassic);
        barBehaviorText.setString("To move the game bar. Avoid loosing balls!");
        barBehaviorText.setCharacterSize(22);
        barBehaviorText.setFillColor(sf::Color::White);
        barBehaviorText.setOutlineColor(sf::Color::Black);
        barBehaviorText.setOutlineThickness(5);
        barBehaviorText.setPosition(365, 630);

        //Text of the play binding
        sf::Text warningText;
        warningText.setFont(AtariClassic);
        warningText.setString("");
        warningText.setCharacterSize(20);
        warningText.setFillColor(sf::Color::Red);
        warningText.setOutlineColor(sf::Color::Black);
        warningText.setOutlineThickness(5);
        warningText.setPosition(550, 675);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                // Mouse events to emulate buttons
                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (event.mouseButton.x >= 400 && event.mouseButton.x <= 1200 && event.mouseButton.y >= 280 &&
                            event.mouseButton.y <= 380) { //Button for typing the player name
                            string playerName;
                            cout << "Player: ";
                            cin >> playerName;
                            this->playerName = playerName;
                            warningText.setString("");
                            providedPlayernameText.setString(this->playerName);
                        } else if (event.mouseButton.x >= 400 && event.mouseButton.x <= 790 &&
                                   event.mouseButton.y >= 520 &&
                                   event.mouseButton.y <= 620) { //Button for typing the ip
                            string ip;
                            cout << "IP: ";
                            cin >> ip;
                            this->ip = ip;
                            warningText.setString("");
                            providedIptext.setString(this->ip);
                        } else if (event.mouseButton.x >= 810 && event.mouseButton.x <= 1200 &&
                                   event.mouseButton.y >= 520 &&
                                   event.mouseButton.y <= 620) { //Button for typing the port
                            string port;
                            cout << "Port: ";
                            cin >> port;
                            this->port = port;
                            providedPorttext.setString(this->port);
                            warningText.setString("");
                        }
                    }
                }
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::B) { // B Binding to go to game window
                        if (this->playerName != "" and this->ip != "" and this->port != "") { // Validating no blanks

                            thread socket(RunClient, port, ip);
                            socket.detach();

                            window.clear();

                            playText.setString("Loading game...");
                            playText.setFillColor(sf::Color::White);
                            playText.setPosition(525, 800);

                            window.draw(loadingBackgroundSprite);
                            window.draw(playText);
                            window.draw(htpText);
                            window.draw(singleBlockText);
                            window.draw(doubleBlockText);
                            window.draw(tripleBlockText);
                            window.draw(surpriseBlockText);
                            window.draw(insideBlockText);
                            window.draw(depthBlockText);
                            window.draw(barBehaviorText);

                            window.display();
                            sf::sleep(sf::seconds(45));
                            window.close();
                            GameWindow *window = new GameWindow(this->ip, this->port, this->playerName);
                            window->start();
                        } else { // In case of blanks
                            warningText.setString("Please, fill the blanks.");
                        }
                    } else if (event.key.code == sf::Keyboard::Escape) { //Escape binding to close program
                        window.close();
                    }
                }
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            //Drawing of the background image
            window.draw(gameSettingsbackgroundSprite);

            //Drawing of the title text
            window.draw(gameSettingstext);

            //Drawing of the player playerName text
            window.draw(playerNametext);
            window.draw(providedPlayernameText);

            //Drawing of the player playerName text
            window.draw(ipText);
            window.draw(providedIptext);

            //Drawing of the player playerName text
            window.draw(portText);
            window.draw(providedPorttext);

            //Drawing of the play text
            window.draw(playText);

            //Drawing of the warning text
            window.draw(warningText);

            window.display();
        }
    }

};

#endif //CLIENTBREAKOUT_GAMESETTINGSWINDOW_H
