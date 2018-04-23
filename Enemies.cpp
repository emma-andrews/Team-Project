#include <SFML/Graphics.hpp>
#include "Enemies.h"
#include "Levels.h"
#include <vector>
#include <cmath>
#include <iostream>

const float maxY = 2.5f;
const float gravity = 30.0f;

// Default constructor for monsters
Enemies::Enemies() {
    // Give enemies a variable speed, with 25 to 50
    eSpeed = (rand() % 25) + 25;
    rFrame = 0;//sets animation frames to 0 initially
    lFrame = 0;
    irFrame = 0;
    ilFrame = 0;
    jFrame = 0;
    killed = false;//enemy has not been killed yet
    sf::IntRect batRect(0, 0, 50, 30);//sets the original frames of each enemy type
    sf::IntRect slimeRect(0,0,30,27);
    sf::IntRect slime2Rect(0, 0, 30, 32);
    int chance;
    chance = rand() % 3 + 1;//1 in 3 chance of spawing each type of monster

    if (chance == 1) {
        //if the chance is 1, slime type 1 is generated
        sTexture.loadFromFile("slime sheet.png");//sets the texture to the sprite sheet and the rectangle to the initial frame
        eSprite.setTextureRect(slimeRect);
        eSprite.setTexture(sTexture);
        eSprite.setScale(2,2);//scales it by 2
        slime = true;//it is a slime
        bat = false;
        slime2 = false;
    }

    else if (chance == 2) {
        //if the chance is 2, bat is generated
        bTexture.loadFromFile("bat sheet.png");//sets the texture to the sprite sheet and the rectangle to the initial frame
        eSprite.setTexture(bTexture);
        eSprite.setTextureRect(batRect);
        eSprite.setScale(2,2);//scales it by 2
        bat = true;//it is a bat
        slime = false;
        slime2 = false;
    }

    else if (chance == 3) {
        ssTexture.loadFromFile("slime 2 sheet.png");//sets the texture to the sprite sheet and the rectangle to the initial frame
        eSprite.setTexture(ssTexture);
        eSprite.setTextureRect(slime2Rect);
        eSprite.setScale(2,2);//scales it by 2
        slime2 = true;//it is a slime 2
        slime = false;
        bat = false;
    }
}

sf::Sprite Enemies::getSprite() {
    return eSprite;//returns the sprite of the enemy
}

// Function to set the position to be on top of the home platform
void Enemies::setPosition(std::vector<sf::RectangleShape> plats) {
    ePosition.x = plats[home].getPosition().x + plats[home].getGlobalBounds().width/2
                  - eSprite.getGlobalBounds().width/2;
    ePosition.y = plats[home].getPosition().y - eSprite.getGlobalBounds().height;
    eSprite.setPosition(ePosition);
}

// Spawn function to initialize the location and decide a starting direction for the monster
void Enemies::spawn(std::vector<sf::RectangleShape> plats) {
    ePosition.x = plats[home].getPosition().x + plats[home].getGlobalBounds().width/2
                  - eSprite.getGlobalBounds().width/2;
    ePosition.y = plats[home].getPosition().y - eSprite.getGlobalBounds().height;
    eSprite.setPosition(ePosition);
    startDir = (int) ePosition.x % 2;
}

// Setter method for home location
void Enemies::setHome(int home) {
    this->home = home;
}

int Enemies::checkCollision(sf::Sprite player, bool invulnerable) {
    float ydifference;
    float xdifference;
    ydifference = eSprite.getGlobalBounds().top - (player.getGlobalBounds().top + player.getGlobalBounds().height);
    xdifference = (eSprite.getGlobalBounds().left + eSprite.getGlobalBounds().width) - (player.getGlobalBounds().left + player.getGlobalBounds().width);
    if (ydifference <= 10 && ydifference >= -10 && xdifference <= 20 && xdifference >= -20 && !invulnerable) {
        //if the player jumps on top of the enemy, it is killed
        return 2;
    }
    else if (player.getGlobalBounds().intersects(eSprite.getGlobalBounds()) && !invulnerable) {
        //if the player intersects the enemy but it is not by jumping on top, they lose a life
        return 1;
    }
    else {
        //otherwise no collision takes place
        return 0;
    }
}
int x = 2100;
int y = 1500;
int Enemies::update(Player *player, float elapsedTime, std::vector<sf::RectangleShape> plats) {
    // Behavior decision

    if (!killed) {//while they are not killed, engage the player
        engage(elapsedTime, player->getSprite());
    }
    int collision = checkCollision((*player).getSprite(), player->invulnerable);//checks if the enemy was killed by the player
    int pX = (*player).getX();
    int pY = (*player).getY();
    if (!killed) {//while they are not killed by the player
        if (abs(pX - (int) ePosition.x) < 100) {
            if (abs(pY - (int) ePosition.y) < 100) {
                startDir = pX - ePosition.x < 0 ? 0 : 1;
                patrol(plats, elapsedTime);//patrol the platforms in a certain direction
            }
            else {
                patrol(plats, elapsedTime);
            }
        }
        else {
            patrol(plats, elapsedTime);
        }
    }

    // Position Verification to prevent weird bug on new level
    if (collision == 2) {
        //if the enemy was killed, set the enemy to appear of the screen to act as if it were dead
        ePosition.x = x;//2100 initially
        ePosition.y = y;//1500 initially
        eSprite.setPosition(ePosition);
        x += 100;//increase the x and y
        y += 100;
        killed = true;//the enemy has been killed
        player->invulnerable = true;//the player is invulnerable
        return 2;
    }
    else if (ePosition.x < plats[home].getPosition().x - 20 && !killed) {
        //spawn on the platform in case there is overlap in platforms
        spawn(plats);
    }
    else if (ePosition.x > plats[home].getPosition().x + plats[home].getGlobalBounds().width + 20 - eSprite.getGlobalBounds().width && !killed) {
        //spawn on the platform in case there is overlap in platforms
        spawn(plats);
    }

    if (slime && eAniClock.getElapsedTime().asSeconds() > 0.3f) {//changes the frame every 0.3 seconds
        eAniRect = monAnim.slime();//sets a vector to contain all of the frames of the animation
        eSprite.setTextureRect(eAniRect[rFrame]);//sets the rectangle texture to the current frame
        rFrame++;//increases the frame count by one
        if (rFrame >= eAniRect.size() - 1) {//if the frame count is greater or equal to the size of the animation vector
            rFrame = 0;//reset the frame count to zero to create a looping animation
        }
        eAniClock.restart();//restarts the clock
    }
    else if (bat && eAniClock.getElapsedTime().asSeconds() > 0.3f) {//changes the frame every 0.3 seconds
        eAniRect = monAnim.batFly();//sets a vector to contain all of the frames of the animation
        eSprite.setTextureRect(eAniRect[lFrame]);//sets the rectangle texture to the current frame
        lFrame++;//increases the frame count by one
        if (lFrame >= eAniRect.size() - 1) {//if the frame count is greater or equal to the size of the animation vector
            lFrame = 0;//reset the frame count to zero to create a looping animation
        }
        eAniClock.restart();//restarts the clock
    }
    else if (slime2 && eAniClock.getElapsedTime().asSeconds() > 0.3f) {//changes the frame every 0.3 seconds
        eAniRect = monAnim.slime2();//sets a vector to contain all of the frames of the animation
        eSprite.setTextureRect(eAniRect[ilFrame]);//sets the rectangle texture to the current frame
        ilFrame++;//increases the frame count by one
        if (ilFrame >= eAniRect.size() - 1) {//if the frame count is greater or equal to the size of the animation vector
            ilFrame = 0;//reset the frame count to zero to create a looping animation
        }
        eAniClock.restart();//restarts the clock
    }
    // Update the sprites location

    if (!killed) {
        //if the enemy has not been killed, update its position
        eSprite.setPosition(ePosition);
    }
    if (collision == 1) {
        //if the enemy was not killed and still intersected the player, the player is invulnerable
        player->invulnerable = true;
        return 1;
    }
    else if (collision == 0) {
        //no collision took place and the player is not invulnerable
        player->invulnerable = false;
        return 0;
    }
}

// Generates homes for the monsters
void Enemies::generateHome(int homes[]) {
    //set the homes of the enemy to the last five platforms of the vector of platforms (static size of 25)
    for (int i = 0; i < 5; i++) {
        homes[i] = 25 - i;
    }

}

// Patrol function that moves the monster to the bounds of its home platform
void Enemies::patrol(std::vector<sf::RectangleShape> plats, float elapsedTime) {
    // startDir == 0 LEFT
    if (startDir == 0) {
        // Border the monster is allowed to traverse
        auto borderLeft = (int) plats[home].getPosition().x;
        if (ePosition.x < borderLeft) {
            startDir = 1;
            moveRight(elapsedTime);
        }
        else {
            moveLeft(elapsedTime);
        }
    }
        // startDir == 1 RIGHT
    else {
        // Border the monster is allowed to traverse
        auto borderRight = (int) plats[home].getPosition().x + (int) plats[home].getGlobalBounds().width - eSprite.getGlobalBounds().width;
        if (ePosition.x > borderRight) {
            startDir = 0;
            moveLeft(elapsedTime);
        }
        else {
            moveRight(elapsedTime);
        }
    }
}

// Engagement function if the player get's within a specific distance of the enemy
void Enemies::engage(float elapsedTime, sf::Sprite player) {
    float xDifference = 0;
    xDifference = player.getGlobalBounds().left - eSprite.getGlobalBounds().left;

    if (xDifference < 100 && xDifference > 0) {
        //if the difference between the left of the player and the left of the enemy is between 100 and 0, move towards the player (right)
        moveRight(elapsedTime);
    }
    else if (xDifference > -100 && xDifference < 0) {
        //if the difference between the left of the player and the left of the enemy is between 0 and -100, move towards the player (left)
        moveLeft(elapsedTime);
    }
}

void Enemies::moveLeft(float elapsedTime) {
    //move at the speed over the period of elapsed time
    ePosition.x -= eSpeed * elapsedTime;
}

void Enemies::moveRight(float elapsedTime) {
    //move at the speed over the period of elapsed time
    ePosition.x += eSpeed * elapsedTime;
}

bool Enemies::checkKill(sf::Sprite player) {
    if (eSprite.getGlobalBounds().top == (player.getGlobalBounds().top + player.getGlobalBounds().height)) {
        //delete the enemy if it is killed
        return true;
    }
    else {
        return false;
    }
}

void Enemies::setDead(sf::RectangleShape plat) {
    //move enemy if it is dead to the platform off the screen
    sf::Vector2f position;
    position.x = plat.getGlobalBounds().left;
    position.y = plat.getGlobalBounds().top;
    eSprite.setPosition(position);
}