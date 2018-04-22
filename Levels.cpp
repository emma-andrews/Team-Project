#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Levels.h"

Levels::Levels() {
    levelNum = 0;//level number is initialized to zero
    srand(time(nullptr));//seeds the random value used for generating randomly located platforms

    texture.loadFromFile("platform.png");//loads the texture for the platforms
    lTexture = &texture;//sets the texture to a reference to the texture loaded in
    finishPlat.setTexture(lTexture);//sets the finish platform and the static stair to the texture
    staticStair.setTexture(lTexture);

    texture1.loadFromFile("platform1.png");//loads in the texture for the larger platforms to avoid stretching bu trying to use the smaller texture
    lTexture1 = &texture1;

    enemyPosition.x = 200;//sets the size of the platforms where the enemies move when they are killed by the player
    enemyPosition.y = 25;

    ssPosition.x = 100;//sets the size of the static stair
    ssPosition.y = 25;

    tposition.x = 100;//sets the size of the first platform
    tposition.y = 25;

    gPosition.x = 1920;//sets the size of the ground
    gPosition.y = 20;

    fPosition.x = 100;//sets the size of the finish platform
    fPosition.y = 20;

    plat1.setFillColor(sf::Color(107, 19, 66));//sets the color to a purple-like color
    finishPlat.setFillColor(sf::Color(107, 19, 66));
    staticStair.setFillColor(sf::Color(107, 19, 66));
    ground.setFillColor(sf::Color::Transparent);//sets the color to transparent

    plat1.setSize(tposition);//sets the size of each platform to the size of the vector passed in
    ground.setSize(gPosition);
    finishPlat.setSize(fPosition);
    staticStair.setSize(ssPosition);
    enemyDead.setSize(enemyPosition);

    fPosition.x = 1700;//sets the finish platform to (1700, 200)
    fPosition.y = 200;

    gPosition.x = 0;//sets the ground to (10, 1070);
    gPosition.y = 1070;

    enemyPosition.x = 2100;//sets the enemy dead platform to (2100, 1500) so they appear off the screen after they die
    enemyPosition.y = 1500;

    ssPosition.x = 1825;//sets the position of the static stair just in case the level is generated horribly there is a platform that can aid in completion
    ssPosition.y = 375;

    ground.setPosition(gPosition);//sets the position of each static platform
    finishPlat.setPosition(fPosition);
    enemyDead.setPosition(enemyPosition);

    platforms.push_back(ground);//pushes the ground and the finish platform to the vector containing all platforms
    platforms.push_back(finishPlat);
    platforms.push_back(staticStair);//pushes it back to the vector of all platforms, as well as the platform for dead enemies
    platforms.push_back(enemyDead);
}

int Levels::checkCollision(sf::Sprite player) {
    for (unsigned i = 0; i < platforms.size(); i++) {
        if (player.getGlobalBounds().intersects(platforms[i].getGlobalBounds())) {
            return i;//if the player's sprite intersects with any platform, return that platform's index in the vector
        }
    }
    return -1;//if no platforms were collided with, return -1
}

sf::RectangleShape Levels::getPlatforms(int index) {
    return platforms[index];//returns the platform at a specific index
}

void Levels::popPlat() {
    platforms.clear();//clears the platform vector for a new level
    platforms.push_back(ground);//adds the ground, finish, static, and enemy dead platforms back
    platforms.push_back(finishPlat);
    platforms.push_back(staticStair);
    platforms.push_back(enemyDead);
}

bool Levels::isEmpty() {//checks if the platform vector is empty or not
    if (platforms.empty())
        return true;
    else
        return false;
}

bool Levels::checkFinished(sf::Sprite player) {
    if (player.getGlobalBounds().intersects(platforms[1].getGlobalBounds())) {//finish platform is located at index 4 in platforms, static index
        return true;//if the player intersects the finish platform which is always at index one in the vector, the level is completed
    }
    else
        return false;//otherwise the level is not completed
}

void Levels::generatePlat() {//generates random platforms to fill out the rest of the level
    bool secondloop = false;
    int x = 0;
    sf::Vector2f size;
    size.x = 100;
    size.y = 25;
    sf::Vector2f eSize;
    for (int i = 0; i < 17; i++) {//loop for 17 platforms
        sf::RectangleShape plat;//platforms are rectangle shapes
        plat.setSize(size);//sets the size of these platforms to 100 by 25
        plat.setFillColor(sf::Color(107, 19, 66));//fills the platforms with a purple color
        plat.setTexture(lTexture);//sets the texture of these platforms to the texture used
        sf::Vector2f position;
        if (!secondloop) {//if not in the second loop
            x += 150;//increase the x position by 150, effectively moving them to the right by a value greater than their width to avoid overlapping
        }
        else if (secondloop) {//if the platforms are on the second loop
            x -= 200;//decrease the x value, effectively moving them to the left by a value greater than their width
            if (x < 0) {//once they go past x = 0, they reset to x = 50
                secondloop = false;//and second loop is set to false
                x = 50;
            }
        }
        if (x >= 1725) {//when the platforms go beyond an x value of 1725
            x = 1675;//x value is initially set to 1675
            secondloop = true;//they are on the second loop of platforms across the width of the screen
        }
        position.y = rand() % 800 + 140;//generate a random height for the platform, a value from 140 to 940
        position.x = x;//set the x position to the x value generated in the loops above
        plat.setPosition(position);//set the platform position to the x and y positions
        platforms.push_back(plat);//push that platform into the vector containing all platforms
    }

    int ex = 0;
    eSize.x = 160;
    eSize.y = 25;
    for (int i = 0; i < 5; i++) {//sets 5 platforms with a bigger width for the enemies to stand/patrol on
        sf::RectangleShape enemyplat;
        sf::Vector2f position;
        enemyplat.setFillColor(sf::Color(107, 19, 66));//sets the fill color to a purple
        enemyplat.setSize(eSize);//sets the size to have a width of 60 pixels greater than the regular platforms
        enemyplat.setTexture(lTexture1);//sets the texture to a longer version of the other platforms' texture
        ex += 175;//increase the x direction by 175
        if (ex >= 1725) {//if the x becomes greater than 1725
            ex = 200;//reset it to 200
        }
        position.y = rand() % 800 + 140;//again using a random height from 140 to 940
        position.x = ex;//setting the x position to the x value generated in the loops above
        enemyplat.setPosition(position);//sets the position of these platforms
        platforms.push_back(enemyplat);//pushes these platforms into the vector, and these are the last five in the vector so they are easily identified
    }
    sf::Vector2f tempPosition;
    //check for platform intersections and bad offsets in y direction
    for (unsigned i = 0; i < platforms.size(); i++) {//will loop through the entire vector of all platforms
        for (unsigned j = 0; j < platforms.size(); j++) {//and compare one platform to every other platform in the vector
            float xDifference;
            float yDifference;
            xDifference = platforms[i].getGlobalBounds().left - platforms[j].getGlobalBounds().left;//calculates the difference in the x direction between two platforms
            yDifference = platforms[i].getGlobalBounds().top - platforms[j].getGlobalBounds().top;//calculates the difference in the y direction between two platforms

            bool intersect;
            bool tooClose;
            intersect = platforms[i].getGlobalBounds().intersects(platforms[j].getGlobalBounds());//if any two platforms intersect at all, set to true
            tooClose = (xDifference > -110 && xDifference < 110) && (yDifference > -90 && yDifference < 90);//if any platforms that have an x and y difference where it would cause issues with jumping and movement, set to true

            if (i != j && (intersect || tooClose) && i != 1) {//cannot move the finish platform at index 1, will move the other platforms that intersect or are too close around it, additionally i and j cannot be the same otherwise it will be using the same platform
                tempPosition.x = platforms[i].getGlobalBounds().left;//sets the position to the same x position
                tempPosition.y = rand() % 800 + 140;//but generates a new height, still between 140 and 940
                platforms[i].setPosition(tempPosition);//sets the position to the x and y calculated
            }
        }
    }
}