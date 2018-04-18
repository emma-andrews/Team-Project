#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include <vector>
#include <iostream>

const float maxY = 2.5f;
const float gravity = 30.0f;
sf::IntRect textRect(0, 0, 30, 40);
Player::Player() {
    pSpeed = 400;
    rFrame = 0;
    lFrame = 0;
    iFrame = 0;
    lives = 3;

    pTexture.loadFromFile("player character sheet.png");
    pSprite.setTexture(pTexture);
    pSprite.setTextureRect(textRect);
    pSprite.setScale(2,2);//64 by 64
    pPosition.x = 500;
    pPosition.y = 800;
}

//void Player::setSprite(sf::IntRect aniRect) {
//    pSprite.setTextureRect(aniRect);
//}

sf::Sprite Player::getSprite() {
    return pSprite;
}

void Player::setPosition() {
    pPosition.x = 500;
    pPosition.y = 800;
    pSprite.setPosition(pPosition);
}

void Player::moveLeft() {
    pLeftPressed = true;
}

void Player::moveRight() {
    pRightPressed = true;
}

void Player::stopLeft() {
    pLeftPressed = false;
}

void Player::stopRight() {
    pRightPressed = false;
}

void Player::jump() {
    pJump = true;
    if(canJump) {
        pVelocity.y = -12.0f;
        canJump = false;
    }
}

void Player::stopJump() {
    pJump = false;
    if (pVelocity.y < -6.0f) {
        pVelocity.y = -6.0f;
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
        pPosition.x += pSpeed * elapsedTime;
        if (pPosition.x >= sf::VideoMode::getDesktopMode().width - 64)
            pPosition.x = sf::VideoMode::getDesktopMode().width - 74;

        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerRun();
            pSprite.setTextureRect(aniRect[rFrame]);
            rFrame++;
            if (rFrame >= aniRect.size()) {
                rFrame = 0;
            }
            aniClock.restart();
        }
    }

    if (pLeftPressed) {
        pPosition.x -= pSpeed * elapsedTime;
        if (pPosition.x <= 0)
            pPosition.x = 10;

        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerRun();
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
    if (collision >= 0) {
        if (pPosition.y > plats[collision].getGlobalBounds().top) {
            //pPosition.y = plats[collision].getGlobalBounds().top + pSprite.getGlobalBounds().height;
            pVelocity.y = 3.0f;
        }
        else {
            pPosition.y =  plats[collision].getGlobalBounds().top - pSprite.getGlobalBounds().height;
            pVelocity.y = 0;
            canJump = true;
        }



    }
    if (!pLeftPressed && !pRightPressed && !pJump && !canJump) {
        //pSprite.setTextureRect();
    }
    pSprite.setPosition(pPosition);
}