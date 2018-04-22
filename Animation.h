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
    std::vector<sf::IntRect> playerLJump();
    std::vector<sf::IntRect> playerRHurt();
    std::vector<sf::IntRect> playerLHurt();
    std::vector<sf::IntRect> coinTurn();
    std::vector<sf::IntRect> chestOpen();
    std::vector<sf::IntRect> batFly();
    std::vector<sf::IntRect> slime();
    std::vector<sf::IntRect> slime2();
    std::vector<sf::IntRect> potion();
};

#endif //TEAMPROJECT_ANIMATION_H
