#ifndef TEAMPROJECT_ANIMATION_H
#define TEAMPROJECT_ANIMATION_H
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
private:
    sf::Texture runTexture;

public:
    Animation();
    std::vector<sf::IntRect> playerRIdle();
    std::vector<sf::IntRect> playerLIdle();
    std::vector<sf::IntRect> playerRRun();
    std::vector<sf::IntRect> playerLRun();
    std::vector<sf::IntRect> playerRJump();
    std::vector<sf::IntRect> coinTurn();
};

#endif //TEAMPROJECT_ANIMATION_H
