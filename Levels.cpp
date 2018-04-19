#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Levels.h"

Levels::Levels() {
    levelNum = 0;
    srand(time(nullptr));
    sf::Vector2f cPosition;
    sf::RectangleShape ceiling;

    texture.loadFromFile("platform.png");
    lTexture = &texture;
    //finishPlat.setTexture(lTexture);
    //staticStair.setTexture(lTexture);

    ssPosition.x = 100;
    ssPosition.y = 25;

    cPosition.x = 1920;
    cPosition.y = 10;

    tposition.x = 100;
    tposition.y = 25;

    gPosition.x = 1920;
    gPosition.y = 20;

    fPosition.x = 100;
    fPosition.y = 20;

    //lTexture.loadFromFile("pixil-frame-0.png");

    plat1.setFillColor(sf::Color(107, 19, 66));
    ground.setFillColor(sf::Color::Magenta);//change to transparent later, set as this just to see where it is when testing
    finishPlat.setFillColor(sf::Color(107, 19, 66));
    ceiling.setFillColor(sf::Color::Magenta);
    staticStair.setFillColor(sf::Color(107, 19, 66));

    plat1.setSize(tposition);
    ground.setSize(gPosition);
    finishPlat.setSize(fPosition);
    ceiling.setSize(cPosition);
    staticStair.setSize(ssPosition);

    ssPosition.x = 270;
    ssPosition.y = 875;
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
    staticStair.setPosition(ssPosition);

    platforms.push_back(ground);
    //platforms.push_back(ceiling);
    platforms.push_back(finishPlat);
    platforms.push_back(staticStair);

    ssPosition.x = 1850;
    ssPosition.y = 350;
    staticStair.setPosition(ssPosition);
    platforms.push_back(staticStair);
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
    for (unsigned i = 0; i < platforms.size() - 4; i++) {
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
    bool secondloop = false;
    int x = 0;
    sf::Vector2f size;
    size.x = 100;
    size.y = 25;
    sf::Vector2f eSize;
    for (int i = 0; i < 13; i++) {
        sf::RectangleShape plat;
        plat.setSize(size);
        plat.setFillColor(sf::Color(107, 19, 66));
        //plat.setTexture(lTexture);
        sf::Vector2f position;
        if (!secondloop) {
            x += 150;
        }
        else if (secondloop) {
            x += 125;
        }
        if (x >= 1750) {
            x = 250;
            secondloop = true;
        }
        position.y = rand() % 800 + 140;
        position.x = x;
        plat.setPosition(position);
        platforms.push_back(plat);
    }
    int ex = 0;
    eSize.x = 150;
    eSize.y = 25;
    for (int i = 0; i < 5; i++) {
        sf::RectangleShape enemyplat;
        sf::Vector2f position;
        enemyplat.setFillColor(sf::Color(107, 19, 66));
        enemyplat.setSize(eSize);
        ex += 175;
        if (ex >= 1750) {
            ex = 200;
        }
        position.y = rand() % 800 + 140;
        position.x = ex;
        enemyplat.setPosition(position);
        platforms.push_back(enemyplat);
    }
}