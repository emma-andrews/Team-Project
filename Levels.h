#ifndef TEAMPROJECT_LEVELS_H
#define TEAMPROJECT_LEVELS_H
#include <vector>
#include <SFML/Graphics.hpp>

class Levels {
private:
    sf::Sprite lSprite;
    sf::Texture lTexture;

public:
    int levelNum = 1;
    Levels();
    bool checkCollision(sf::Sprite player);//use player.getSprite
    sf::RectangleShape getPlatforms(int index);
    void popPlat();
    bool isEmpty();
    std::vector<sf::RectangleShape> platforms;
};

#endif //TEAMPROJECT_LEVELS_H
