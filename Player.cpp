#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include <vector>
const float maxY = 2.5f;
const float gravity = 30.0f;
sf::IntRect textRect(0, 0, 30, 40);
Player::Player() {
    pSpeed = 400;

    pTexture.loadFromFile("player character sheet.png");
    pSprite.setTexture(pTexture);
    pSprite.setTextureRect(textRect);
    pSprite.setScale(2,2);//64 by 64
    pPosition.x = 500;
    pPosition.y = 800;
}

void Player::setSprite(sf::IntRect aniRect) {
    pSprite.setTextureRect(aniRect);
}

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

void Player::update(float elapsedTime, float aniElapsed, int collision, std::vector<sf::RectangleShape> plats) {
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
        //animation.playerRun();
        //if (elapsedTime > 0.5f) {
//        textRect.top = 40;
//        if(textRect.left >= 180)
//            textRect.left = 30;
//        else
//            textRect.left += 30;
//        pSprite.setTextureRect(textRect);
        //}
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
        if (pPosition.x <= plats[collision].getPosition().x && pPosition.y >= plats[collision].getPosition().y) {
            pPosition.x = plats[collision].getPosition().x - 64;
            pPosition.y = plats[collision].getPosition().y + 64;
        }
        else if (pPosition.x <= plats[collision].getPosition().x && pPosition.y <= plats[collision].getPosition().y - plats[collision].getGlobalBounds().height) {
            pPosition.x = plats[collision].getPosition().x - 64;
            pPosition.y = plats[collision].getPosition().y - plats[collision].getGlobalBounds().height - 64;
        }
        else if (pPosition.x >= plats[collision].getPosition().x + plats[collision].getGlobalBounds().width && pPosition.y >= plats[collision].getPosition().y) {
            pPosition.x = plats[collision].getPosition().x + plats[collision].getGlobalBounds().width + 64;
            pPosition.y = plats[collision].getPosition().y + 64;
        }
        else if (pPosition.x >= plats[collision].getPosition().x + plats[collision].getGlobalBounds().width && pPosition.y <= plats[collision].getPosition().y - plats[collision].getGlobalBounds().height) {
            pPosition.x = plats[collision].getPosition().x + plats[collision].getGlobalBounds().width + 64;
            pPosition.y = plats[collision].getPosition().y - plats[collision].getGlobalBounds().height - 64;
        }
//        else if (pPosition.y >= plats[collision].getPosition().y) {
//            pPosition.y = plats[collision].getPosition().y + 64;
//        }
//        else if (pPosition.y <= plats[collision].getPosition().y - plats[collision].getGlobalBounds().height) {
//            pPosition.y = plats[collision].getPosition().y - plats[collision].getGlobalBounds().height - 64;
//        }

        pVelocity.y = 0;
        canJump = true;
    }
    if (!pLeftPressed && !pRightPressed && !pJump && !canJump) {
        //pSprite.setTextureRect();
    }
    pSprite.setPosition(pPosition);
}