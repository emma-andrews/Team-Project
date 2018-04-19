#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Chest.h"

Chest::Chest() {
    srand(time(nullptr));
    cTexture.loadFromFile("chest sheet.png");
    cSprite.setTexture(cTexture);
    cSprite.setScale(2,2);
    sf::IntRect ctempRect(0, 0, 16, 16);
    cSprite.setTextureRect(ctempRect);
    cFrame = 0;
}

sf::Sprite Chest::getChestSprite() {
    return cSprite;
}

void Chest::setPosition(sf::Vector2f platPosition) {
    cPosition.x = platPosition.x + cSprite.getGlobalBounds().width;
    cPosition.y = platPosition.y - cSprite.getGlobalBounds().height;
}

void Chest::update() {
    cSprite.setPosition(cPosition);
}

void Chest::playAnimation() {
    bool lastFrame = false;
    if (cClock.getElapsedTime().asSeconds() > 0.2f) {
        chestAni = animation.chestOpen();
        cSprite.setTextureRect(chestAni[cFrame]);
        if (cFrame == chestAni.size() - 1) {
            lastFrame = true;
        }
        if (!lastFrame) {
            cFrame++;
        }
        else if (lastFrame) {
            cFrame = chestAni.size() - 1;
        }
        cClock.restart();
    }
}

void Chest::resetSprite() {
    sf::IntRect ctempRect(0, 0, 16, 16);
    cSprite.setTextureRect(ctempRect);
}