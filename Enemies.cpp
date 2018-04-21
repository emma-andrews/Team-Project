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
    rFrame = 0;
    lFrame = 0;
    irFrame = 0;
    ilFrame = 0;
    jFrame = 0;
    killed = false;
    sf::IntRect batRect(0, 0, 50, 30);
    sf::IntRect slimeRect(0,0,30,27);
    sf::IntRect slime2Rect(0, 0, 30, 32);
    int chance;
    chance = rand() % 3 + 1;
    std::cout << chance;
    if (chance == 1) {
        if(!sTexture.loadFromFile("slime sheet.png")){
            std::cout<<"Could not load from file"<<std::endl;
        }
        eSprite.setTextureRect(slimeRect);
        eSprite.setTexture(sTexture);
        eSprite.setScale(2,2);
        slime = true;
        bat = false;
        slime2 = false;
    }
    else if (chance == 2) {
        bTexture.loadFromFile("bat sheet.png");
        eSprite.setTexture(bTexture);
        eSprite.setTextureRect(batRect);
        eSprite.setScale(2,2);
        bat = true;
        slime = false;
        slime2 = false;
    }
    else if (chance == 3) {
        ssTexture.loadFromFile("slime 2 sheet.png");
        eSprite.setTexture(ssTexture);
        eSprite.setTextureRect(slime2Rect);
        eSprite.setScale(2,2);
        slime2 = true;
        slime = false;
        bat = false;
    }
}

sf::Sprite Enemies::getSprite() {
    return eSprite;
}

// Function to set the position
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

int Enemies::checkCollision(sf::Sprite player) {
    float ydifference;
    float xdifference;
    ydifference = eSprite.getGlobalBounds().top - (player.getGlobalBounds().top + player.getGlobalBounds().height);
    xdifference = (eSprite.getGlobalBounds().left + eSprite.getGlobalBounds().width) - (player.getGlobalBounds().left + player.getGlobalBounds().width);
    if (ydifference <= 10 && ydifference >= -10 && xdifference <= 20 && xdifference >= -20) {
        return 2;
    }
    else if (eSprite.getGlobalBounds().intersects(player.getGlobalBounds())) {
        return 1;
    }
    else {
        return 0;
    }
}

void Enemies::update(Player *player, float elapsedTime, std::vector<sf::RectangleShape> plats) {
    // Behavior decision
    engage(elapsedTime, player->getSprite());
    int collision = checkCollision((*player).getSprite());
    int pX = (*player).getX();
    int pY = (*player).getY();
    if (!killed) {
        if (abs(pX - (int) ePosition.x) < 100) {
            if (abs(pY - (int) ePosition.y) < 100) {
                startDir = pX - ePosition.x < 0 ? 0 : 1;
                patrol(plats, elapsedTime);
            } else {
                patrol(plats, elapsedTime);
            }
        } else {
            patrol(plats, elapsedTime);
        }
    }

    // Position Verification to prevent weird bug on new level
    if (collision == 2) {
        ePosition.x = 2100;
        ePosition.y = 1500;
        eSprite.setPosition(ePosition);
        killed = true;
    }
    else if (ePosition.x < plats[home].getPosition().x - 20 && !killed) {
        spawn(plats);
    } else if (ePosition.x > plats[home].getPosition().x + plats[home].getGlobalBounds().width + 20 - eSprite.getGlobalBounds().width && !killed) {
        spawn(plats);
    }

    if (slime && eAniClock.getElapsedTime().asSeconds() > 0.3f) {
        eAniRect = monAnim.slime();
        eSprite.setTextureRect(eAniRect[rFrame]);
        rFrame++;
        if (rFrame >= eAniRect.size() - 1) {
            rFrame = 0;
        }
        eAniClock.restart();
    }
    else if (bat && eAniClock.getElapsedTime().asSeconds() > 0.3f) {
        eAniRect = monAnim.batFly();
        eSprite.setTextureRect(eAniRect[lFrame]);
        lFrame++;
        if (lFrame >= eAniRect.size() - 1) {
            lFrame = 0;
        }
        eAniClock.restart();
    }
    else if (slime2 && eAniClock.getElapsedTime().asSeconds() > 0.3f) {
        eAniRect = monAnim.slime2();
        eSprite.setTextureRect(eAniRect[ilFrame]);
        ilFrame++;
        if (ilFrame >= eAniRect.size() - 1) {
            ilFrame = 0;
        }
        eAniClock.restart();
    }
    // Update the sprites location

    if (!killed) {
        eSprite.setPosition(ePosition);
    }
}

// Generates homes for the monsters, checking for duplicates to prevent two on one platform
void Enemies::generateHome(int homes[]) {
    bool duplicate;
    srand(time(NULL));

    int newHome;
    duplicate = false;
    for (int i = 0; i < 5; i++) {
//        do {
//            // Generate a new home
//            homes[i] = (rand() % 17) + 1;
//            // Don't allow enemies to spawn on the finish platform
//            if (homes[i] == 1) {
//                homes[i]++;
//            }
//
//            // Check from back for duplication
//            for (int j = i - 1; j > -1; j--) {
//                if (homes[i] == homes[j]) {
//                    duplicate = true;
//                    break;
//                } else {
//                    duplicate = false;
//                }
//            }
//        } while (duplicate);
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
//do calculations to figure out what direction to move in but not able to jump
    xDifference = player.getGlobalBounds().left - eSprite.getGlobalBounds().left;

    if (xDifference < 100 && xDifference > 0) {
        moveRight(elapsedTime);
    }
    else if (xDifference > -100 && xDifference < 0) {
        moveLeft(elapsedTime);
    }
}

void Enemies::moveLeft(float elapsedTime) {
    ePosition.x -= eSpeed * elapsedTime;
}

void Enemies::moveRight(float elapsedTime) {
    ePosition.x += eSpeed * elapsedTime;
}

bool Enemies::checkKill(sf::Sprite player) {
    if (eSprite.getGlobalBounds().top == (player.getGlobalBounds().top + player.getGlobalBounds().height)) {
        //delete the enemy
        return true;
    }
    else {
        return false;
    }
}

void Enemies::setDead(sf::RectangleShape plat) {
    sf::Vector2f position;
    position.x = plat.getGlobalBounds().left;
    position.y = plat.getGlobalBounds().top;
    eSprite.setPosition(position);
}