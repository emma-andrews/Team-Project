#include <SFML/Graphics.hpp>
#include "Chest.h"

Chest::Chest() {
    //called when the chest object is created in Engine.cpp
    cTexture.loadFromFile("chest sheet.png");//sprite sheet containing all the frames of the chest animation
    cSprite.setTexture(cTexture);//sets the texture of the chest sprite to the sprite sheet
    cSprite.setScale(2,2);//scales it up by 2 so it is more visible
    sf::IntRect ctempRect(0, 0, 16, 16);//creates an integer rectangle with origin (0,0), width 16, and height 16
    cSprite.setTextureRect(ctempRect);//sets the texture to be the rectangle of ctempRect
    cFrame = 0;//initializes the frame for animation to 0
}

sf::Sprite Chest::getChestSprite() {
    return cSprite;//returns the chest sprite with the current texture it is on in terms of animation
}

void Chest::setPosition(sf::Vector2f platPosition) {
    cPosition.x = platPosition.x + cSprite.getGlobalBounds().width;//sets the x position of the chest to be the x position of the platform it is on, then moved over by its width so it is halfway on the platform
    cPosition.y = platPosition.y - cSprite.getGlobalBounds().height;//sets the y position of the chest to be the y position of the platform minus the height of the sprite so it lays on it nicely
}

void Chest::update() {//updates the chest by setting it in the correct position
    cSprite.setPosition(cPosition);
}

void Chest::playAnimation() {
    bool lastFrame = false;
    if (cClock.getElapsedTime().asSeconds() > 0.2f) {//changes frame every 0.2 seconds
        chestAni = animation.chestOpen();//gets the vector of the frames in the animation
        cSprite.setTextureRect(chestAni[cFrame]);//sets the rectangle texture of the sprite to the current frame of the animation
        if (cFrame == chestAni.size() - 1) {//if the frame is one the second to last frame, lastFrame becomes true
            lastFrame = true;
        }
        if (!lastFrame) {//if it is not on the lastFrame, continue to increase the frame count
            cFrame++;
        }
        else if (lastFrame) {//if it is on the last frame, set the frame to only be the last frame and not play the animation any more
            cFrame = chestAni.size() - 1;
        }
        cClock.restart();//restart the clock so that frames can change
    }
}

void Chest::resetSprite() {
    sf::IntRect ctempRect(0, 0, 16, 16);//resets the sprite to the original rectangle when a level is completed or reset
    cSprite.setTextureRect(ctempRect);
}