#ifndef TEAMPROJECT_COIN_H
#define TEAMPROJECT_COIN_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Levels.h"
#include "Animation.h"

class Coin {
private:
    sf::Vector2f coinPosition;
    sf::Sprite coinSprite;
    sf::Texture coinTexture;
public:
    Coin();
    sf::Sprite getSprite();
    void update();
//    void drawTo(sf::RenderWindow &window);
//    sf::FloatRect getGlobalBounds();
//    void setPos(sf::Vector2f newPos);

};
#endif //TEAMPROJECT_COIN_H