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

    float pSpeed;
    int lives = 3;

public:
    Player();
    sf::Sprite getSprite();
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    void jump();
    void stopJump();
    void update(float elapsedTime);
};

#endif //TEAMPROJECT_PLAYER_H
