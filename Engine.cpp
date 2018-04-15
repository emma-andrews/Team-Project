#include "Engine.h"
#include <SFML/Graphics.hpp>

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
    window.display();
}

