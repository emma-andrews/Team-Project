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
    sf::Texture sTexture;
    sf::Texture bTexture;
    sf::Texture ssTexture;
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
    bool slime;
    bool slime2;
    bool bat;
    bool kill;


public:
    sf::Clock eAniClock;
    sf::Time tp;
    bool killed;

    Enemies();
    std::vector<Enemies> enemyVect;
    sf::Sprite getSprite();
    int checkCollision(sf::Sprite player, bool invulnerable);
    void moveLeft(float elapsedTime);
    void moveRight(float elapsedTime);
    void setPosition(std::vector<sf::RectangleShape> plats);
    void engage(float elapsedTime, sf::Sprite player);
    void patrol(std::vector<sf::RectangleShape> plats, float elapsedTime);
    void setHome(int home);
    void generateHome(int homes[]);
    int update(Player *player, float elapsedTime, std::vector<sf::RectangleShape> plats);
    void spawn(std::vector<sf::RectangleShape> plats);
    bool checkKill (sf::Sprite player);
    void setDead(sf::RectangleShape plat);
};

#endif //TEAMPROJECT_ENEMIES_H