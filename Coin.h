#ifndef TEAMPROJECT_COIN_H
#define TEAMPROJECT_COIN_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Levels.h"
#include "Player.h"
#include "Animation.h"
class Player;
class Coin {
private:
    sf::Vector2f coinPosition;
    sf::Sprite coinSprite;
    sf::Texture coinTexture;
    sf::Clock coinClock;
    std::vector<sf::IntRect> coinRect;
    Animation animation;
    int cFrame;
public:
    Coin();
    sf::Sprite getSprite();
    void setPosition(sf::Vector2f platPosition);
    void update();
    std::vector<Coin> coins;
};
#endif //TEAMPROJECT_COIN_H