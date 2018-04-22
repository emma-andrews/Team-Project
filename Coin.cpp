#include <SFML/Graphics.hpp>
#include "Coin.h"
#include <vector>

Coin::Coin() {
    coinTexture.loadFromFile("jewel sheet.png");//sets the texture of the coin to the sprite sheet for its animation
    coinSprite.setTexture(coinTexture);
    sf::IntRect tempcoinrect(0,0,16,16);//sets the initial rectangle to origin (0,0), width 16 and height 16
    coinSprite.setTextureRect(tempcoinrect);
    coinSprite.setScale(2,2);//scales it by 2 to make it more visible

    cFrame = 0;//initializes the animation frame to 0
}

sf::Sprite Coin::getSprite() {//returns the coin sprite
    return coinSprite;
}

void Coin::setPosition(sf::Vector2f platPosition) {
    coinPosition.x = platPosition.x + coinSprite.getGlobalBounds().width;//sets the x position of the coin to the x position of the platform plus the coin width
    coinPosition.y = platPosition.y - coinSprite.getGlobalBounds().height;//sets the y position of the coin to the y position of the platform minus the height of the coin
}

void Coin::update() {//updates the coin every frame
    if (coinClock.getElapsedTime().asSeconds() > 0.15f) {//changes the frame every 0.15 seconds
        coinRect = animation.coinTurn();//sets a vector to contain all of the frames of the animation
        coinSprite.setTextureRect(coinRect[cFrame]);//sets the rectangle texture to the current frame
        cFrame++;//increases the frame count by one
        if (cFrame >= coinRect.size()) {//if the frame count is greater or equal to the size of the animation vector
            cFrame = 0;//reset the frame count to zero to create a looping animation
        }
        coinClock.restart();//restarts the clock
    }
    coinSprite.setPosition(coinPosition);//sets the position of the sprite to its position
}