#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player() {
    pSpeed = 400;
    pTexture.loadFromFile("32 x 32 platform character_idle_0.png");
    pSprite.setTexture(pTexture);
    pSprite.setScale(2,2);
    pPosition.x = 500;
    pPosition.y = 920;
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

void Player::update(float elapsedTime) {
    if (pRightPressed)
        pPosition.x += pSpeed * elapsedTime;
    if (pLeftPressed)
        pPosition.x -= pSpeed * elapsedTime;
    pSprite.setPosition(pPosition);
}