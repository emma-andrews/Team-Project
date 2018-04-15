#ifndef TEAMPROJECT_PLAYER_H
#define TEAMPROJECT_PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Vector2f pPosition;
    sf::Vector2f pVelocity;
    sf::Sprite pSprite;
    sf::Texture pTexture;
    bool pLeftPressed;
    bool pRightPressed;
    bool pJump;
    float pSpeed;
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
