#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"

Animation::Animation() {
    runTexture.loadFromFile("player character run sheet.png");
}

std::vector<sf::Texture> Animation::playerRun() {
    std::vector<sf::Texture> vect;
    sf::IntRect runSource(0, 0, 30, 40);
    return vect;
}