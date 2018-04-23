#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

Engine::Engine() {
    score = 0;//initializes score to 0
    startup = true;//initializes startup to true
    flash = false;//initializes flash to false
    wait = false;//initializes wait to false
    //alreadyOpen = false;
    retry = false;

    player = new Player();//instantiates the player class

    lTexture.loadFromFile("heart.png");//loads the texture for the lives and sets it for the sprite for the lives
    lSprite.setTexture(lTexture);
    lSprite.setScale(4,4);//scales it by 4

    coinBuffer.loadFromFile("coin_sound.wav");//loads all the music files that are going to be played throughout the game
    music.openFromFile("Main Theme.wav");
    gameOverTheme.openFromFile("Game Over.WAV");
    startTheme.openFromFile("Story.wav");
    startTheme.setLoop(true);//sets the opening music to loop and play
    startTheme.play();

    chestBuffer.loadFromFile("chest_sound.wav");//loads other music files that will be player throughout the game
    jumpBuffer.loadFromFile("jump_sound.wav");

    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;//gets dimensions for game window
    resolution.y = sf::VideoMode::getDesktopMode().height;

    window.create(sf::VideoMode(resolution.x, resolution.y), "Team Project", sf::Style::Resize);//creates render window which the game will be displayed on
    //creates the window, most windows will use a resolution of 1920 by 1080

    backgroundTexture.loadFromFile("cyberpunk-street.png");//608 by 192 file
    backgroundSprite.setTexture(backgroundTexture);//sets the texture of the background to the image

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

    livesText.setString("Lives: ");//sets the strings for the texts that will not change throughout the game
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
    finishText.setPosition(900, 500);
    endplatText.setPosition(1705, 170);
    closeText.setPosition(560, 540);
    stuckText.setPosition(560, 540);
    startText.setPosition(560, 540);
    remainText.setPosition(20, 140);
    openText.setPosition(560, 30);
}

void Engine::start() {//starts the game
    if (startup) {//will only be called when the game is first launched
        wait = true;//pauses the game
        playerName();//calls on the logo screen and story screen to appear
        startTheme.stop();//stops the start screen music from playing
        //main background music plays
        startup = false;//cannot call startup again during the game
    }
    if (retry) {
        player->setLives(3);//set the player lives to 3
        level.popPlat();//clear the platforms in case anything was in it
        level.levelNum = 0;//set the level number back to zero
    }
    sf::Clock clock;//clocks start to run
    sf::Clock gameClock;

    music.setLoop(true);//main background music is able to be looped
    music.play();

    levelFinished = false;//the level is not finished since it just started
    chestOpen = false;//the chest is not open since the level just started
    alreadyOpen = false;//the chest is not already open
    isInvulnerable = false;//player is not invulnerable
    exitOpen = false;//the exit is not open
    levelLost = false;//the level is not lost
    coin.coins.clear();//the coin vector is cleared to avoid any vector
    lGameTime = 0;//the game time initially is 0
    wait = false;//no longer waiting
    activated = false;//potion has not been activated



    chest.resetSprite();//resetting the chest sprite so it is not opened when a new level begins
    level.generatePlat();//generates the random platforms of the level
    chest.setPosition(level.platforms[7].getPosition());//sets the chest onto the 7th platform in the vector of platforms

    potionSpawn = (rand() % 100) + 1;//potion has a random spawn from 1 to 101
    potionHome = (rand() % 17) + 2;//potion home is random from the second platform to the 17th

    for (int i = 0; i < 6; i++) {//creates a vector containing 6 coins
        coin.coins.push_back(coin);
    }
    int n = 7;
    for (int i = 0; i < 6; i++) {//sets the position of the coins to platforms 8-14
        n++;
        coin.coins[i].setPosition(level.platforms[n].getPosition());
    }

    int numbers[5];
    // Home generation of the enemies
    enemies->generateHome(numbers);
    for (unsigned i = 0; i < 5; i++) {
        enemies[i].setHome(numbers[i]);//sets the home of each enemy to one of the platforms in numbers
        enemies[i].spawn(level.platforms);//spawns the enemy on the platform that it is home to
    }

    level.levelNum++;//increases the level number
    std::ostringstream s;//create a stringstream so that the text on the screen will change depending on what level the player is currently on
    s << "Level " << level.levelNum;
    levelText.setString(s.str());

    sf::Time gameTime = gameClock.restart();//keeps track of the total game time
    gameClock.restart();//starts clock at first instance of loop for the game
    while (window.isOpen()) {//updates the game every frame
        sf::Time dt = clock.restart();//restarts the clock to get the time elapsed between frames
        float dtAsSeconds = dt.asSeconds();//gets the elapsed time
        lGameTime = gameClock.getElapsedTime().asSeconds();//game time is set to the elapsed time since the game clock was started
        input();//receives input from user during this frame
        update(dtAsSeconds, lGameTime);//calls for updates based on elapsed time and user input
        draw();//draws all sprites, texts, and shapes to the render window
    }
}

void Engine::nextLevel() {
    //sets up the next level, printing out the level number and total score to the console so the player can see how they did after completing the game
    std::cout << "Level " << level.levelNum << " completed!";
    std::cout << " Total score: " << score << std::endl;
    player->setPosition();//set the position back to the initial position
    for (int i = 0; i < 5; i++) {
        enemies[i].killed = false;//if any enemies were killed during the previous level they come back to lide
    }
    start();//starts the game again
}
bool open = true;//window is currently open
bool stuck = false;//player is currently not stuck
bool jumpAlreadyPlayed;//sound has not been played yet
void Engine::input() {//calculates user inputs and what actions are performed based on input
    sf::Event event;
    while (window.pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            //if the user presses escape, the window is trying to be closed, and open is set to false
            open = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            //if the user enters backspace, they might be stuck, so stuck is set to true
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
            player->jump();//player is trying to jump when they press space
            if (!jumpAlreadyPlayed) {//if the jump sound has not been played (prevents looping of sound when space is held)
                jumpSound.setBuffer(jumpBuffer);//play the jump sound
                jumpSound.setVolume(70.f);
                jumpSound.setLoop(false);
                jumpSound.play();
                jumpAlreadyPlayed = true;//set to true as it has already been played
            }
        }
        else {
            player->stopJump();//player is not trying to jump
            jumpAlreadyPlayed = false;//and thus the jump sound has not already been player
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && !open) {
            window.close();//if the user presses escape and then y, they want to exit the game and the window closes
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !open) {
            open = true;//if the user presses escape and then n, they do not want to exit the game
            window.clear();//the window is then cleared and draw is called upon
            draw();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && stuck) {
            //if the player enters backspace and then yes, meaning they are stuck
            stuck = false;//sets stuck back to false
            level.levelNum--;//did not pass level, counteracts increment in start()
            window.clear();//clears the window
            level.popPlat();//empties the vector of platforms to be regenerated
            nextLevel();//advances to "next level", but its more of a redo
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && stuck) {
            //if the user enters backspace and then n, meaning they are not stuck
            stuck = false;//sets stuck back to false
            window.clear();//clears the window and then calls on draw
            draw();
        }
    }
}

void Engine::update(float dtAsSeconds, float totalTime) {
    //updates all sprites and elements in the game every frame
    int col = level.checkCollision(player->getSprite());//if a collision occurs between the player and a platform, get the platform numebr they are colliding with
    player->update(dtAsSeconds, col, level.platforms);//updates the player

    for (unsigned i = 0; i < coin.coins.size(); i++) {
        if (player->getSprite().getGlobalBounds().intersects(coin.coins[i].getSprite().getGlobalBounds())) {
            coin.coins.erase(coin.coins.begin() + i);//erases the coin that the player collides with from the vector as they have "picked" it up
            player->setScore(player->getScore() + 100);//increases score by 100
            // make a coin sound, plays when user picks up coin
            coinSound.setBuffer(coinBuffer);
            coinSound.setVolume(7.5f);
            coinSound.play();
        }
    }
    if (coin.coins.empty()) {
        //if there are no more coins on the level, the exit is then opened so that the player can advance to the next level
        exitOpen = true;
    }
    //checks if the level is finished
    levelFinished = level.checkFinished(player->getSprite()) && coin.coins.size() == 0;

    if (!alreadyOpen) {//if the chest is not already open
        chestOpen = player->checkInteraction(chest.getChestSprite());//checks the player interaction with the chest
        if (chestOpen) {//if the chest is open, play the chest sound
            chestSound.setBuffer(chestBuffer);
            chestSound.setVolume(30.f);
            chestSound.play();
        }
    }
    if (chestOpen) {//if the chest is open
        chest.playAnimation();//play the animation
        alreadyOpen = true;//chest has now been opened
    }
    for (int i = 0; i < coin.coins.size(); i++) {
        coin.coins[i].update();//updates each coin
    }
    chest.update();//updates the chest
    int collision = 0;//collision is set to 0 initially
    std::vector<sf::IntRect> rect;


    if (potionSpawn % 3 == 0 && !activated) {
        potion.update(level.platforms[potionHome].getPosition());//updates the potion
        potion.playAnimation();//plays the animation for the potion
        if (potion.potionCollide(player->getSprite()) > 0) {//if the user collides with the potion
            potion.rewardTimer.restart();//restarts the reward timer
            player->setSpeed(800);//sets the speed of the player to 800
            potion.potionHide();//moves the potion offscreen
            activated = true;//potion has been activated for the level
        }

        if (potion.rewardTimer.getElapsedTime().asSeconds() > 2.0f) {
            //if the time elapsed since interacting with the potion has been two seconds
            player->setSpeed(400);//reset the speed back to 400
        }
    }

    // Update the enemies status
    for (unsigned i = 0; i < 5; i++) {
        collision = enemies[i].update(player, dtAsSeconds, level.platforms);
        //checks collision with the player character
        if (collision == 1) {//if collision is one, the player was hurt
            if (isInvulnerable) {//if they are invulnerable
                sf::Time timePassed = invulnerableTimer.getElapsedTime();//get the time elapsed since becoming invulnerable
                if (timePassed.asSeconds() > 1.5f) {
                    //if the time spent invulnerable is greater than 1.5 seconds
                    isInvulnerable = false;//player is no longer invulnerable
                }
            }
            else {
                //otherwise the player is not invulnerable and loses a life
                player->setLives(player->getLives() - 1);
                isInvulnerable = true;//they are now invulnerable
                invulnerableTimer.restart();//restarts the invulnerable timer
                if(player->rightLast) {
                    //bounce back off the enemy in the left direction if they were headed right when they collided with the enemy
                    player->bounceBack(1);
                }
                else if (player->leftLast) {
                    //bounce back off the enemy in the right direction if they were headed left when they collided with the enemy
                    player->bounceBack(2);
                }

            }
        }
        else if (collision == 2) {
            //if the player kills an enemy, increase the score by 150
            player->setScore(player->getScore() + 150);
        }
    }

    //create a string stream to change the text of the total score in game
    score = player->getScore();
    std::ostringstream s1;
    s1 << "Score: " << score;
    scoreText.setString(s1.str());

    //create a string stream to change the text of the total time in game
    std::ostringstream s2;
    s2 << "Time: " << totalTime;
    timeText.setString(s2.str());

    //create a string stream to change the number of jewels remaining in the level in game
    std::ostringstream s3;
    s3 << "Jewels Remaining: " << coin.coins.size();
    remainText.setString(s3.str());

    playerLives = player->getLives();

    if (player->getLives() == 0) {
        //if the player is at 0 lives, they have lost the game
        levelLost = true;
    }
    //Clear, or else it infinitely populates
    pHearts.clear();

    int x = 110;//initial starting position for the hearts representing the number of lives
    for (int i = 0; i < playerLives; i++) {
        x += 40;//increase x by 40
        lPosition.x = x;//set the position of the hearts to x
        lPosition.y = 55;//and the y position of the "Lives: " text
        lSprite.setPosition(lPosition);
        pHearts.push_back(lSprite);//pushes the lives into the vector
    }

    if (exitOpen) {
        //if the exit is open after all the jewels have been collected
        if (flash) {
            //flash that exit is opened by alternating between white and orange fill colors
            openText.setFillColor(sf::Color::White);
            flash = false;
        }
        else if (!flash) {
            openText.setFillColor(sf::Color(255, 162, 40));
            flash = true;
        }
    }
    if (levelLost) {
        //if the player reaches zero lives and the game is over
        wait = true;//pause the game
        music.stop();//stop the background music
        gameOverTheme.setLoop(true);//play the game over music
        gameOverTheme.play();
        gameOver();
    }
}

void Engine::draw() {//draws everything to the screen, called every frame in update
    if (!wait) {//while the game is not paused during menus
        window.clear(sf::Color::White);//clears the window if anything is on it
        window.draw(backgroundSprite);//draws the background
        window.draw(player->getSprite());//the player sprite
        window.draw(chest.getChestSprite());//the chest sprite

        if (potionSpawn % 3 == 0) {
            window.draw(potion.getSprite());//the potion sprite
        }

        for (unsigned i = 0; i < level.platforms.size(); i++) {
            window.draw(level.platforms[i]);//each individual platform that was generated
        }

        for (unsigned i = 0; i < pHearts.size(); i++) {
            window.draw(pHearts[i]);//each of the lives represented by a heart
        }

        for (unsigned i = 0; i < coin.coins.size(); i++) {
            window.draw(coin.coins[i].getSprite());//each of the jewels
        }

        for (unsigned i = 0; i < 5; i++) {
            window.draw(enemies[i].getSprite());//each of the enemies
        }
        window.draw(levelText);//draws all the texts
        window.draw(livesText);
        window.draw(scoreText);
        window.draw(endplatText);
        window.draw(timeText);
        window.draw(remainText);

        if (exitOpen) {
            window.draw(openText);//if the exit is open the exit opened text will be displayed
        }

        if (!open) {//if the user enters escape to exit the game
            window.draw(closeText);
        }

        if (stuck) {//if the user enters backspace to generate a new level due to being stuck
            window.draw(stuckText);
        }
        window.display();//displays everything that was drawn to the screen
    }

    if (levelFinished) {
        //if the level was finished draw the finish text, then advance to the next level
        window.draw(finishText);
        window.display();
        window.clear();
        level.popPlat();//clear the platform vectors to generate a brand new level
        nextLevel();

    }
}

void Engine::gameOver() {
    //called if the player loses all of their lives
    window.clear(sf::Color::Black);//clears the screen to black
    sf::Text overText;//sets text to font, red, etc.
    overText.setFont(font);
    overText.setFillColor(sf::Color::Red);
    overText.setString("GAME OVER\nExit?\nYes: Y\tNo: N");
    overText.setCharacterSize(40);
    overText.setPosition(800, 440);
    window.draw(overText);//draws the text to the screen and displays it
    window.display();

    while (wait) {
        //loops until the user decides on an action
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            //if the press y, the want to exit the game
            wait = false;
            window.close();//window is closed
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            //if they press n, they want to restart the game
            gameOverTheme.stop();//stops the music
            wait = false;
            window.clear();//clears the window
            retry = true;//retrying the game
            start();//start game over
        }
    }
}

void Engine::playerName() {
    //initial screen that pops up when starting the game for the first time
    sf::Text logoText;
    sf::Text tagText;
    sf::Text overText;
    sf::Text controlText;
    sf::Text nameText;
    sf::Text story;
    sf::Font font1;

    sf::Sprite playerGuy;
    sf::Texture pTexture;
    sf::IntRect pTemp(0,0,30,40);//creates a sprite of the player character to be displayed on beginning screen
    sf::Clock clock2;//starts a clock
    sf::Vector2f pPosition;
    std::vector<sf::IntRect> pRect;

    window.clear(sf::Color::Black);//clears the screen to black

    pTexture.loadFromFile("player character sheet.png");
    playerGuy.setTexture(pTexture);//sets the player to the first idle frame
    playerGuy.setTextureRect(pTemp);
    pPosition.x = 450;//sets the position of the player
    pPosition.y = 700;
    playerGuy.setPosition(pPosition);
    playerGuy.setScale(4,4);//scales the player by 4

    overText.setFont(font);//sets the font, color, size, and position of the text
    overText.setFillColor(sf::Color::Green);
    overText.setString("ENTER NAME: ");
    overText.setCharacterSize(40);
    overText.setPosition(600, 540);

    font1.loadFromFile("Demonized.ttf");//sets the font, color, size, and position of the text
    logoText.setFont(font1);
    logoText.setCharacterSize(100);
    logoText.setString("RENEGADE");
    logoText.setFillColor(sf::Color::Red);
    logoText.setPosition(525, 305);

    tagText.setFont(font1);//sets the font, color, size, and position of the text
    tagText.setCharacterSize(40);
    tagText.setString("Take back your glory \nand save the planet");
    tagText.setFillColor(sf::Color::Red);
    tagText.setPosition(530, 425);

    controlText.setFont(font);//sets the font, color, size, and position of the text
    controlText.setFillColor(sf::Color::White);
    controlText.setCharacterSize(30);
    controlText.setString("CONTROLS:\n[A]: Move left\n[D]: Move right\n[Space]: Jump\n[Backspace]: Restart Level\n[Escape]: Exit Game");
    controlText.setPosition(30, 30);

    story.setFont(font);//sets the font, color, size, and position of the text
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

    nameText.setFont(font);//sets the font, color, size, and position of the text
    nameText.setFillColor(sf::Color::Green);
    nameText.setCharacterSize(40);
    nameText.setPosition(850, 540);

    sf::Clock clock1;//starts the clock
    while (wait) {
        //loops until the menu is exited by making wait false
        window.draw(story);//draws the story and the player to the screen and displays them
        window.draw(playerGuy);
        window.display();
        if (clock1.getElapsedTime().asSeconds() > 20.0f) {
            //story will stay on the screen for 20 seconds so the player has enough time to read it
            wait = false;//done waiting
            window.clear();//clear the screen and display it so it processes the clear
            window.display();
        }
    }

    window.clear(sf::Color::Black);//clears the screen to black
    window.draw(logoText);//draws the texts
    window.draw(tagText);
    window.draw(controlText);
    window.draw(overText);
    window.display();//displays the texts
    wait = true;//wait is now true
    std::string x;//string for player name
    while (wait) {
        //until user hits enter to begin the game
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered && event.text.unicode != 32) {
                if (event.text.unicode == '\b') {
                    //if they enter backspace, erase the last letter entered into the name space
                    x.erase(x.size() - 1, 1);
                    nameText.setString(x);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    //player is now ready to start game, exit the loop and clear the screen
                    wait = false;
                    window.clear();
                }
                else {
                    //any other input is considered to be a part of the name being entered
                    x += (char)(event.text.unicode);
                    if (event.text.unicode < 128 && x.size() < 8) {
                        //as long as it is a standard unicode character and the size of the string is not greater than 8
                        nameText.setString(x);
                    }
                }
                window.clear();//clears the window and displays it to process the clear
                window.display();
                window.draw(logoText);//draws the texts and displays it
                window.draw(overText);
                window.draw(tagText);
                window.draw(nameText);
                window.display();
            }
        }
    }
}