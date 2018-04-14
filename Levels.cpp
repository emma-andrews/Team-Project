#include <SFML/Graphics.hpp>
#include "Levels.h"

Levels::Levels() {
    //load in tiled map?
    sf::Vector2f tposition;
    tposition.x = 75;
    tposition.y = 25;
    sf::RectangleShape plat1;
    //lTexture.loadFromFile("pixil - frame - 0.png");

    plat1.setFillColor(sf::Color(107, 19, 66));

    plat1.setSize(tposition);

    tposition.y = 800;

    for (int i = 0; i < (levelNum * 5); i++) {
        plat1.setPosition(tposition);
        platforms.push_back(plat1);
        tposition.x += 60;
        tposition.y -= 60;
    }
}

bool Levels::checkCollision(sf::Sprite player) {
    return true;//add collisions
}

sf::RectangleShape Levels::getPlatforms(int index) {
    return platforms[index];
}

void Levels::popPlat() {
    platforms.pop_back();
}

bool Levels::isEmpty() {
    if (platforms.empty())
        return true;
    else
        return false;
}