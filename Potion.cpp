#include "Potion.h"

Potion::Potion() {
    sf::IntRect temp(0,0,20,22);
    sTexture.loadFromFile("potion sheet.png");
    sSprite.setTexture(sTexture);//sets the texture to the sprite sheet of the potion and its initial frame
    sSprite.setTextureRect(temp);
    sFrame = 0;//frame count is initially 0
}

sf::Sprite Potion::getSprite() {
    return sSprite;//returns the potion sprite
}

void Potion::setSpawn(bool spawn) {
    willSpawn = spawn;
}

bool Potion::getSpawn() {
    return willSpawn;
}

void Potion::setPosition(sf::Vector2f platPosition) {
    sPosition.x = platPosition.x + sSprite.getGlobalBounds().width;//sets the potion onto the top of the platform and in the middle of it
    sPosition.y = platPosition.y - sSprite.getGlobalBounds().height;
}

void Potion::update(sf::Vector2f plat) {
    setPosition(plat);//sets the position of the potion
    sSprite.setPosition(sPosition);
}

void Potion::playAnimation() {
    if (sClock.getElapsedTime().asSeconds() > 0.1f) {//frames change every 0.1 seconds
        sRect = animation.potion();//sets the vector to the potion frame
        sSprite.setTextureRect(sRect[sFrame]);//sets the texture to the current frame in the vector
        sFrame++;//increases the frame by one
        if (sFrame == sRect.size()) {
            //if the frame is equal to the size of the vector
            sFrame = 0;//reset the frame count back to 0
        }
        sClock.restart();//restart the clock
    }
}

int Potion::potionCollide(sf::Sprite player) {
    if (player.getGlobalBounds().intersects(sSprite.getGlobalBounds())) {
        //if the player intersects with the potion, return 1 signifying that an interaction has taken place
        return 1;
    }
    else {//otherwise no interaction occurred
        return 0;
    }
}

void Potion::potionHide() {
    //hides the potion off the screen if it is interacted with
    sSprite.setPosition(2000, 1400);
}