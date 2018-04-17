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
    std::vector<sf::IntRect> aniRect;

    Animation animation;

    bool pLeftPressed;
    bool pRightPressed;
    bool pJump;
    bool canJump;
    bool platJump;

    float pSpeed;
    int lives;
    int rFrame;
    int lFrame;
    int iFrame;

public:
    sf::Clock aniClock;
    sf::Time da;
    Player();
    //void setSprite(sf::IntRect aniRect);
    sf::Sprite getSprite();
    void setPosition();
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    void jump();
    void stopJump();
    void update(float elapsedTime, int collision, std::vector<sf::RectangleShape> plats);
};

#endif //TEAMPROJECT_PLAYER_H
