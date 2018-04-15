#include <SFML/Graphics.hpp>
#include "Levels.h"

Levels::Levels() {
    sf::Vector2f cPosition;
    sf::Vector2f sPosition;

    sf::RectangleShape ceiling;
    sf::RectangleShape side;

    cPosition.x = 1920;
    cPosition.y = 10;

    sPosition.x = 10;
    sPosition.y = 1080;

    tposition.x = 75;
    tposition.y = 25;

    gPosition.x = 1920;
    gPosition.y = 10;

    fPosition.x = 100;
    fPosition.y = 25;

    //lTexture.loadFromFile("pixil - frame - 0.png");

    plat1.setFillColor(sf::Color(107, 19, 66));
    ground.setFillColor(sf::Color::Magenta);
    finishPlat.setFillColor(sf::Color(107, 19, 66));
    ceiling.setFillColor(sf::Color::Magenta);
    side.setFillColor(sf::Color::Magenta);

    plat1.setSize(tposition);
    ground.setSize(gPosition);
    finishPlat.setSize(fPosition);
    ceiling.setSize(cPosition);
    side.setSize(sPosition);

    tposition.y = 800;
    fPosition.x = 1800;
    fPosition.y = 150;
    gPosition.y = 1080;
    cPosition.x = 0;
    cPosition.y = 0;
    sPosition.x = 0;
    sPosition.y = 0;

    ground.setPosition(gPosition);
    ceiling.setPosition(cPosition);
    side.setPosition(sPosition);
    finishPlat.setPosition(fPosition);

    platforms.push_back(ground);
    platforms.push_back(ceiling);
    platforms.push_back(side);

    sPosition.x = 1920;
    sPosition.y = 0;
    side.setPosition(sPosition);

    platforms.push_back(side);
    platforms.push_back(finishPlat);
}

int Levels::checkCollision(sf::Sprite player) {
    for (unsigned i = 0; i < platforms.size(); i++) {
        if (player.getGlobalBounds().intersects(platforms[i].getGlobalBounds())) {
            return i;
        }
    }
    return -1;//add collisions
}

sf::RectangleShape Levels::getPlatforms(int index) {
    return platforms[index];
}

void Levels::popPlat() {
    for (unsigned i = 0; i < platforms.size() - 5; i++) {
        platforms.pop_back();//removes all platforms except for the ground, ceiling, sides, and the finish platform
    }
}

bool Levels::isEmpty() {
    if (platforms.empty())
        return true;
    else
        return false;
}

bool Levels::checkFinished(sf::Sprite player) {
    if (player.getGlobalBounds().intersects(platforms[4].getGlobalBounds())) {//finish platform is located at index 4 in platforms, static index
        return true;
    }
    else
        return false;
}

void Levels::generatePlat() {
    for (int i = 0; i < (levelNum * 5); i++) {
        plat1.setPosition(tposition);
        platforms.push_back(plat1);
        tposition.x += 60;
        tposition.y -= 60;
    }
}