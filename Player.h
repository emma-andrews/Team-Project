#ifndef TEAMPROJECT_PLAYER_H
#define TEAMPROJECT_PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    int irFrame;
    int ilFrame;
    int jrFrame;
    int jlFrame;
    int score;

public:
    sf::Clock aniClock;
    sf::Time da;

    bool rightLast;
    bool leftLast;
    bool invulnerable;

    Player();
    //void setSprite(sf::IntRect aniRect);
    sf::Sprite getSprite();
    void setPosition();
    void moveLeft();
    int getX();
    int getY();
    void moveRight();
    void stopLeft();
    void stopRight();
    void jump();
    void setSpeed(int speed);
    void stopJump();
    void update(float elapsedTime, int collision, std::vector<sf::RectangleShape> plats);
    void setLives(int num);
    int getLives();
    bool checkInteraction(sf::Sprite chest);
    int getScore();
    void setScore(int num);
    void bounceBack(int direction);
};

#endif //TEAMPROJECT_PLAYER_H