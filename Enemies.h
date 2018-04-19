#ifndef TEAMPROJECT_ENEMIES_H
#define TEAMPROJECT_ENEMIES_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Levels.h"
#include "Animation.h"

class Enemies {
private:
    sf::Vector2f ePosition;
    sf::Vector2f eVelocity;
    sf::Sprite eSprite;
    sf::Texture eTexture;
    std::vector<sf::IntRect> eAniRect;

    Animation monAnim;

    float eSpeed;
    int rFrame;
    int lFrame;
    int irFrame;
    int ilFrame;
    int jFrame;
    int home;
    int startDir;

public:
    sf::Clock eAniClock;
    sf::Time tp;
    Enemies();

    sf::Sprite getSprite();
    int checkCollision(sf::Sprite player);
    void moveLeft(float elapsedTime);
    void moveRight(float elapsedTime);
    void setPosition(std::vector<sf::RectangleShape> plats);
    void engage(std::vector<sf::RectangleShape> plats, float elapsedTime);
    void patrol(std::vector<sf::RectangleShape> plats, float elapsedTime);
    void setHome(int home);
    void generateHome(int homes[]);
    void update(Player *player, float elapsedTime, std::vector<sf::RectangleShape> plats);
    void spawn(std::vector<sf::RectangleShape> plats);
};

#endif //TEAMPROJECT_ENEMIES_H