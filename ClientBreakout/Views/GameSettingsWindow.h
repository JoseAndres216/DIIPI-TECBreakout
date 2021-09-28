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
    string port = "9090";
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
        sf::RenderWindow window(sf::VideoMode(width, height), "Crazy Breakout Settings");

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

                            playText.setString("Loading game! Please wait...");
                            playText.setFillColor(sf::Color::Green);
                            playText.setPosition(300, 400);

                            window.draw(loadingBackgroundSprite);
                            window.draw(playText);

                            window.display();
                            sf::sleep(sf::seconds(15));
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
