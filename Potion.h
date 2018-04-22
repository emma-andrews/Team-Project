#ifndef TEAMPROJECT_POTION_H
#define TEAMPROJECT_POTION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"

class Potion {
private:
    sf::Sprite sSprite;
    sf::Texture sTexture;
    std::vector<sf::IntRect> sRect;
    sf::Clock sClock;
    sf::Vector2f sPosition;

    int sFrame;
    Animation animation;

public:
    Potion();
    sf::Sprite getSprite();
    void setPosition(sf::Vector2f platPosition);
    void update();
    void playAnimation();
};

#endif //TEAMPROJECT_POTION_H