#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"

Animation::Animation() {
    runTexture.loadFromFile("player character sheet.png");//loads the character sheet as a texture when an animation object is created
}

std::vector<sf::IntRect> Animation::playerRIdle() {
    //returns a vector containing rectangles of the texture for each frame in the right (player faces right) idle
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect idleSource(0, 0, 30, 40);//creates an integer rectangle with origin (0,0), width 30, and height 40
    while (idleSource.left <= 90) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(idleSource);//pushes back the rectangle to the vector
        idleSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLIdle() {
    //returns a vector containing rectangles of the texture for each frame in the left idle
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect idleSource(0, 160, 30, 40);//creates an integer rectangle with origin (0,160), width 30, and height 40
    while (idleSource.left <= 90) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(idleSource);//pushes back the rectangle to the vector
        idleSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerRRun() {
    //returns a vector containing rectangles of the texture for each frame in the right run
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect runSource(0, 40, 26, 37);//creates an integer rectangle with origin (0,40), width 26, and height 37
    while (runSource.left <= 150) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(runSource);//pushes back the rectangle to the vector
        runSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLRun() {
    //returns a vector containing rectangles of the texture for each frame in the left run
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect runSource(0, 120, 26, 37);//creates an integer rectangle with origin (0,120), width 26, and height 37
    while (runSource.left <= 150) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(runSource);//pushes back the rectangle to the vector
        runSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerRJump() {
    //returns a vector containing rectangles of the texture for each frame in the right jump
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    bool second = false;
    sf::IntRect jumpSource(0, 80, 26, 37);//creates an integer rectangle with origin (0,80), width 26, and height 37
    while (jumpSource.left <= 70) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(jumpSource);//pushes back the rectangle to the vector
        if (!second) {//since the second frame is much larger in size than the first frame, left will be increased by 30 then 35
            jumpSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
            second = true;
        }
        if (second) {
            jumpSource.left += 35;//now on the second frame, which has a width of 35
        }
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLJump() {
    //returns a vector containing rectangles of the texture for each frame in the left jump
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    bool second = false;
    sf::IntRect jumpSource(69, 80, 30, 35);//creates an integer rectangle with origin (69,80), width 30, and height 35
    while (jumpSource.left <= 134) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(jumpSource);//pushes back the rectangle to the vector
        if (!second) {//since the second frame is much larger in size than the first frame, left will be increased by 30 then 40
            jumpSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
            second = true;
        }
        if (second) {
            jumpSource.left += 40;//now on the second frame, which has a width of 40
        }
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerRHurt() {
    //returns a vector containing rectangles of the texture for each frame in the right hurt after the player loses a life
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect hurtSource(0, 200, 34, 40);//creates an integer rectangle with origin (0,200), width 34, and height 40
    while (hurtSource.left <= 34) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(hurtSource);//pushes back the rectangle to the vector
        hurtSource.left += 35;//moves the left side of the rectangle over 35 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::playerLHurt() {
    //returns a vector containing rectangles of the texture for each frame in the left hurt
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect hurtSource(40, 200, 34, 40);//creates an integer rectangle with origin (40,200), width 34, and height 40
    while (hurtSource.left <= 34) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(hurtSource);//pushes back the rectangle to the vector
        hurtSource.left += 35;//moves the left side of the rectangle over 35 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::coinTurn() {
    //returns a vector containing rectangles of the texture for each frame of the coin/jewel turning
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect turnSource(0, 0, 16, 16);//creates an integer rectangle with origin (0,0), width 16, and height 16
    while (turnSource.left <= 95) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(turnSource);//pushes back the rectangle to the vector
        turnSource.left += 16;//moves the left side of the rectangle over 16 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::chestOpen() {
    //returns a vector containing rectangles of the texture for each frame of the chest opening
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect openSource(0, 0, 16, 16);//creates an integer rectangle with origin (0,0), width 16, and height 16
    while (openSource.left <= 48) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(openSource);//pushes back the rectangle to the vector
        openSource.left += 17;//moves the left side of the rectangle over 17 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::batFly() {
    //returns a vector containing rectangles of the texture for each frame of the bat flying
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect flySource(0, 0, 50, 30);//creates an integer rectangle with origin (0,0), width 50, and height 30
    while (flySource.left <= 250) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(flySource);//pushes back the rectangle to the vector
        flySource.left += 50;//moves the left side of the rectangle over 50 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::slime() {
    //returns a vector containing rectangles of the texture for each frame of the slime moving/idling
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect moveSource(0, 0, 30, 27);//creates an integer rectangle with origin (0,0), width 30, and height 27
    while (moveSource.left <= 120) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(moveSource);//pushes back the rectangle to the vector
        moveSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::slime2() {
    //returns a vector containing rectangles of the texture for each frame of the second slime moving/idling
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect moveSource(0, 0, 30, 32);//creates an integer rectangle with origin (0,0), width 30, and height 32
    while (moveSource.left <= 120) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(moveSource);//pushes back the rectangle to the vector
        moveSource.left += 30;//moves the left side of the rectangle over 30 pixels in the positive x-direction
    }
    return vect;
}

std::vector<sf::IntRect> Animation::potion() {
    //returns a vector containing rectangles of the texture for each frame of the potion bubbling inside the jar
    std::vector<sf::IntRect> vect;//creates a vector of integer rectangles
    sf::IntRect jarSource(0, 0, 20, 22);//creates an integer rectangle with origin (0,0), width 20, and height 22
    while (jarSource.left <= 80) {//gets all the frames of this animation on the sprite sheet
        vect.push_back(jarSource);//pushes back the rectangle to the vector
        jarSource.left += 20;//moves the left side of the rectangle over 20 pixels in the positive x-direction
    }
    return vect;
}