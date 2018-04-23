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
    bool willSpawn;
    Animation animation;

public:
    Potion();
    sf::Clock rewardTimer;
    int potionCollide(sf::Sprite player);
    bool getSpawn();
    sf::Time rewardLeft();
    void setSpawn(bool spawn);
    void potionHide();
    sf::Sprite getSprite();
    void setPosition(sf::Vector2f platPosition);
    void update(sf::Vector2f plat);
    void playAnimation();
};

#endif //TEAMPROJECT_POTION_H