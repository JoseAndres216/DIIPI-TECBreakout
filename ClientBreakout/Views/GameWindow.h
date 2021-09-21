#ifndef CLIENTBREAKOUT_GAMEWINDOW_H
#define CLIENTBREAKOUT_GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "../Socket/Client.h"
#include "../Socket/TypeMessage.h"

using namespace std;


class GameWindow {

private: // Class' attributes
    int width = 1600;
    int height = 900;
    string ip;
    string port;
    string playerName;
    int score;
    int lifes;
    int ballDepth;
    Client *client;
    vector<string> matrix;
    bool ballMoves = false;
    int ballMovementX = 5;
    int ballMovementY = -5;

public: // Class' functions

    void RunClient() {
        Client::getInstance()->InitClient(stoi(port), ip);
    }

    void updateMatrix() {
        string updatedmatrix = Client::getInstance()->getResponse();
        this->matrix.clear();
        stringstream ss(updatedmatrix);

        while (ss.good()) {
            string substr;
            getline(ss, substr, ';');
            matrix.push_back(substr);
        }
    }

    // Class constructor
    GameWindow(string ip, string port, string playerName) {
        this->ip = ip;
        this->port = port;
        this->playerName = playerName;
        this->score = 0;
        this->lifes = 3;
        this->ballDepth = 0;
        updateMatrix();
    }


    // Function to start the GUI process
    int start() {
        // Window creation
        sf::RenderWindow window(sf::VideoMode(width, height), "Crazy Breakout");

        //Window FPS
        window.setFramerateLimit(60);

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

        // Load of the double block texture
        sf::Texture doubleBlocktexture;
        if (!doubleBlocktexture.loadFromFile(
                "../Resources/Images/Game/DoubleBlock.png"))
            return EXIT_FAILURE;

        // Load of the double block with resistance one texture
        sf::Texture doubleBlockR1texture;
        if (!doubleBlockR1texture.loadFromFile(
                "../Resources/Images/Game/DoubleBlockR1.png"))
            return EXIT_FAILURE;

        // Load of the triple block texture
        sf::Texture tripleBlocktexture;
        if (!tripleBlocktexture.loadFromFile(
                "../Resources/Images/Game/TripleBlock.png"))
            return EXIT_FAILURE;

        // Load of the triple block with resistance one texture
        sf::Texture tripleBlockR1texture;
        if (!tripleBlockR1texture.loadFromFile(
                "../Resources/Images/Game/TripleBlockR1.png"))
            return EXIT_FAILURE;

        // Load of the triple block with resistance two texture
        sf::Texture tripleBlockR2texture;
        if (!tripleBlockR2texture.loadFromFile(
                "../Resources/Images/Game/TripleBlockR2.png"))
            return EXIT_FAILURE;

        // Load of the intern block texture
        sf::Texture internBlocktexture;
        if (!internBlocktexture.loadFromFile(
                "../Resources/Images/Game/InternBlock.png"))
            return EXIT_FAILURE;

        // Load of the depth block texture
        sf::Texture depthBlocktexture;
        if (!depthBlocktexture.loadFromFile(
                "../Resources/Images/Game/DepthBlock.png"))
            return EXIT_FAILURE;

        // Load of the surprise block texture
        sf::Texture surpriseBlocktexture;
        if (!surpriseBlocktexture.loadFromFile(
                "../Resources/Images/Game/SurpriseBlock.png"))
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
        bar.setOutlineThickness(2);
        bar.setOutlineColor(sf::Color::Black);

        // Creation of the ball
        sf::CircleShape ball(15);
        ball.setFillColor(sf::Color::White);
        ball.setPosition(785, 750);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonReleased) { // Mouse binding to start game
                    ballMoves = true;
                    /*startGametext.setString("");
                    startGametext.setPosition(10, 10);
                    auto collision = new TypeMessage();
                    collision->setCollision("TRUE");
                    collision->setX(to_string(100));
                    collision->setY(to_string(100));
                    string json = JSON_Management::TypeMessageToJSON(collision);
                    Client::getInstance()->Send(json.c_str());*/
                }
                if (event.key.code == sf::Keyboard::Escape) { //Escape binding to close program
                    window.close();
                }
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseMoved) {
                    bar.setPosition((sf::Mouse::getPosition(window).x) - bar.getSize().x / 2, 800);
                    if (bar.getPosition().x < 0) {
                        bar.setPosition(0, 800);
                    }
                    if (bar.getPosition().x > width - bar.getSize().x) {
                        bar.setPosition(width - bar.getSize().x, 800);
                    }
                }
            }

            if (ballMoves) {
                ball.move(ballMovementX, ballMovementY);
            }

            if (ball.getPosition().x < 0) {
                ballMovementX = ballMovementX * -1;
            } else if (ball.getPosition().x > (width - ball.getRadius())) {
                ballMovementX = ballMovementX * -1;
            } else if (ball.getPosition().y < 0) {
                ballMovementY = ballMovementY * -1;
            } else if (ball.getPosition().y > height) {
                ballMovementY = ballMovementY * -1;
            } else if (ball.getPosition().y == (bar.getPosition().y - ball.getRadius()) and
                       ball.getPosition().x > bar.getPosition().x and
                       ball.getPosition().x < (bar.getPosition().x + bar.getSize().x)) {
                ballMovementY = ballMovementY * -1;
            } else if (ball.getPosition().x > 100 and ball.getPosition().x < 1500 and ball.getPosition().y > 100 and
                       ball.getPosition().y < 400) {
                for (int i = 0; i < matrix.size(); i++) {
                    string blockinfo = matrix[i];
                    vector<string> block;

                    stringstream ss(blockinfo);

                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, ',');
                        block.push_back(substr);
                    }

                    int blockX = stoi(block[0]);
                    int blockY = stoi(block[1]);

                    if (ball.getPosition().x >= blockX and ball.getPosition().x <= (blockX + 100) and
                            (ball.getPosition().y + 15) >= blockY and ball.getPosition().y <= (blockY + 50)) {
                        cout << "Collide on block on x: " << blockX << " and y: " << blockY << endl;
                        if(ball.getPosition().x == blockX and ball.getPosition().x == (blockX + 100)){
                            ballMovementX = ballMovementX * -1;
                        }else if(ball.getPosition().y == blockY and ball.getPosition().y == (blockY + 50)){
                            ballMovementY = ballMovementY * -1;
                        } else{
                            ballMovementY = ballMovementY * -1;
                        }
                    }
                }
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
            for (int i = 0; i < matrix.size(); i++) {
                string blockinfo = matrix[i];
                vector<string> block;

                stringstream ss(blockinfo);

                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    block.push_back(substr);
                }

                int blockX = stoi(block[0]);
                int blockY = stoi(block[1]);
                int blockType = stoi(block[2]);
                int blockResistance = stoi(block[3]);

                if (blockResistance != 0) {
                    sf::RectangleShape blockShape(sf::Vector2f(100, 50));
                    blockShape.setPosition(blockX, blockY);
                    if (blockType == 1) {
                        blockShape.setTexture(&singleBlocktexture);
                    } else if (blockType == 2) {
                        if (blockResistance == 1) {
                            blockShape.setTexture(&doubleBlockR1texture);
                        } else {
                            blockShape.setTexture(&doubleBlocktexture);
                        }
                    } else if (blockType == 3) {
                        if (blockResistance == 1) {
                            blockShape.setTexture(&tripleBlockR1texture);
                        } else if (blockResistance == 2) {
                            blockShape.setTexture(&tripleBlockR2texture);
                        } else {
                            blockShape.setTexture(&tripleBlocktexture);
                        }
                    } else if (blockType == 4) {
                        blockShape.setTexture(&surpriseBlocktexture);
                    } else if (blockType == 5) {
                        blockShape.setTexture(&internBlocktexture);
                    } else if (blockType == 6) {
                        blockShape.setTexture(&depthBlocktexture);
                    }

                    window.draw(blockShape);
                }
            }

            window.draw(bar);

            // Drawing of the ball
            window.draw(ball);

            window.display();
        }
    }
};

#endif //CLIENTBREAKOUT_GAMEWINDOW_H
