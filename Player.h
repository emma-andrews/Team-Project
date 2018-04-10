#ifndef TEAMPROJECT_PLAYER_H
#define TEAMPROJECT_PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Vector2f pPosition;
    sf::Sprite pSprite;
    sf::Texture pTexture;
    bool pLeftPressed;
    bool pRightPressed;
    float pSpeed;
public:
    Player();
    sf::Sprite getSprite();
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    void update(float elapsedTime);
};

#endif //TEAMPROJECT_PLAYER_H
