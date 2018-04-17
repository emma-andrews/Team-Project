#ifndef TEAMPROJECT_PLAYER_H
#define TEAMPROJECT_PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Levels.h"
#include "Animation.h"

class Player {
private:
    sf::Vector2f pPosition;
    sf::Vector2f pVelocity;
    sf::Sprite pSprite;
    sf::Texture pTexture;

    Animation animation;

    bool pLeftPressed;
    bool pRightPressed;
    bool pJump;
    bool canJump;

    float pSpeed;
    int lives = 3;

public:
    Player();
    sf::Sprite getSprite();
    void moveLeft();
    void moveRight();
    void jump();
    void stopJump();
    void stopLeft();
    void stopRight();
    void update(float elapsedTime, int collision, std::vector<sf::RectangleShape> plats);
};

#endif //TEAMPROJECT_PLAYER_H
