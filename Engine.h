#ifndef TEAMPROJECT_ENGINE_H
#define TEAMPROJECT_ENGINE_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include "Coin.h"
#include "Chest.h"

class Engine {
private:
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Event event;

    sf::Text levelText;
    sf::Text livesText;
    sf::Text scoreText;
    sf::Text finishText;
    sf::Text endplatText;
    sf::Text timeText;
    sf::Text closeText;
    sf::Text stuckText;
    sf::Text startText;
    sf::Font font;

    Player player;
    Levels level;
    Coin coin;
    Chest chest;

    bool levelFinished;
    bool chestOpen;
    bool startup;
    int playerLives;
    int score;
    float lGameTime;
    void input();
    void update(float dtAsSeconds, float totalTime);
    void draw();
    void nextLevel();

public:
    Engine();
    void start();
};

#endif //TEAMPROJECT_ENGINE_H
