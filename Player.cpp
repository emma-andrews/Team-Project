#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"

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
}

void Player::stopJump() {
    pJump = false;
}

void Player::update(float elapsedTime, int collision, std::vector<sf::RectangleShape> plats) {
    if (pRightPressed) {
        pPosition.x += pSpeed * elapsedTime;
        if (pPosition.x >= sf::VideoMode::getDesktopMode().width - 64)
            pPosition.x = sf::VideoMode::getDesktopMode().width - 74;
    }
    if (pLeftPressed) {
        pPosition.x -= pSpeed * elapsedTime;
        if (pPosition.x <= 0)
            pPosition.x = 10;
    }
    if (pJump) {
        pPosition.y += pSpeed * elapsedTime;
    }
    if (collision >= 0) {
        pPosition.y = (plats[collision].getGlobalBounds().top - plats[collision].getGlobalBounds().height);
    }

    pSprite.setPosition(pPosition);
}