#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"

Animation::Animation() {
    runTexture.loadFromFile("player character sheet.png");
}

std::vector<sf::IntRect> Animation::playerRIdle() {
    std::vector<sf::IntRect> vect;
    sf::IntRect idleSource(0, 0, 30, 40);
    while (idleSource.left <= 90) {
        vect.push_back(idleSource);
        idleSource.left += 30;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLIdle() {
    std::vector<sf::IntRect> vect;
    sf::IntRect idleSource(0, 160, 30, 40);
    while (idleSource.left <= 90) {
        vect.push_back(idleSource);
        idleSource.left += 30;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerRRun() {
    std::vector<sf::IntRect> vect;
    sf::IntRect runSource(0, 40, 26, 37);
    while (runSource.left <= 150) {
        vect.push_back(runSource);
        runSource.left += 30;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLRun() {
    std::vector<sf::IntRect> vect;
    sf::IntRect runSource(0, 120, 26, 37);
    while (runSource.left <= 150) {
        vect.push_back(runSource);
        runSource.left += 30;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerRJump() {
    std::vector<sf::IntRect> vect;
    bool second = false;
    sf::IntRect runSource(0, 80, 26, 37);
    while (runSource.left <= 70) {
        vect.push_back(runSource);
        if (!second) {
            runSource.left += 30;
            second = true;
        }
        if (second) {
            runSource.left += 35;
        }

    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLJump() {
    std::vector<sf::IntRect> vect;
    bool second = false;
    sf::IntRect runSource(69, 80, 30, 35);
    while (runSource.left <= 134) {
        vect.push_back(runSource);
        if (!second) {
            runSource.left += 30;
            second = true;
        }
        if (second) {
            runSource.left += 40;
        }
    }
    return vect;
}

std::vector<sf::IntRect> Animation::coinTurn() {
    std::vector<sf::IntRect> vect;
    sf::IntRect turnSource(0, 0, 16, 16);
    while (turnSource.left <= 95) {
        vect.push_back(turnSource);
        turnSource.left += 16;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::chestOpen() {//animation for chest opening
    std::vector<sf::IntRect> vect;
    sf::IntRect openSource(0, 0, 16, 16);
    while (openSource.left <= 48) {
        vect.push_back(openSource);
        openSource.left += 17;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::batFly() {
    bool first = true;
    bool forty = false;
    std::vector<sf::IntRect> vect;
    sf::IntRect flySource(0, 0, 44, 28);
    while (flySource.left <= 280) {
        vect.push_back(flySource);
        if (first) {
            flySource.left += 50;
            first = false;
        }
    }
    return vect;
}