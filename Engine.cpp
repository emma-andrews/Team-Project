#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

Engine::Engine() {
    score = 0;
    startup = true;
    flash = false;
    wait = false;
    //alreadyOpen = false;

    player = new Player();

    lTexture.loadFromFile("heart.png");
    lSprite.setTexture(lTexture);
    lSprite.setScale(4,4);

    coinBuffer.loadFromFile("coin_sound.wav");
    music.openFromFile("Main Theme.wav");
    music.setLoop(true);
    music.play();
    chestBuffer.loadFromFile("chest_sound.wav");
    jumpBuffer.loadFromFile("jump_sound.wav");

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
    remainText.setFont(font);
    openText.setFont(font);

    livesText.setString("Lives: ");
    finishText.setString("Level Complete!");
    endplatText.setString("FINISH");
    closeText.setString("Do you want to exit the game?\n\t\tYES: Y\tNO: N");
    stuckText.setString("Are you stuck?\nYES: Y\tNO: N");
    startText.setString("Please enter your name: ");
    openText.setString("EXIT OPENED!");

    levelText.setCharacterSize(30);//sets the size of the text
    livesText.setCharacterSize(30);
    scoreText.setCharacterSize(30);
    timeText.setCharacterSize(30);
    finishText.setCharacterSize(75);
    endplatText.setCharacterSize(25);
    closeText.setCharacterSize(40);
    stuckText.setCharacterSize(40);
    startText.setCharacterSize(50);
    remainText.setCharacterSize(30);
    openText.setCharacterSize(40);

    levelText.setFillColor(sf::Color::White);//sets the color of the text
    livesText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    timeText.setFillColor(sf::Color::White);
    finishText.setFillColor(sf::Color::White);
    endplatText.setFillColor(sf::Color(255, 162, 40));//rgb is an orange color
    closeText.setFillColor(sf::Color::White);
    stuckText.setFillColor(sf::Color::White);
    startText.setFillColor(sf::Color::White);
    remainText.setFillColor(sf::Color::White);
    openText.setFillColor(sf::Color(255, 162, 40));

    levelText.setPosition(20, 20);//sets the text at a position on the screen
    livesText.setPosition(20, 50);
    scoreText.setPosition(20, 80);
    timeText.setPosition(20, 110);
    finishText.setPosition(900, 500);//temporary position, needs to be updated to be somewhat in the middle of the screen
    endplatText.setPosition(1705, 170);
    closeText.setPosition(560, 540);
    stuckText.setPosition(560, 540);
    startText.setPosition(560, 540);
    remainText.setPosition(20, 140);
    openText.setPosition(560, 30);
}

void Engine::start() {//starts the game
    if (startup) {
        wait = true;
        playerName();
        startup = false;
    }
    sf::Clock clock;
    sf::Clock gameClock;

    levelFinished = false;//the level is not finished since it just started
    chestOpen = false;
    alreadyOpen = false;
    exitOpen = false;
    levelLost = false;
    coin.coins.clear();
    lGameTime = 0;
    wait = false;

    chest.resetSprite();
    level.generatePlat();//generates the random platforms of the level
    chest.setPosition(level.platforms[7].getPosition());


    for (int i = 0; i < 6; i++) {
        coin.coins.push_back(coin);
    }
    int n = 7;
    for (int i = 0; i < 6; i++) {
        n++;
        coin.coins[i].setPosition(level.platforms[n].getPosition());
    }

    int numbers[5];
    // Home generation
    enemies->generateHome(numbers);
    for (unsigned i = 0; i < 5; i++) {
        enemies[i].setHome(numbers[i]);
        enemies[i].spawn(level.platforms);
    }

    level.levelNum++;
    std::ostringstream s;
    s << "Level " << level.levelNum;
    levelText.setString(s.str());
    sf::Time gameTime = gameClock.restart();
    gameClock.restart();
    while (window.isOpen()) {//updates the game every frame
        sf::Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();//gets the elapsed time
        lGameTime = gameClock.getElapsedTime().asSeconds();
        input();//receives input from user during this frame
        update(dtAsSeconds, lGameTime);//calls for updates based on elapsed time and user input
        draw();//draws all sprites, texts, and shapes to the render window
    }
}

void Engine::nextLevel() {
    //set up for next level with message saying level complete, etc.
    std::cout << "Level " << level.levelNum << " completed!";
    std::cout << "Total score: " << score << std::endl;
    player->setPosition();
    for (int i = 0; i < 5; i++) {
        enemies[i].killed = false;
    }
    start();
}
bool open = true;
bool stuck = false;
bool jumpAlreadyPlayed;
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
            if (!jumpAlreadyPlayed) {
                jumpSound.setBuffer(jumpBuffer);
                jumpSound.setVolume(70.f);
                jumpSound.setLoop(false);
                jumpSound.play();
                jumpAlreadyPlayed = true;
            }
        }
        else {
            player->stopJump();
            jumpAlreadyPlayed = false;
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
            level.levelNum--;//did not pass level, counteracts increment in start()
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

void Engine::update(float dtAsSeconds, float totalTime) {
    int col = level.checkCollision(player->getSprite());
    player->update(dtAsSeconds, col, level.platforms);

    for (unsigned i = 0; i < coin.coins.size(); i++) {
        if (player->getSprite().getGlobalBounds().intersects(coin.coins[i].getSprite().getGlobalBounds())) {
            coin.coins.erase(coin.coins.begin() + i);
            player->setScore(100);
            // make a coin sound
            coinSound.setBuffer(coinBuffer);
            coinSound.setVolume(7.5f);
            coinSound.play();
        }
    }
    if (coin.coins.empty()) {
        exitOpen = true;
    }

    levelFinished = level.checkFinished(player->getSprite()) && coin.coins.size() == 0;

    if (!alreadyOpen) {
        chestOpen = player->checkInteraction(chest.getChestSprite());
        if (chestOpen) {
            chestSound.setBuffer(chestBuffer);
            chestSound.setVolume(30.f);
            chestSound.play();
        }
    }
    if (chestOpen) {
        chest.playAnimation();
        alreadyOpen = true;
    }
    for (int i = 0; i < coin.coins.size(); i++) {
        coin.coins[i].update();
    }
    chest.update();
    potion.update();
    int collision = 0;
    std::vector<sf::IntRect> rect;

    // Update the enemies status
    for (unsigned i = 0; i < 5; i++) {
        collision = enemies[i].update(player, dtAsSeconds, level.platforms);
        if (collision == 1) {
            if (isInvulnerable) {
                sf::Time timePassed = invulnerableTimer.getElapsedTime();
                if (timePassed.asSeconds() > 1.5f) {
                    isInvulnerable = false;
                }
            }
            else {
                player->setLives(player->getLives() - 1);
                isInvulnerable = true;
                invulnerableTimer.restart();
                if(player->rightLast) {
                    player->bounceBack(1);
                }
                else if (player->leftLast) {
                    player->bounceBack(2);
                }

            }
        }
        else if (collision == 2) {
            score += 150;
        }
    }
    score = player->getScore();
    std::ostringstream s1;
    s1 << "Score: " << score;
    scoreText.setString(s1.str());

    std::ostringstream s2;
    s2 << "Time: " << totalTime;
    timeText.setString(s2.str());

    std::ostringstream s3;
    s3 << "Jewels Remaining: " << coin.coins.size();
    remainText.setString(s3.str());

    playerLives = player->getLives();

    if (player->getLives() == 0) {
        levelLost = true;
    }
    //Clear, or else it infinitely populates
    pHearts.clear();
    int x = 110;
    for (int i = 0; i < playerLives; i++) {
        x += 40;
        lPosition.x = x;
        lPosition.y = 55;
        lSprite.setPosition(lPosition);
        pHearts.push_back(lSprite);
    }
    if (exitOpen) {
        if (flash) {
            openText.setFillColor(sf::Color::White);
            flash = false;
        }
        else if (!flash) {
            openText.setFillColor(sf::Color(255, 162, 40));
            flash = true;
        }
    }
    if (levelLost) {
        wait = true;
        gameOver();
    }
}

void Engine::draw() {//draws everything to the screen, called every frame in update
    if (!wait) {
        window.clear(sf::Color::White);//clears the window if anything is on it
        window.draw(backgroundSprite);//draws the background
        window.draw(player->getSprite());//the player sprite
        //window.draw(coin.getSprite());//the coin sprite
        window.draw(chest.getChestSprite());
        window.draw(potion.getSprite());

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
        for (unsigned i = 0; i < 5; i++) {
            window.draw(enemies[i].getSprite());
        }
        window.draw(levelText);//draws all the texts
        window.draw(livesText);
        window.draw(scoreText);
        window.draw(endplatText);
        window.draw(timeText);
        window.draw(remainText);
        if (exitOpen) {
            window.draw(openText);
        }
        if (!open) {//if the user enters esc to exit the game
            window.draw(closeText);
        }
        if (stuck) {
            window.draw(stuckText);
        }
        window.display();//displays everything that was drawn to the screen
    }

    if (levelFinished) {
        window.draw(finishText);
        //create a pause so that text is displayed and not immediately cleared
        window.display();
        window.clear();
        level.popPlat();
        nextLevel();

    }
}

void Engine::gameOver() {
    window.clear(sf::Color::Black);
    sf::Text overText;
    overText.setFont(font);
    overText.setFillColor(sf::Color::Red);
    overText.setString("GAME OVER\nExit?\nYes: Y\tNo: N");
    overText.setCharacterSize(40);
    overText.setPosition(800, 440);
    window.draw(overText);
    window.display();

    while (wait) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            wait = false;
            window.close();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            wait = false;
            window.clear();
            start();
        }
    }
}

void Engine::playerName() {
    sf::Text logoText;
    sf::Text tagText;
    sf::Text overText;
    sf::Text controlText;
    sf::Text nameText;
    sf::Text story;
    sf::Font font1;

    sf::Sprite playerGuy;
    sf::Texture pTexture;
    sf::IntRect pTemp(0,0,30,40);
    sf::Clock clock2;
    sf::Vector2f pPosition;
    std::vector<sf::IntRect> pRect;
    int frame = 0;

    window.clear(sf::Color::Black);

    pTexture.loadFromFile("player character sheet.png");
    playerGuy.setTexture(pTexture);
    playerGuy.setTextureRect(pTemp);
    pPosition.x = 450;
    pPosition.y = 700;
    playerGuy.setPosition(pPosition);
    playerGuy.setScale(4,4);

    overText.setFont(font);
    overText.setFillColor(sf::Color::Green);
    overText.setString("ENTER NAME: ");
    overText.setCharacterSize(40);
    overText.setPosition(600, 540);

    font1.loadFromFile("Demonized.ttf");
    logoText.setFont(font1);
    logoText.setCharacterSize(100);
    logoText.setString("RENEGADE");
    logoText.setFillColor(sf::Color::Red);
    logoText.setPosition(525, 305);

    tagText.setFont(font1);
    tagText.setCharacterSize(40);
    tagText.setString("Take back your glory \nand save the planet");
    tagText.setFillColor(sf::Color::Red);
    tagText.setPosition(530, 425);

    controlText.setFont(font);
    controlText.setFillColor(sf::Color::White);
    controlText.setCharacterSize(30);
    controlText.setString("CONTROLS:\n[A]: Move left\n[D]: Move right\n[Space]: Jump\n[Backspace]: Restart Level\n[Escape]: Exit Game");
    controlText.setPosition(30, 30);

    story.setFont(font);
    story.setString("Hundreds of years ago, the Earth was once prosperous and on the rise to universal success.\n"
                    "Jon Bao and his group of government spies discovered a new jewel on the planet of Xorcids,\n"
                    "which would one day be worth millions here on Earth. Xorcids was approximately four light \n"
                    "years away from Earth, giving Jon Bao and his team a long travel to and fro. When they \n"
                    "returned to Earth, the planet was destroyed; human life had ceased to exist and Earth's \n"
                    "only inhabitants were slow-minded but vicious enemies. From then on, Jon Bao had only one\n"
                    "mission and it wasn't about jewels or fame or glory. It was survival.");
    story.setPosition(200, 150);
    story.setFillColor(sf::Color::White);
    story.setCharacterSize(30);

    nameText.setFont(font);
    nameText.setFillColor(sf::Color::Green);
    nameText.setCharacterSize(40);
    nameText.setPosition(850, 540);

    sf::Clock clock1;
    while (wait) {
        window.draw(story);
        window.draw(playerGuy);
        window.display();
        if (clock1.getElapsedTime().asSeconds() > 1.0f) {//if intro seems long af, change 20.0f to 1.0f for your testing purposes
            wait = false;
            window.clear();
            window.display();
        }
    }

    window.clear(sf::Color::Black);
    window.draw(logoText);
    window.draw(tagText);
    window.draw(controlText);
    window.draw(overText);
    window.display();
    wait = true;
    std::string x;
    while (wait) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered && event.text.unicode != 32) {
                if (event.text.unicode == '\b') {
                    x.erase(x.size() - 1, 1);
                    nameText.setString(x);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    wait = false;
                    window.clear();
                }
                else {
                    x += (char)(event.text.unicode);
                    if (event.text.unicode < 128 && x.size() < 8) {
                        nameText.setString(x);
                    }
                }
                window.clear();
                window.display();
                window.draw(logoText);
                window.draw(overText);
                window.draw(tagText);
                window.draw(nameText);
                window.display();
            }
        }
    }
}