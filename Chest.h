#ifndef TEAMPROJECT_CHEST_H
#define TEAMPROJECT_CHEST_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Player.h"

class Chest {
private:
    sf::Sprite cSprite;
    sf::Texture cTexture;
    sf::Vector2f cPosition;
    sf::Clock cClock;
    std::vector<sf::IntRect> chestAni;
    sf::IntRect cRect;

    Animation animation;
    int cFrame;

public:
    Chest();
    sf::Sprite getChestSprite();
    void setPosition(sf::Vector2f platPosition);
    void update();
    void playAnimation();
    void resetSprite();
};

#endif //TEAMPROJECT_CHEST_H
