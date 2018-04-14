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
    Player player;
    Levels level;
    void input();
    void update(float dtAsSeconds);
    void draw();
public:
    Engine();
    void start();
};

#endif //TEAMPROJECT_ENGINE_H
