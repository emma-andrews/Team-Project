#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Levels.h"

Levels::Levels() {
    srand(time(nullptr));
    sf::Vector2f cPosition;
    sf::RectangleShape ceiling;

    cPosition.x = 1920;
    cPosition.y = 10;

    tposition.x = 100;
    tposition.y = 25;

    gPosition.x = 1920;
    gPosition.y = 20;

    fPosition.x = 100;
    fPosition.y = 25;

    //lTexture.loadFromFile("pixil-frame-0.png");

    plat1.setFillColor(sf::Color(107, 19, 66));
    ground.setFillColor(sf::Color::Magenta);//change to transparent later, set as this just to see where it is when testing
    finishPlat.setFillColor(sf::Color(107, 19, 66));
    ceiling.setFillColor(sf::Color::Magenta);

    plat1.setSize(tposition);
    ground.setSize(gPosition);
    finishPlat.setSize(fPosition);
    ceiling.setSize(cPosition);

    tposition.y = 850;
    fPosition.x = 1700;
    fPosition.y = 200;
    gPosition.x = 0;
    gPosition.y = 1070;
    cPosition.x = 0;
    cPosition.y = 0;

    ground.setPosition(gPosition);
    ceiling.setPosition(cPosition);
    finishPlat.setPosition(fPosition);

    platforms.push_back(ground);
    //platforms.push_back(ceiling);
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
    if (player.getGlobalBounds().intersects(platforms[1].getGlobalBounds())) {//finish platform is located at index 4 in platforms, static index
        return true;
    }
    else
        return false;
}

void Levels::generatePlat() {
    for (int i = 0; i < 17; i++) {
        plat1.setPosition(tposition);
        platforms.push_back(plat1);

        tposition.x += rand() % 100 + 100;//will have to check if its possible to reach some of these offsets once jumping is implemented
        if (tposition.x > 1800)
            tposition.x = rand() % 100 + 1;

        tposition.y = rand() % 1000 - 300;
        if (tposition.y < 50)
            tposition.y = rand() % 700 + 100;
    }
}