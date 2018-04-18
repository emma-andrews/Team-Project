#include <SFML/Graphics.hpp>
#include "Chest.h"

Chest::Chest() {
    cTexture.loadFromFile("chest sheet.png");
    sf::IntRect cRect(0, 0, 16, 16);
    cSprite.setTextureRect(cRect);
}

sf::Sprite Chest::getChestSprite() {
    return cSprite;
}

void Chest::setPosition(sf::Vector2f platPosition) {
    cPosition.x = platPosition.x;
    cPosition.y = platPosition.y - cSprite.getGlobalBounds().height;
}