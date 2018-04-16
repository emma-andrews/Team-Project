#include <SFML/Graphics.hpp>
#include "Animation.h"

Animation::Animation() {
    runTexture.loadFromFile("player character run sheet.png");

}

void Animation::playerRun(float elapsedTime, sf::Sprite player) {
    sf::IntRect runSource(0, 0, 30, 40);
    if (elapsedTime > 1.0f) {
        if (runSource.left == 120) {
            runSource.left = 0;
        }
        else {
            runSource.left += 30;
        }
        player.setTextureRect(runSource);
    }
}