#include <SFML/Graphics.hpp>
#include "Enemies.h"
#include "Levels.h"
#include <vector>
#include <cmath>
#include <iostream>

const float maxY = 2.5f;
const float gravity = 30.0f;

// Monster box
sf::IntRect monsterRect(0,0,32,32);

// Default constructor for monsters
Enemies::Enemies() {
    // Give enemies a variable speed, with 25 to 50
    eSpeed = (rand() % 25) + 25;
    rFrame = 0;
    lFrame = 0;
    irFrame = 0;
    ilFrame = 0;
    jFrame = 0;

    eTexture.loadFromFile("platformer slime_Animation 1_0.png");
    eSprite.setTexture(eTexture);
    eSprite.setTextureRect(monsterRect);
    eSprite.setScale(2,2);
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
    if (eSprite.getGlobalBounds().intersects(player.getGlobalBounds())) {
        return 1;
    }
    else {
        return 0;
    }
}

void Enemies::update(Player *player, float elapsedTime, std::vector<sf::RectangleShape> plats) {
    // Behavior decision
    int collision = checkCollision((*player).getSprite());
    int pX = (*player).getX();
    int pY = (*player).getY();
    if (abs(pX - (int) ePosition.x) < 100) {
        if (abs(pY - (int) ePosition.y) < 100) {
            startDir = pX - ePosition.x < 0 ? 0 : 1;
            patrol(plats, elapsedTime);
        }
        else {
            patrol(plats, elapsedTime);
        }
    }
    else {
        patrol(plats, elapsedTime);
    }
    // Position Verification to prevent weird bug on new level
    if (ePosition.x < plats[home].getPosition().x - 20) {
        spawn(plats);
    } else if (ePosition.x > plats[home].getPosition().x + plats[home].getGlobalBounds().width + 20 - eSprite.getGlobalBounds().width) {
        spawn(plats);
    }
    // Update the sprites location
    eSprite.setPosition(ePosition);
}

// Generates homes for the monsters, checking for duplicates to prevent two on one platform
void Enemies::generateHome(int homes[]) {
    bool duplicate;
    srand(time(NULL));

    int newHome;
    duplicate = false;
    for (int i = 0; i < 5; i++) {
        do {
            // Generate a new home
            homes[i] = (rand() % 17) + 1;
            // Don't allow enemies to spawn on the finish platform
            if (homes[i] == 1) {
                homes[i]++;
            }

            // Check from back for duplication
            for (int j = i - 1; j > -1; j--) {
                if (homes[i] == homes[j]) {
                    duplicate = true;
                    break;
                } else {
                    duplicate = false;
                }
            }
        } while (duplicate);
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
void Enemies::engage(std::vector<sf::RectangleShape> plats, float elapsedTime) {

}

void Enemies::moveLeft(float elapsedTime) {
    ePosition.x -= eSpeed * elapsedTime;
}

void Enemies::moveRight(float elapsedTime) {
    ePosition.x += eSpeed * elapsedTime;
}