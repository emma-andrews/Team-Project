#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include <vector>
const float maxY = 2.5f;
const float gravity = 30.0f;
Player::Player() {
    pSpeed = 400;
    pTexture.loadFromFile("32 x 32 platform character_idle_0.png");
    pSprite.setTexture(pTexture);
    pSprite.setScale(2,2);//64 by 64
    pPosition.x = 500;
    pPosition.y = 500;
}

sf::Sprite Player::getSprite() {
    return pSprite;
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
        animation.playerRun(elapsedTime, getSprite());
    }
    if (pLeftPressed) {
        pPosition.x -= pSpeed * elapsedTime;
        if (pPosition.x <= 0)
            pPosition.x = 10;
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
        pPosition.y = (plats[collision].getGlobalBounds().top - plats[collision].getGlobalBounds().height);
    }

    pSprite.setPosition(pPosition);
}