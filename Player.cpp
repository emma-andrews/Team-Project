#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include <vector>
const float maxY = 2.5f;
const sf::Vector2f gravity(0.f, 5.f);
sf::Vector2f velocity(2.f, 5.f);
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
        animation.playerRun(elapsedTime, getSprite());
    }
    if (pLeftPressed) {
        pPosition.x -= pSpeed * elapsedTime;
        if (pPosition.x <= 0)
            pPosition.x = 10;
    }
    if (pJump) {
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