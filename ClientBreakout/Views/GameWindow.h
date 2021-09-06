#ifndef CLIENTBREAKOUT_GAMEWINDOW_H
#define CLIENTBREAKOUT_GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class GameWindow{

private: // Class' attributes
    int width = 1600;
    int height = 900;
    string ip;
    string port;
    string playerName;
    int score;
    int lifes;
    int ballDepth;

public: // Class' functions

    // Class constructor
    GameWindow(string ip, string port, string playerName){
        this->ip = ip;
        this->port = port;
        this->playerName = playerName;
        this->score = 0;
        this->lifes = 3;
        this->ballDepth = 0;
    }

    // Function to start the GUI process
    int start(){
        // Window creation
        sf::RenderWindow window(sf::VideoMode(width, height), "Crazy Breakout");

        // Mouse hiding
        window.setMouseCursorVisible(false);

        // Load of the background image
        sf::Texture gameBackground;
        if (!gameBackground.loadFromFile(
                "../Resources/Images/Backgrounds/GameBackground.png"))
            return EXIT_FAILURE;
        sf::Sprite gameBackgroundSprite(gameBackground);

        // Load of the font
        sf::Font AtariClassic;
        if (!AtariClassic.loadFromFile(
                "../Resources/Fonts/AtariClassic.ttf")) {
            window.close();
        }

        // Load of the single block texture
        sf::Texture singleBlocktexture;
        if (!singleBlocktexture.loadFromFile(
                "../Resources/Images/Game/SingleBlock.png"))
            return EXIT_FAILURE;

        // Load of the single block texture
        sf::Texture doubleBlocktexture;
        if (!doubleBlocktexture.loadFromFile(
                "../Resources/Images/Game/DoubleBlock.png"))
            return EXIT_FAILURE;

        // Load of the single block texture
        sf::Texture internBlocktexture;
        if (!internBlocktexture.loadFromFile(
                "../Resources/Images/Game/InternBlock.png"))
            return EXIT_FAILURE;

        // Load of the single block texture
        sf::Texture depthBlocktexture;
        if (!depthBlocktexture.loadFromFile(
                "../Resources/Images/Game/DepthBlock.png"))
            return EXIT_FAILURE;

        // Load of the single block texture
        sf::Texture surpriseBlocktexture;
        if (!surpriseBlocktexture.loadFromFile(
                "../Resources/Images/Game/SurpriseBlock.png"))
            return EXIT_FAILURE;

        // Load of the single block texture
        sf::Texture tripleBlocktexture;
        if (!tripleBlocktexture.loadFromFile(
                "../Resources/Images/Game/TripleBlock.png"))
            return EXIT_FAILURE;

        //Text of the player name
        sf::Text playerNametext;
        playerNametext.setFont(AtariClassic);
        playerNametext.setString("Player: " + this->playerName);
        playerNametext.setCharacterSize(20);
        playerNametext.setFillColor(sf::Color::White);
        playerNametext.setOutlineColor(sf::Color::Black);
        playerNametext.setOutlineThickness(5);
        playerNametext.setPosition(10, 10);

        //Text of the player lifes
        sf::Text lifesText;
        lifesText.setFont(AtariClassic);
        lifesText.setString("Lifes: " + to_string(this->lifes));
        lifesText.setCharacterSize(20);
        lifesText.setFillColor(sf::Color::White);
        lifesText.setOutlineColor(sf::Color::Black);
        lifesText.setOutlineThickness(5);
        lifesText.setPosition(720, 10);

        //Text of the player score
        sf::Text scoreText;
        scoreText.setFont(AtariClassic);
        scoreText.setString("Score: " + to_string(this->score));
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setOutlineThickness(5);
        scoreText.setPosition(1350, 10);

        //Text of the start game
        sf::Text startGametext;
        startGametext.setFont(AtariClassic);
        startGametext.setString("Click once to start!");
        startGametext.setCharacterSize(50);
        startGametext.setFillColor(sf::Color::White);
        startGametext.setOutlineColor(sf::Color::Black);
        startGametext.setOutlineThickness(5);
        startGametext.setPosition(300, 500);

        //Text of the ip and port connection
        sf::Text ipPorttext;
        ipPorttext.setFont(AtariClassic);
        ipPorttext.setString("Connected to " + this->ip + " on port " + this->port);
        ipPorttext.setCharacterSize(10);
        ipPorttext.setFillColor(sf::Color::Green);
        ipPorttext.setOutlineColor(sf::Color::Black);
        ipPorttext.setOutlineThickness(2.5);
        ipPorttext.setPosition(10, 880);

        //Text of the ball depth
        sf::Text ballDepthtext;
        ballDepthtext.setFont(AtariClassic);
        ballDepthtext.setString("Ball depth: " + to_string(this->ballDepth));
        ballDepthtext.setCharacterSize(20);
        ballDepthtext.setFillColor(sf::Color::White);
        ballDepthtext.setOutlineColor(sf::Color::Black);
        ballDepthtext.setOutlineThickness(5);
        ballDepthtext.setPosition(1330, 870);

        // Creation of the bar
        sf::RectangleShape bar(sf::Vector2f(300, 25));
        bar.setFillColor(sf::Color::White);
        bar.setPosition(650, 800);

        // Creation of the ball
        sf::CircleShape ball(15);
        ball.setFillColor(sf::Color::White);
        ball.setPosition(785, 750);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::MouseButtonReleased){ // Mouse binding to start game
                    startGametext.setString("");
                    startGametext.setPosition(10,10);
                }
                if (event.key.code == sf::Keyboard::Escape) { //Escape binding to close program
                    window.close();
                }
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            // Drawing of the background image
            window.draw(gameBackgroundSprite);

            // Drawing of the player name text
            window.draw(playerNametext);

            // Drawing of the player score text
            window.draw(scoreText);

            // Drawing of the start game text
            window.draw(startGametext);

            // Drawing of the ip and port text
            window.draw(ipPorttext);

            // Drawing of the player lifes text
            window.draw(lifesText);

            // Drawing of the ball depth text
            window.draw(ballDepthtext);

            //Drawing of the blocks
            for(int i = 100; i<=1400; i+=100){
                sf::RectangleShape tripleBlock(sf::Vector2f(100, 50));
                tripleBlock.setPosition(i, 100);
                tripleBlock.setTexture(&tripleBlocktexture);
                window.draw(tripleBlock);

                sf::RectangleShape doubleBlock(sf::Vector2f(100, 50));
                doubleBlock.setPosition(i, 150);
                doubleBlock.setTexture(&doubleBlocktexture);
                window.draw(doubleBlock);

                sf::RectangleShape singleBlock(sf::Vector2f(100, 50));
                singleBlock.setPosition(i, 200);
                singleBlock.setTexture(&singleBlocktexture);
                window.draw(singleBlock);

                sf::RectangleShape internBlock(sf::Vector2f(100, 50));
                internBlock.setPosition(i, 250);
                internBlock.setTexture(&internBlocktexture);
                window.draw(internBlock);

                sf::RectangleShape surpirseBlock(sf::Vector2f(100, 50));
                surpirseBlock.setPosition(i, 300);
                surpirseBlock.setTexture(&surpriseBlocktexture);
                window.draw(surpirseBlock);

                sf::RectangleShape depthBlock(sf::Vector2f(100, 50));
                depthBlock.setPosition(i, 350);
                depthBlock.setTexture(&depthBlocktexture);
                window.draw(depthBlock);
            }

            // Drawing of the bar
            if(event.mouseMove.x > (bar.getSize().x/2) and event.mouseMove.x < (1600 - (bar.getSize().x/2))){
                bar.setPosition((event.mouseMove.x - (bar.getSize().x/2)), 800);
            }
            window.draw(bar);

            // Drawing of the ball
            window.draw(ball);

            window.display();
        }
    }
};

#endif //CLIENTBREAKOUT_GAMEWINDOW_H
