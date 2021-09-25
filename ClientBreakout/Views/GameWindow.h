#ifndef CLIENTBREAKOUT_GAMEWINDOW_H
#define CLIENTBREAKOUT_GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <thread>
#include <iostream>

#include "../Socket/Client.h"
#include "../Socket/TypeMessage.h"
#include "../Socket/JsonManagement.h"

using namespace std;

/**
 * @class Class for the game window GUI.
 */
class GameWindow {

private: // Class' attributes

    int width = 1600;
    int height = 900;
    int score;
    int lives;
    int ballDepth;
    int barSizeX = 300;
    int combo = 0;
    float ballMovementX = 5;
    float ballMovementY = -5;
    bool ballMoves = false;
    string ip;
    string port;
    string playerName;
    vector<string> matrix;

public: // Class' functions

    /**
     * @class GameWindow constructor.
     * @param ip
     * @param port
     * @param playerName
     */
    GameWindow(string ip, string port, string playerName) {
        this->ip = ip;
        this->port = port;
        this->playerName = playerName;
        this->score = 0;
        this->lives = 3;
        this->ballDepth = 0;
        updateMatrix();
        updateInterface();
    }

    /**
     * @brief Matrix update function.
     */
    void updateMatrix() {
        string response = Client::getInstance()->getResponse();
        string updatedMatrix = JSON_Management::GetJSONString("Matrix", response);
        this->matrix.clear();
        stringstream ss(updatedMatrix);

        while (ss.good()) {
            string substr;
            getline(ss, substr, ';');
            matrix.push_back(substr);
        }
    }

    /**
     * @brief GUI elements update function (Player score, lives, ball depth and bar size).
     */
    void updateInterface() {
        string response = Client::getInstance()->getResponse();
        this->score = stoi(JSON_Management::GetJSONString("Score", response));
        this->lives = stoi(JSON_Management::GetJSONString("Lives", response));
        this->ballDepth = stoi(JSON_Management::GetJSONString("Depth", response));
        this->barSizeX = stoi(JSON_Management::GetJSONString("BarSize", response));
        /*
        if(JSON_Management::GetJSONString("ballMovement", response) != ""){
            if(JSON_Management::GetJSONString("ballMovement", response) == "increase"){
                ballMovementX = ballMovementX * 1.5;
                ballMovementY = ballMovementY * 1.5;
            }else{
                ballMovementX = ballMovementX / 1.5;
                ballMovementY = ballMovementY / 1.5;
            }
        }*/
    }

    /**
     * @brief GUI start function.
     * @return 0.
     */
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
        sf::Texture singleBlockTexture;
        if (!singleBlockTexture.loadFromFile(
                "../Resources/Images/Game/SingleBlock.png"))
            return EXIT_FAILURE;

        // Load of the double block texture
        sf::Texture doubleBlockTexture;
        if (!doubleBlockTexture.loadFromFile(
                "../Resources/Images/Game/DoubleBlock.png"))
            return EXIT_FAILURE;

        // Load of the double block with resistance one texture
        sf::Texture doubleBlockR1Texture;
        if (!doubleBlockR1Texture.loadFromFile(
                "../Resources/Images/Game/DoubleBlockR1.png"))
            return EXIT_FAILURE;

        // Load of the triple block texture
        sf::Texture tripleBlockTexture;
        if (!tripleBlockTexture.loadFromFile(
                "../Resources/Images/Game/TripleBlock.png"))
            return EXIT_FAILURE;

        // Load of the triple block with resistance one texture
        sf::Texture tripleBlockR1texture;
        if (!tripleBlockR1texture.loadFromFile(
                "../Resources/Images/Game/TripleBlockR1.png"))
            return EXIT_FAILURE;

        // Load of the triple block with resistance two texture
        sf::Texture tripleBlockR2Texture;
        if (!tripleBlockR2Texture.loadFromFile(
                "../Resources/Images/Game/TripleBlockR2.png"))
            return EXIT_FAILURE;

        // Load of the intern block texture
        sf::Texture internBlockTexture;
        if (!internBlockTexture.loadFromFile(
                "../Resources/Images/Game/InternBlock.png"))
            return EXIT_FAILURE;

        // Load of the depth block texture
        sf::Texture depthBlockTexture;
        if (!depthBlockTexture.loadFromFile(
                "../Resources/Images/Game/DepthBlock.png"))
            return EXIT_FAILURE;

        // Load of the surprise block texture
        sf::Texture surpriseBlockTexture;
        if (!surpriseBlockTexture.loadFromFile(
                "../Resources/Images/Game/SurpriseBlock.png"))
            return EXIT_FAILURE;

        //Text of the player name
        sf::Text playerNameText;
        playerNameText.setFont(AtariClassic);
        playerNameText.setString("Player: " + this->playerName);
        playerNameText.setCharacterSize(20);
        playerNameText.setFillColor(sf::Color::White);
        playerNameText.setOutlineColor(sf::Color::Black);
        playerNameText.setOutlineThickness(5);
        playerNameText.setPosition(10, 10);

        //Text of the player lives
        sf::Text livesText;
        livesText.setFont(AtariClassic);
        livesText.setString("Lives: " + to_string(this->lives));
        livesText.setCharacterSize(20);
        livesText.setFillColor(sf::Color::White);
        livesText.setOutlineColor(sf::Color::Black);
        livesText.setOutlineThickness(5);
        livesText.setPosition(720, 10);

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
        sf::Text startGameText;
        startGameText.setFont(AtariClassic);
        startGameText.setString("Click once to start!");
        startGameText.setCharacterSize(50);
        startGameText.setFillColor(sf::Color::White);
        startGameText.setOutlineColor(sf::Color::Black);
        startGameText.setOutlineThickness(5);
        startGameText.setPosition(300, 500);

        //Text of the ip and port connection
        sf::Text ipPortText;
        ipPortText.setFont(AtariClassic);
        ipPortText.setString("Connected to " + this->ip + " on port " + this->port);
        ipPortText.setCharacterSize(10);
        ipPortText.setFillColor(sf::Color::Green);
        ipPortText.setOutlineColor(sf::Color::Black);
        ipPortText.setOutlineThickness(2.5);
        ipPortText.setPosition(10, 880);

        //Text of the ball depth
        sf::Text ballDepthText;
        ballDepthText.setFont(AtariClassic);
        ballDepthText.setString("Ball depth: " + to_string(this->ballDepth));
        ballDepthText.setCharacterSize(20);
        ballDepthText.setFillColor(sf::Color::White);
        ballDepthText.setOutlineColor(sf::Color::Black);
        ballDepthText.setOutlineThickness(5);
        ballDepthText.setPosition(1330, 870);

        // Creation of the bar
        sf::RectangleShape bar(sf::Vector2f(barSizeX, 25));
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
                    startGameText.setString("");
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

                // Collision with bar
            } else if ((ball.getPosition().y + ball.getRadius() * 2) == bar.getPosition().y and
                       ball.getPosition().x >= bar.getPosition().x and
                       ball.getPosition().x <= (bar.getPosition().x + bar.getSize().x)) {
                ballMovementY = ballMovementY * -1;
                combo++;
                if (combo % 10 == 0) {
                    ballMovementX = ballMovementX * 1.5;
                    ballMovementY = ballMovementY * 1.5;
                }
            } else if ((ball.getPosition().x + ball.getRadius() * 2) >= 100 and ball.getPosition().x <= 1500 and
                       (ball.getPosition().y + ball.getRadius() * 2) >= 100 and
                       ball.getPosition().y <= 400) {
                for (int i = 0; i < matrix.size(); i++) {
                    string blockInfo = matrix[i];
                    vector<string> block;

                    stringstream ss(blockInfo);

                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, ',');
                        block.push_back(substr);
                    }

                    int blockX = stoi(block[0]);
                    int blockY = stoi(block[1]);
                    int blockR = stoi(block[3]);

                    if ((ball.getPosition().x + ball.getRadius() * 2) >= blockX and
                        ball.getPosition().x <= (blockX + 100) and
                        (ball.getPosition().y + ball.getRadius() * 2) >= blockY and
                        ball.getPosition().y <= (blockY + 50) and blockR != 0) {
                        cout << "Collide on block on x: " << blockX << " and y: " << blockY << endl;
                        cout << "Ball position x: " << ball.getPosition().x << " and y: " << ball.getPosition().y
                             << endl;


                        if ((ball.getPosition().x + ball.getRadius() * 2) == blockX or
                            ball.getPosition().x == (blockX + 100)) {
                            ballMovementX = ballMovementX * -1;
                        } else if ((ball.getPosition().y + ball.getRadius() * 2) == blockY or
                                   ball.getPosition().y == (blockY + 50)) {
                            ballMovementY = ballMovementY * -1;
                        } else {
                            ballMovementX = ballMovementX * -1;
                            ballMovementY = ballMovementY * -1;
                        }

                        auto collision = new TypeMessage();
                        collision->setCollision("TRUE");
                        collision->setX(to_string(blockX));
                        collision->setY(to_string(blockY));
                        string json = JSON_Management::TypeMessageToJSON(collision);
                        Client::getInstance()->Send(json.c_str());

                        thread t([this]() {
                            sf::sleep(sf::seconds(1));
                            updateMatrix();
                            updateInterface();
                        });
                        t.detach();
                    }
                }
            }
            bar.setSize(sf::Vector2f(barSizeX, 25));

            window.clear();

            // Drawing of the background image
            window.draw(gameBackgroundSprite);

            // Drawing of the player name text
            window.draw(playerNameText);

            // Drawing of the player score text
            scoreText.setString("Score: " + to_string(this->score));
            window.draw(scoreText);

            // Drawing of the start game text
            window.draw(startGameText);

            // Drawing of the ip and port text
            window.draw(ipPortText);

            // Drawing of the player lives text
            window.draw(livesText);

            // Drawing of the ball depth text
            ballDepthText.setString("Ball depth: " + to_string(this->ballDepth));
            window.draw(ballDepthText);

            //Drawing of the blocks
            for (int i = 0; i < matrix.size(); i++) {
                string blockInfo = matrix[i];
                vector<string> block;

                stringstream ss(blockInfo);

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
                        blockShape.setTexture(&singleBlockTexture);
                    } else if (blockType == 2) {
                        if (blockResistance == 1) {
                            blockShape.setTexture(&doubleBlockR1Texture);
                        } else {
                            blockShape.setTexture(&doubleBlockTexture);
                        }
                    } else if (blockType == 3) {
                        if (blockResistance == 1) {
                            blockShape.setTexture(&tripleBlockR1texture);
                        } else if (blockResistance == 2) {
                            blockShape.setTexture(&tripleBlockR2Texture);
                        } else {
                            blockShape.setTexture(&tripleBlockTexture);
                        }
                    } else if (blockType == 4) {
                        blockShape.setTexture(&surpriseBlockTexture);
                    } else if (blockType == 5) {
                        blockShape.setTexture(&internBlockTexture);
                    } else if (blockType == 6) {
                        blockShape.setTexture(&depthBlockTexture);
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
