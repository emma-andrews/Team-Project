#ifndef TEAMPROJECT_ENGINE_H
#define TEAMPROJECT_ENGINE_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Engine {
private:
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Text levelText;
    sf::Text livesText;
    sf::Font font;
    Player player;
    void input();
    void update(float dtAsSeconds);
    void draw();
public:
    Engine();
    void start();
};

#endif //TEAMPROJECT_ENGINE_H
