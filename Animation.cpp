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

std::vector<sf::IntRect> Animation::playerRHurt() {
    std::vector<sf::IntRect> vect;
    sf::IntRect runSource(0, 200, 34, 40);
    while (runSource.left <= 34) {
        vect.push_back(runSource);
        runSource.left += 35;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLHurt() {
    std::vector<sf::IntRect> vect;
    sf::IntRect runSource(40, 200, 34, 40);
    while (runSource.left <= 34) {
        vect.push_back(runSource);
        runSource.left += 35;
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
    std::vector<sf::IntRect> vect;
    sf::IntRect flySource(0, 0, 50, 30);
    while (flySource.left <= 250) {
        vect.push_back(flySource);
        flySource.left += 50;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::slime() {
    std::vector<sf::IntRect> vect;
    sf::IntRect openSource(0, 0, 30, 27);
    while (openSource.left <= 120) {
        vect.push_back(openSource);
        openSource.left += 30;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::slime2() {
    std::vector<sf::IntRect> vect;
    sf::IntRect openSource(0, 0, 30, 32);
    while (openSource.left <= 120) {
        vect.push_back(openSource);
        openSource.left += 30;
    }
    return vect;
}

std::vector<sf::IntRect> Animation::potion() {
    std::vector<sf::IntRect> vect;
    sf::IntRect jarSource(0, 0, 20, 22);
    while (jarSource.left <= 80) {
        vect.push_back(jarSource);
        jarSource.left += 20;
    }
    return vect;
}