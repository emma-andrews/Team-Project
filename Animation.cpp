#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"

Animation::Animation() {
    runTexture.loadFromFile("player character sheet.png");
}

std::vector<sf::IntRect> Animation::playerIdle() {
    std::vector<sf::IntRect> vect;
    sf::IntRect idleSource(0, 0, 30, 40);
    while (idleSource.left <= 120) {
        vect.push_back(idleSource);
        idleSource.left += 30;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerRun() {
    std::vector<sf::IntRect> vect;
    sf::IntRect runSource(0, 40, 30, 40);
    while (runSource.left <= 150) {
        vect.push_back(runSource);
        runSource.left += 30;
    }
    return vect;
}