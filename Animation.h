#ifndef TEAMPROJECT_ANIMATION_H
#define TEAMPROJECT_ANIMATION_H
#include <SFML/Graphics.hpp>

class Animation {
private:
    sf::Texture runTexture;

public:
    Animation();
    void playerRun(float elapsedTime, sf::Sprite player);
};

#endif //TEAMPROJECT_ANIMATION_H
