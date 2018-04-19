#ifndef TEAMPROJECT_LEVELS_H
#define TEAMPROJECT_LEVELS_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Levels {
private:
    sf::Sprite lSprite;
    const sf::Texture *lTexture;
    sf::Texture texture;
    sf::Vector2f tposition;
    sf::Vector2f gPosition;
    sf::Vector2f fPosition;
    sf::Vector2f tempPosition;

    sf::RectangleShape plat1;
    sf::RectangleShape ground;
    sf::RectangleShape finishPlat;

    bool validPosition;

public:
    int levelNum;
    std::vector<sf::RectangleShape> platforms;

    Levels();
    int checkCollision(sf::Sprite player);//use player.getSprite
    sf::RectangleShape getPlatforms(int index);
    void popPlat();
    bool isEmpty();
    bool checkFinished(sf::Sprite player);
    void generatePlat();
};

#endif //TEAMPROJECT_LEVELS_H