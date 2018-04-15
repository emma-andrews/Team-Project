#ifndef TEAMPROJECT_ENGINE_H
#define TEAMPROJECT_ENGINE_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"

class Engine {
private:
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;

    sf::Text levelText;
    sf::Text livesText;
    sf::Text finishText;
    sf::Font font;

    Player player;
    Levels level;

    bool levelFinished;
    void input();
    void update(float dtAsSeconds);
    void draw();
    void nextLevel();

public:
    Engine();
    void start();
};

#endif //TEAMPROJECT_ENGINE_H
