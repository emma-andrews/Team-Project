#include "Potion.h"
//IS NOT PLUGGED INTO ENGINE, JUST SET UP HERE
Potion::Potion() {
    sf::IntRect temp(0,0,20,22);
    sTexture.loadFromFile("potion sheet.png");
    sSprite.setTexture(sTexture);
    sSprite.setTextureRect(temp);

    sFrame = 0;
}

sf::Sprite Potion::getSprite() {
    return sSprite;
}

void Potion::setPosition(sf::Vector2f platPosition) {
    //set position on platform 8 in engine, check interaction with the potion in player & engine (basically just copy all of chest except for animations)
    sPosition.x = platPosition.x + sSprite.getGlobalBounds().width;
    sPosition.y = platPosition.y - sSprite.getGlobalBounds().height;
}

void Potion::update() {
    sSprite.setPosition(sPosition);
}

void Potion::playAnimation() {
    if (sClock.getElapsedTime().asSeconds() > 0.1f) {
        sRect = animation.potion();
        sSprite.setTextureRect(sRect[sFrame]);
        sFrame++;
        if (sFrame == sRect.size()) {
            sFrame = 0;
        }
        sClock.restart();
    }
}