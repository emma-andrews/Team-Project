#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

Engine::Engine() {
    score = 0;
    startup = true;

    lTexture.loadFromFile("heart.png");
    lSprite.setTexture(lTexture);
    lSprite.setScale(4,4);

    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;//gets dimensions for game window
    resolution.y = sf::VideoMode::getDesktopMode().height;

    window.create(sf::VideoMode(resolution.x, resolution.y), "Team Project", sf::Style::Resize);//creates render window which the game will be displayed on
    //creates the window
    backgroundTexture.loadFromFile("cyberpunk-street.png");//608 by 192
    backgroundSprite.setTexture(backgroundTexture);

    float xScale = resolution.x / 608;//set scales so background will stretch to fit any screen
    float yScale = resolution.y / 192;
    backgroundSprite.setScale(xScale, yScale);//sets scale of background image

    font.loadFromFile("VCR_OSD_MONO_1.001.ttf");//sets all texts used on the screen to this font
    levelText.setFont(font);
    livesText.setFont(font);
    scoreText.setFont(font);
    finishText.setFont(font);
    endplatText.setFont(font);
    timeText.setFont(font);
    closeText.setFont(font);
    stuckText.setFont(font);
    startText.setFont(font);

    livesText.setString("Lives: ");
    finishText.setString("Level Complete!");
    endplatText.setString("FINISH");
    closeText.setString("Do you want to exit the game?\n\t\tYES: Y\tNO: N");
    stuckText.setString("Are you stuck?\nYES: Y\tNO: N");
    startText.setString("Please enter your name: ");

    levelText.setCharacterSize(30);//sets the size of the text
    livesText.setCharacterSize(30);
    scoreText.setCharacterSize(30);
    timeText.setCharacterSize(30);
    finishText.setCharacterSize(75);
    endplatText.setCharacterSize(25);
    closeText.setCharacterSize(40);
    stuckText.setCharacterSize(40);
    startText.setCharacterSize(50);

    levelText.setFillColor(sf::Color::White);//sets the color of the text
    livesText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    timeText.setFillColor(sf::Color::White);
    finishText.setFillColor(sf::Color::White);
    endplatText.setFillColor(sf::Color(255, 162, 40));//rgb is an orange color
    closeText.setFillColor(sf::Color::White);
    stuckText.setFillColor(sf::Color::White);
    startText.setFillColor(sf::Color::White);

    levelText.setPosition(20, 20);//sets the text at a position on the screen
    livesText.setPosition(20, 50);
    scoreText.setPosition(20, 80);
    timeText.setPosition(20, 110);
    finishText.setPosition(900, 500);//temporary position, needs to be updated to be somewhat in the middle of the screen
    endplatText.setPosition(1705, 170);
    closeText.setPosition(560, 540);
    stuckText.setPosition(560, 540);
    startText.setPosition(560, 540);
}

void Engine::start() {//starts the game
//    if (startup) {
//        window.clear(sf::Color::Black);
//        window.draw(startText);
//        window.display();
//    }
    sf::Clock clock;
    sf::Clock gameClock;
    levelFinished = false;//the level is not finished since it just started
    chestOpen = false;

    level.generatePlat();//generates the random platforms of the level
    chest.setPosition(level.platforms[7].getPosition());
    sf::Time gameTime = gameClock.restart();

    for (int i = 0; i < 6; i++) {
        coin.coins.push_back(coin);
    }
    int n = 7;
    for (int i = 0; i < 6; i++) {
        n++;
        coin.coins[i].setPosition(level.platforms[n].getPosition());
    }

    level.levelNum++;
    std::ostringstream s;
    s << "Level " << level.levelNum;
    levelText.setString(s.str());

    while (window.isOpen()) {//updates the game every frame
        sf::Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();//gets the elapsed time
        lGameTime += gameTime.asSeconds();
        input();//receives input from user during this frame
        update(dtAsSeconds, lGameTime);//calls for updates based on elapsed time and user input
        draw();//draws all sprites, texts, and shapes to the render window
    }
}

void Engine::nextLevel() {
    //set up for next level with message saying level complete, etc.
    player->setPosition();
    start();
}
bool open = true;
bool stuck = false;
void Engine::input() {//calculates user inputs and what actions are performed based on input
    sf::Event event;
    while (window.pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            //window.close();
            open = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            stuck = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player->moveLeft();//moves left when A is pressed
        }
        else {
            player->stopLeft();//does not move left when anything other than A is pressed
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player->moveRight();//moves right when D is pressed
        }
        else {
            player->stopRight();//does not move right when anything other than D is pressed
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player->jump();
        }
        else {
            player->stopJump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && !open) {
            window.close();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !open) {
            open = true;
            window.clear();
            draw();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && stuck) {
            stuck = false;
            window.clear();
            level.popPlat();
            nextLevel();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && stuck) {
            stuck = false;
            window.clear();
            draw();
        }
    }
}
bool alreadyOpen = false;
void Engine::update(float dtAsSeconds, float totalTime) {
    int col = level.checkCollision(player->getSprite());
    player->update(dtAsSeconds, col, level.platforms);
    levelFinished = level.checkFinished(player->getSprite());
    if (!alreadyOpen) {
        chestOpen = player->checkInteraction(chest.getChestSprite());
    }
    if (chestOpen) {
        chest.playAnimation();
        alreadyOpen = true;
    }
    for (int i = 0; i < coin.coins.size(); i++) {
        coin.coins[i].update();
    }
    chest.update();

    score = player->getScore();
    std::ostringstream s1;
    s1 << "Score: " << score;
    scoreText.setString(s1.str());

    std::ostringstream s2;
    s2 << "Time: " << totalTime;
    timeText.setString(s2.str());

    playerLives = player->getLives();

    int x = 110;
    for (int i = 0; i < playerLives; i++) {
        x += 40;
        lPosition.x = x;
        lPosition.y = 55;
        lSprite.setPosition(lPosition);
        pHearts.push_back(lSprite);
    }
}

void Engine::draw() {//draws everything to the screen, called every frame in update
    window.clear(sf::Color::White);//clears the window if anything is on it
    window.draw(backgroundSprite);//draws the background
    window.draw(player->getSprite());//the player sprite
    //window.draw(coin.getSprite());//the coin sprite
    window.draw(chest.getChestSprite());

    for (unsigned i = 0; i < level.platforms.size(); i++) {
        window.draw(level.platforms[i]);//each individual platform that was generated
    }
    //draw hearts here like above for platforms
    for (unsigned i = 0; i < pHearts.size(); i++) {
        window.draw(pHearts[i]);
    }
    for (unsigned i = 0; i < coin.coins.size(); i++) {
        window.draw(coin.coins[i].getSprite());
    }
    window.draw(levelText);//draws all the texts
    window.draw(livesText);
    window.draw(scoreText);
    window.draw(endplatText);
    window.draw(timeText);

    if(!open){//if the user enters esc to exit the game
        window.draw(closeText);
    }
    if (stuck) {
        window.draw(stuckText);
    }
    window.display();//displays everything that was drawn to the screen

    if (levelFinished) {
        window.draw(finishText);
        //create a pause so that text is displayed and not immediately cleared
        window.display();
        window.clear();
        level.popPlat();
        nextLevel();
    }
}