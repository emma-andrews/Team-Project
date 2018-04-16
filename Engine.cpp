#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

Engine::Engine() {
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;//gets dimensions for game window
    resolution.y = sf::VideoMode::getDesktopMode().height;

    window.create(sf::VideoMode(resolution.x, resolution.y), "Team Project", sf::Style::Fullscreen);
    //creates the window
    backgroundTexture.loadFromFile("cyberpunk-street.png");//608 by 192
    backgroundSprite.setTexture(backgroundTexture);

    float xScale = resolution.x / 608;//set scales so background will stretch to fit any screen
    float yScale = resolution.y / 192;
    backgroundSprite.setScale(xScale, yScale);//sets scale of background image

    font.loadFromFile("VCR_OSD_MONO_1.001.ttf");//will need to create a font folder in project so non-windows users can see it
    levelText.setFont(font);
    livesText.setFont(font);
    finishText.setFont(font);
    endplatText.setFont(font);

    levelText.setString("Level 1");//need to increase level count when they reach the next level
    livesText.setString("Lives Remaining: 3");//need to update when player is hit by an enemy
    finishText.setString("Level Complete!");
    endplatText.setString("FINISH");

    levelText.setCharacterSize(30);
    livesText.setCharacterSize(30);
    finishText.setCharacterSize(75);
    endplatText.setCharacterSize(25);

    levelText.setFillColor(sf::Color::White);
    livesText.setFillColor(sf::Color::White);
    finishText.setFillColor(sf::Color::White);
    endplatText.setFillColor(sf::Color(255, 162, 40));

    levelText.setPosition(20, 20);
    livesText.setPosition(20, 50);
    finishText.setPosition(900, 500);//temporary position, needs to be updated to be somewhat in the middle of the screen
    endplatText.setPosition(1705, 170);
}

void Engine::start() {//starts the game
    sf::Clock clock;
    levelFinished = false;
    level.generatePlat();
    while (window.isOpen()) {//updates the game every second
        sf::Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::nextLevel() {
    //set up for next level with message saying level complete, etc.

    start();
}

void Engine::input() {//calculates user inputs and what actions are performed based on input
    sf::Clock ingameClock;
    sf::Text closeText;
    closeText.setFont(font);
    closeText.setString("Do you want to exit the game?\nYES: Y\tNO: N");
    closeText.setCharacterSize(40);
    closeText.setPosition(960, 540);
    closeText.setFillColor(sf::Color::White);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
//        window.draw(closeText);
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
//            window.close();
//        }
//        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
//            window.clear();
//            draw();
//        }
        //closes game when escape is pressed
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.moveLeft();//moves left when A is pressed
    }
    else {
        player.stopLeft();//does not move left when anything other than A is pressed
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.moveRight();//moves right when D is pressed
    }
    else {
        player.stopRight();//does not move right when anything other than D is pressed
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player.jump();
    }
    else {
        player.stopJump();
    }
}

void Engine::update(float dtAsSeconds) {
    int col = level.checkCollision(player.getSprite());
    player.update(dtAsSeconds, col, level.platforms);
    levelFinished = level.checkFinished(player.getSprite());
}

void Engine::draw() {//draws everything to the screen, called every second in update
    window.clear(sf::Color::White);
    window.draw(backgroundSprite);
    window.draw(player.getSprite());

    for (unsigned i = 0; i < level.platforms.size(); i++) {
        window.draw(level.platforms[i]);
    }

    window.draw(levelText);
    window.draw(livesText);
    window.draw(endplatText);
    window.display();

    if (levelFinished) {
        window.draw(finishText);
        //create a pause so that text is displayed and not immediately cleared
        window.clear();
        level.popPlat();
        nextLevel();
    }
}