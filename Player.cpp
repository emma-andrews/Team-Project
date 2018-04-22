#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include <vector>
#include <iostream>

const float maxY = 2.5f;
const float gravity = 30.0f;
sf::IntRect textRect(0, 0, 30, 40);
Player::Player() {
    pSpeed = 400;//speed of the player
    rFrame = 0;//initializes the frame counts for the animations to 0
    lFrame = 0;
    irFrame = 0;
    ilFrame = 0;
    jrFrame = 0;
    jlFrame = 0;
    lives = 3;//start with 3 lives
    score = 0;

    pTexture.loadFromFile("player character sheet.png");
    pSprite.setTexture(pTexture);//sets the texture of the player to be the sheet of all frames of the player
    pSprite.setTextureRect(textRect);//sets the current texture of the sprite to the rectangle starting at position 0,0 and extending to 30 by 40
    pSprite.setScale(2,2);//scales sprite by 2 so it is 64 by 64
    pPosition.x = 50;//initial starting position
    pPosition.y = 920;
}

//void Player::setSprite(sf::IntRect aniRect) {
//    pSprite.setTextureRect(aniRect);
//}

sf::Sprite Player::getSprite() {
    return pSprite;//get the sprite of the player
}

void Player::setPosition() {
    pPosition.x = 500;//sets the position of the player back to the initial starting point
    pPosition.y = 800;
    pSprite.setPosition(pPosition);
}

void Player::moveLeft() {
    pLeftPressed = true;//able to move left
}

void Player::moveRight() {
    pRightPressed = true;//able to move right
}

void Player::stopLeft() {
    pLeftPressed = false;//not able to move left
}

void Player::stopRight() {
    pRightPressed = false;//not able to move right
}

void Player::jump() {
    pJump = true;//input to jump
    if(canJump) {//able to jump based on current position
        pVelocity.y = -12.0f;
        canJump = false;//unable to jump while already in a jump
    }
}

void Player::setSpeed(int speed) {
    this->pSpeed = speed;
}

void Player::stopJump() {
    pJump = false;//no input to jump
    if (pVelocity.y < -6.0f) {
        pVelocity.y = -6.0f;//no longer moving down
    }
}

void Player::update(float elapsedTime, int collision, std::vector<sf::RectangleShape> plats) {
    pPosition.x += pVelocity.x * elapsedTime;
    pPosition.y += pVelocity.y * gravity * elapsedTime * 3;
    pVelocity.y += gravity * elapsedTime;
    if (pPosition.y > 920) {
        pPosition.y = 920;
        canJump = true;
    }
    if (pRightPressed) {
        rightLast = true;
        leftLast = false;
        pPosition.x += pSpeed * elapsedTime;
        if (pPosition.x >= sf::VideoMode::getDesktopMode().width - 64)
            pPosition.x = sf::VideoMode::getDesktopMode().width - 74;

        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerRRun();
            pSprite.setTextureRect(aniRect[rFrame]);
            rFrame++;
            if (rFrame >= aniRect.size()) {
                rFrame = 0;
            }
            aniClock.restart();
        }
    }

    if (pLeftPressed) {
        leftLast = true;
        rightLast = false;
        pPosition.x -= pSpeed * elapsedTime;
        if (pPosition.x <= 0)
            pPosition.x = 10;

        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerLRun();
            pSprite.setTextureRect(aniRect[lFrame]);
            lFrame++;
            if (lFrame >= aniRect.size()) {
                lFrame = 0;
            }
            aniClock.restart();
        }
    }
    if (pJump && canJump) {
        if (pPosition.y > 0) {
            pPosition.y -= maxY;
        }
        else if (pPosition.y == 0) {
            pPosition.y += maxY;
        }
    }
    if (pJump) {
        if (rightLast) {
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {
                aniRect = animation.playerRJump();
                pSprite.setTextureRect(aniRect[jrFrame]);
                jrFrame++;
                if (jrFrame >= aniRect.size()) {
                    jrFrame = aniRect.size() - 1;
                }
                aniClock.restart();
            }
        }
        else if (leftLast) {
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {
                aniRect = animation.playerLJump();
                pSprite.setTextureRect(aniRect[jlFrame]);
                jlFrame++;
                if (jlFrame >= aniRect.size()) {
                    jlFrame = aniRect.size() - 1;
                }
                aniClock.restart();
            }
        }
    }
    if (collision >= 0) {
        bool collideBottom = pPosition.y > plats[collision].getGlobalBounds().top;
        bool collideLeft = (pPosition.y + pSprite.getGlobalBounds().height) > plats[collision].getGlobalBounds().top &&
                           (pPosition.x + pSprite.getGlobalBounds().width) > plats[collision].getGlobalBounds().left &&
                           (pPosition.x + pSprite.getGlobalBounds().width) < plats[collision].getGlobalBounds().left + 5;
        bool collideRight = (pPosition.y + pSprite.getGlobalBounds().height) > plats[collision].getGlobalBounds().top &&
                            (pPosition.x) < plats[collision].getGlobalBounds().left + plats[collision].getGlobalBounds().width &&
                            (pPosition.x) > plats[collision].getGlobalBounds().left + plats[collision].getGlobalBounds().width - 5;
        if (collideBottom) {
            pPosition.y = plats[collision].getGlobalBounds().top + plats[collision].getGlobalBounds().height;
            pVelocity.y = 6.0f;
        }
        else if (collideLeft) {
            pPosition.x = plats[collision].getGlobalBounds().left - pSprite.getGlobalBounds().width;
            pVelocity.y += 0.05f;
        }
        else if (collideRight) {
            pPosition.x = plats[collision].getGlobalBounds().left + plats[collision].getGlobalBounds().width;
            pVelocity.y += 0.05f;
        }
        else {
            pPosition.y = plats[collision].getGlobalBounds().top - pSprite.getGlobalBounds().height;
            pVelocity.y = 0;
            canJump = true;
        }
    }
    if (!pLeftPressed && !pRightPressed && !pJump) {
        if (rightLast) {
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {
                aniRect = animation.playerRIdle();
                pSprite.setTextureRect(aniRect[irFrame]);
                irFrame++;
                if (irFrame >= aniRect.size()) {
                    irFrame = 0;
                }
                aniClock.restart();
            }
        }
        else if (leftLast) {
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {
                aniRect = animation.playerLIdle();
                pSprite.setTextureRect(aniRect[ilFrame]);
                ilFrame++;
                if (ilFrame >= aniRect.size()) {
                    ilFrame = 0;
                }
                aniClock.restart();
            }
        }
    }
    pSprite.setPosition(pPosition);
}

void Player::setLives(int num) {
    lives = num;
}

int Player::getLives() {
    return lives;
}

bool Player::checkInteraction(sf::Sprite chest) {
    if (pSprite.getGlobalBounds().intersects(chest.getGlobalBounds())) {
        //drop chance for either score increase or extra life
        int chance = rand() % 2 + 1;
        std::cout << chance;
        if (chance == 1) {
            //increase life count
            lives++;
        }
        else if (chance == 2) {
            //increase score by some amount
            score += 100;
        }
        return true;
    }
    else {
        return false;
    }
}

int Player::getScore() {
    return score;
}

void Player::setScore(int num) {
    score += num;
}

int Player::getX() {
    return pPosition.x;
}

int Player::getY() {
    return pPosition.y;
}

void Player::bounceBack(int direction) {
    if (direction == 1) {//moving right when collided
        pPosition.x -= pSpeed * 0.15f;
        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerRHurt();
            pSprite.setTextureRect(aniRect[0]);
            aniClock.restart();
        }
    }
    else if (direction == 2) {//moving left when collided
        pPosition.x += pSpeed * 0.15f;
        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerLHurt();
            pSprite.setTextureRect(aniRect[0]);
            aniClock.restart();
        }
    }
}