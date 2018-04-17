#ifndef TEAMPROJECT_ANIMATION_H
#define TEAMPROJECT_ANIMATION_H
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
private:
    sf::Texture runTexture;

public:
    Animation();
    std::vector<sf::IntRect> playerIdle();
    std::vector<sf::IntRect> playerRun();
};

#endif //TEAMPROJECT_ANIMATION_H
