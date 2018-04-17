#include <iostream>
#include <SFML\Graphics.hpp>
#include "Coin.h"
Coin::Coin() {
    coinTexture.loadFromFile("jewel_Animation 1_3.png");
    coinSprite.setTexture(coinTexture);
    coinSprite.setScale(2,2);
    coinPosition.x = 500;
    coinPosition.y = 950;
}
sf::Sprite Coin::getSprite() {
    return coinSprite;
}
void Coin::update() {
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