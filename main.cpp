#include <iostream>
#include <SFML/Graphics.hpp>
#include "Engine.h"

/* Welcome to our platformer!
There will be multiple .cpp and .h files with this project, so make sure you are working in the correct one
Engine.cpp defines all the game rendering and game time processing that is done
Player.cpp defines the player character and its attributes, but input for it is located in ENGINE.CPP
Levels.cpp defines all the map based items, including the imported tile sets Emma will be making
Enemies.cpp defines the enemy movements, which requires AI components, so pathing towards the player, etc.
If you have any questions about SFML, you can find the documentation here: https://www.sfml-dev.org/documentation/2.4.2/index.php
Additionally, there are many resources out there for learning how to code a 2D platformer, and even if they do not use SFML, it will still be similar
Please remember to push early and often! We do not want any lost work (if you want, you can create your own branch for what you are working on)

 FEATURES TO DO: (~~~ indicates std line count increase)
 scoring system
 not proceed in level until all coins are picked up
 animate enemies
 ~~~write to a file to keep high scores
 bonus level
 ~~~create different enemy types
 create different types of platforms
 vary size of platforms
 add platform texture
 animate FINISH to look like a sign in background
 add sounds
 ~~~error catching if engine, files failed to load
 ask for player name at beginning*/

int main() {
    Engine engine;//creates engine and starts it
    engine.start();
    return 0;
}