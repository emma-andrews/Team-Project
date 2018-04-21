#ifndef TEAMPROJECT_ENGINE_H
#define TEAMPROJECT_ENGINE_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include "Coin.h"
#include "Chest.h"
#include "Enemies.h"

class Engine {
private:
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Event event;
    std::vector<sf::Sprite> pHearts;
    sf::Sprite lSprite;
    sf::Texture lTexture;
    sf::Vector2f lPosition;

    sf::Text levelText;
    sf::Text livesText;
    sf::Text scoreText;
    sf::Text finishText;
    sf::Text endplatText;
    sf::Text timeText;
    sf::Text closeText;
    sf::Text stuckText;
    sf::Text startText;
    sf::Text remainText;
    sf::Text openText;
    sf::Font font;

    Player *player;
    Levels level;
    Coin coin;
    Chest chest;
    Enemies enemies[5];

    bool wait;
    bool kill;
    bool levelFinished;
    bool levelLost;
    bool flash;
    bool chestOpen;
    bool startup;
    bool alreadyOpen;
    bool exitOpen;
    int playerLives;
    int score;
    float lGameTime;
    void input();
    void update(float dtAsSeconds, float totalTime);
    void draw();
    void nextLevel();
    void gameOver();
    void playerName();

public:
    Engine();
    void start();
};

#endif //TEAMPROJECT_ENGINE_H
