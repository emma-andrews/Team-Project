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

    levelText.setString("Level 1");//need to increase level count when they reach the next level
    livesText.setString("Lives Remaining: 3");//need to update when player is hit by an enemy
    levelText.setCharacterSize(30);
    livesText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::White);
    livesText.setFillColor(sf::Color::White);

    levelText.setPosition(20, 20);
    livesText.setPosition(20, 50);
}

void Engine::start() {//starts the game
    sf::Clock clock;
    while (window.isOpen()) {//updates the game every second
        sf::Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input() {//calculates user inputs and what actions are performed based on input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();//closes game when escape is pressed
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
}

void Engine::draw() {
    window.clear(sf::Color::White);
    window.draw(backgroundSprite);
    window.draw(player.getSprite());
    for (unsigned i = 0; i < level.platforms.size(); i++) {
        window.draw(level.platforms[i]);
    }
    window.draw(levelText);
    window.draw(livesText);
    window.display();
}

