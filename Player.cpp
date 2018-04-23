#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Levels.h"
#include <vector>
#include <iostream>

const float maxY = 2.5f;
const float gravity = 30.0f;
sf::IntRect textRect(0, 0, 30, 40);
Player::Player() {
    pSpeed = 400;//speed of the player
    rFrame = 0;//initializes the frame counts for the animations to 0
    lFrame = 0;
    irFrame = 0;
    ilFrame = 0;
    jrFrame = 0;
    jlFrame = 0;
    lives = 3;//start with 3 lives
    score = 0;//score is initially 0

    pTexture.loadFromFile("player character sheet.png");
    pSprite.setTexture(pTexture);//sets the texture of the player to be the sheet of all frames of the player
    pSprite.setTextureRect(textRect);//sets the current texture of the sprite to the rectangle starting at position 0,0 and extending to 30 by 40
    pSprite.setScale(2,2);//scales sprite by 2 so it is 64 by 64
    pPosition.x = 50;//initial starting position
    pPosition.y = 920;
}

sf::Sprite Player::getSprite() {
    return pSprite;//get the sprite of the player
}

void Player::setPosition() {
    pPosition.x = 500;//sets the position of the player back to the initial starting point
    pPosition.y = 800;
    pSprite.setPosition(pPosition);
}

void Player::moveLeft() {
    pLeftPressed = true;//able to move left
}

void Player::moveRight() {
    pRightPressed = true;//able to move right
}

void Player::stopLeft() {
    pLeftPressed = false;//not able to move left
}

void Player::stopRight() {
    pRightPressed = false;//not able to move right
}

void Player::jump() {
    pJump = true;//input to jump
    if(canJump) {//able to jump based on current position
        pVelocity.y = -12.0f;
        canJump = false;//unable to jump while already in a jump
    }
}

void Player::setSpeed(int speed) {
    //sets the speed of the player
    this->pSpeed = speed;
}

void Player::stopJump() {
    pJump = false;//no input to jump
    if (pVelocity.y < -6.0f) {
        pVelocity.y = -6.0f;//no longer moving down
    }
}

void Player::update(float elapsedTime, int collision, std::vector<sf::RectangleShape> plats) {
    pPosition.x += pVelocity.x * elapsedTime;//calculate position and velocity for gravity
    pPosition.y += pVelocity.y * gravity * elapsedTime * 3;
    pVelocity.y += gravity * elapsedTime;
    if (pPosition.y > 920) {
        //sets the ground to 920, preventing player from going off the bottom of the screen
        pPosition.y = 920;
        canJump = true;//player is able to jump from the ground
    }
    if (pRightPressed) {
        //if the player presses d to go right
        rightLast = true;//right was the last direction the player was moving in
        leftLast = false;
        pPosition.x += pSpeed * elapsedTime;//increase the position by the the speed over a period of elapsed time
        if (pPosition.x >= sf::VideoMode::getDesktopMode().width - 64)
            //player is not able to run off the right of the screen
            pPosition.x = sf::VideoMode::getDesktopMode().width - 74;

        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {//changes the frame every 0.1 seconds
            aniRect = animation.playerRRun();//sets a vector to contain all of the frames of the animation
            pSprite.setTextureRect(aniRect[rFrame]);//sets the rectangle texture to the current frame
            rFrame++;//increases the frame count by one
            if (rFrame >= aniRect.size()) {//if the frame count is greater or equal to the size of the animation vector
                rFrame = 0;//reset the frame count to zero to create a looping animation
            }
            aniClock.restart();//restarts the clock
        }
    }

    if (pLeftPressed) {
        //if the player presses a to go left
        leftLast = true;//the player was last moving in the left direction
        rightLast = false;
        pPosition.x -= pSpeed * elapsedTime;//decrease the position by the the speed over a period of elapsed time
        if (pPosition.x <= 0)
            //player is not able to run off the left side of the screen
            pPosition.x = 10;

        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {//changes the frame every 0.1 seconds
            aniRect = animation.playerLRun();//sets a vector to contain all of the frames of the animation
            pSprite.setTextureRect(aniRect[lFrame]);//sets the rectangle texture to the current frame
            lFrame++;//increases the frame count by one
            if (lFrame >= aniRect.size()) {//if the frame count is greater or equal to the size of the animation vector
                lFrame = 0;//reset the frame count to zero to create a looping animation
            }
            aniClock.restart();//restarts the clock
        }
    }
    if (pJump && canJump) {
        //if user enters space to jump and the sprite is able to jump
        if (pPosition.y > 0) {
            //go up
            pPosition.y -= maxY;
        }
        else if (pPosition.y == 0) {
            //until they reach max y, then fall down
            pPosition.y += maxY;
        }
    }
    if (pJump) {
        //if the user is pressing space to jump, cycle through animations depending on what direction they were last headed in
        if (rightLast) {
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {//changes the frame every 0.2 seconds
                aniRect = animation.playerRJump();//sets a vector to contain all of the frames of the animation
                pSprite.setTextureRect(aniRect[jrFrame]);//sets the rectangle texture to the current frame
                jrFrame++;//increases the frame count by one
                if (jrFrame >= aniRect.size()) {//if the frame count is greater or equal to the size of the animation vector
                    jrFrame = aniRect.size() - 1;//reset the current frame to the last frame
                }
                aniClock.restart();//restarts the clock
            }
        }
        else if (leftLast) {
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {//changes the frame every 0.2 seconds
                aniRect = animation.playerLJump();//sets a vector to contain all of the frames of the animation
                pSprite.setTextureRect(aniRect[jlFrame]);//sets the rectangle texture to the current frame
                jlFrame++;//increases the frame count by one
                if (jlFrame >= aniRect.size()) {//if the frame count is greater or equal to the size of the animation vector
                    jlFrame = aniRect.size() - 1;//reset the current frame to the last frame
                }
                aniClock.restart();//restarts the clock
            }
        }
    }
    if (collision >= 0) {
        //if the player collides with a platform, check which side of the platform they collide with
        bool collideBottom = pPosition.y > plats[collision].getGlobalBounds().top;
        bool collideLeft = (pPosition.y + pSprite.getGlobalBounds().height) > plats[collision].getGlobalBounds().top &&
                           (pPosition.x + pSprite.getGlobalBounds().width) > plats[collision].getGlobalBounds().left &&
                           (pPosition.x + pSprite.getGlobalBounds().width) < plats[collision].getGlobalBounds().left + 5;
        bool collideRight = (pPosition.y + pSprite.getGlobalBounds().height) > plats[collision].getGlobalBounds().top &&
                            (pPosition.x) < plats[collision].getGlobalBounds().left + plats[collision].getGlobalBounds().width &&
                            (pPosition.x) > plats[collision].getGlobalBounds().left + plats[collision].getGlobalBounds().width - 5;
        if (collideBottom) {
            //if they collide with the bottom of the platform, move back down in the y direction
            pPosition.y = plats[collision].getGlobalBounds().top + plats[collision].getGlobalBounds().height;
            pVelocity.y = 6.0f;
        }
        else if (collideLeft) {
            //if they collide with the left of the platform, move right at a small velocity
            pPosition.x = plats[collision].getGlobalBounds().left - pSprite.getGlobalBounds().width;
            pVelocity.y += 0.05f;
        }
        else if (collideRight) {
            //if they collide with the right of the platform, move left at a small velocity
            pPosition.x = plats[collision].getGlobalBounds().left + plats[collision].getGlobalBounds().width;
            pVelocity.y += 0.05f;
        }
        else {
            //otherwise they are colliding with the top of the platform and the y position will be set to the top of the platform minus the height of the sprite
            pPosition.y = plats[collision].getGlobalBounds().top - pSprite.getGlobalBounds().height;
            pVelocity.y = 0;//velocity in the y direction is zero
            canJump = true;//sprite is able to jump
        }
    }
    if (!pLeftPressed && !pRightPressed && !pJump) {
        //if no inputs are received, player is idling
        if (rightLast) {
            //if they were last moving in the right direction, idle on the right side
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {//changes the frame every 0.2 seconds
                aniRect = animation.playerRIdle();//sets a vector to contain all of the frames of the animation
                pSprite.setTextureRect(aniRect[irFrame]);//sets the rectangle texture to the current frame
                irFrame++;//increases the frame count by one
                if (irFrame >= aniRect.size()) {//if the frame count is greater or equal to the size of the animation vector
                    irFrame = 0;//reset the frame count to zero to create a looping animation
                }
                aniClock.restart();//restarts the clock
            }
        }
        else if (leftLast) {
            //if they were last moving in the left direction, idle on the left side
            if (aniClock.getElapsedTime().asSeconds() > 0.2f) {//changes the frame every 0.2 seconds
                aniRect = animation.playerLIdle();//sets a vector to contain all of the frames of the animation
                pSprite.setTextureRect(aniRect[ilFrame]);//sets the rectangle texture to the current frame
                ilFrame++;//increases the frame count by one
                if (ilFrame >= aniRect.size()) {//if the frame count is greater or equal to the size of the animation vector
                    ilFrame = 0;//reset the frame count to zero to create a looping animation
                }
                aniClock.restart();//restarts the clock
            }
        }
    }
    pSprite.setPosition(pPosition);//sets the position of the sprite
}

void Player::setLives(int num) {
    //sets the lives to what is passed in
    lives = num;
}

int Player::getLives() {
    //returns the number of lives the player currently has
    return lives;
}

bool Player::checkInteraction(sf::Sprite chest) {
    if (pSprite.getGlobalBounds().intersects(chest.getGlobalBounds())) {
        //drop chance for either score increase or extra life if the player intersects the chest
        int chance = rand() % 2 + 1;
        if (chance == 1) {
            //increase life count
            lives++;
        }
        else if (chance == 2) {
            //increase score by 100
            score += 100;
        }
        return true;//player did interact with the chest
    }
    else {
        return false;//player did not interact with the chest
    }
}

int Player::getScore() {
    //returns the current score
    return score;
}

void Player::setScore(int num) {
    //sets the score by increasing its amount by what has been passed in
    score += num;
}

int Player::getX() {
    //returns the x position of the player
    return pPosition.x;
}

int Player::getY() {
    //returns the y position of the player
    return pPosition.y;
}

void Player::bounceBack(int direction) {
    if (direction == 1) {//moving right when collided
        pPosition.x -= pSpeed * 0.15f;//move in the opposite direction at the current speed for 0.15 seconds
        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerRHurt();//plays the hurt animation for 0.1 seconds
            pSprite.setTextureRect(aniRect[0]);//only one frame in the vector
            aniClock.restart();//restarts the clock
        }
    }
    else if (direction == 2) {//moving left when collided
        pPosition.x += pSpeed * 0.15f;//move in the opposite direction at the current speed for 0.15 seconds
        if (aniClock.getElapsedTime().asSeconds() > 0.1f) {
            aniRect = animation.playerLHurt();//plays the hurt animation for 0.1 seconds
            pSprite.setTextureRect(aniRect[0]);//only one frame in the vector
            aniClock.restart();//restarts the clock
        }
    }
}