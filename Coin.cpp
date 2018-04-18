#include <iostream>
#include <SFML/Graphics.hpp>
#include "Coin.h"
#include <vector>

Coin::Coin() {
    coinTexture.loadFromFile("jewel sheet.png");
    coinSprite.setTexture(coinTexture);
    sf::IntRect tempcoinrect(0,0,16,16);
    coinSprite.setTextureRect(tempcoinrect);
    coinSprite.setScale(2,2);
    coinPosition.x = 500;
    coinPosition.y = 950;

    cFrame = 0;
}
sf::Sprite Coin::getSprite() {
    return coinSprite;
}
void Coin::update() {
    if (coinClock.getElapsedTime().asSeconds() > 0.15f) {
        coinRect = animation.coinTurn();
        coinSprite.setTextureRect(coinRect[cFrame]);
        cFrame++;
        if (cFrame >= coinRect.size()) {
            cFrame = 0;
        }
        coinClock.restart();
    }
    coinSprite.setPosition(coinPosition);
}
//    Coin(sf::Vector2f size) {
//        coin.setScale(size);
//        coin.setColor(sf::Color::Yellow);
//    }
//
//    void drawTo(sf::RenderWindow &window) {
//        window.draw(coin);
//    }
//
//    sf::FloatRect getGlobalBounds() {
//        return coin.getGlobalBounds();
//    }
//
//    void setPos(sf::Vector2f newPos) {
//        coin.setPosition(newPos);
//    }