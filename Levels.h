#ifndef TEAMPROJECT_LEVELS_H
#define TEAMPROJECT_LEVELS_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Levels {
private:
    sf::Sprite lSprite;
    sf::Texture lTexture;

public:
    int levelNum = 1;
    Levels();
    int checkCollision(sf::Sprite player);//use player.getSprite
    sf::RectangleShape getPlatforms(int index);
    void popPlat();
    bool isEmpty();
    std::vector<sf::RectangleShape> platforms;
};

#endif //TEAMPROJECT_LEVELS_H
