#ifndef CUP_H
#define CUP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
class CupHeadM
{
private:
    float posx, posy, speed, gravity, elapsedTime, jumpTime, sizeX, sizeY, jumpY;
    bool left, right, jump, bottom, inPlatform;
    int jumpCounter, xBorder, yBorder;

public:
    CupHeadM(const float& posx_, const float& posy_, const int& xBorder_, const int& yBorder_) : posx(posx_), posy(posy_), speed(3.0f), jump(0.0f),
    gravity(0.01f), left(false), right(false), jump(false), bottom(false), jumpCounter(0), jumpTime(0.0f),
    xBorder(xBorder_), yBorder(yBorder_), jumpY(0.1f * yBorder), inPlatform(false)
    {
    }
    void mover()
    {
        direction();
    }
    void direction()
    {
        if (left)
        {
            posx -= speed;
        }
        if (right)
        {
             posx += speed
        }
        jumping();
        if (bottom)
        {
            posy += speed;
        }
    }
    void update() 
    {
        move();
        gravedad();
    }
    void gravedad()
    {  
        if (!inPlatform)
        {
            posy += gravity;
        }
    }
    void colisionPlatform()
    {
        if (inPlatform)
        {
            jumpCounter = 0;
        }
    }
    void setLeft(const bool& left_)
    {
        left = left_;
    }
    void setRight(const bool& right_)
    {
        right = right_;
    }
    void setJump(const bool& jump_)
    {
        jump = jump_;
    }
    void jumping()
    {
        if (jump && jumpCounter < 2)
        {
            posy -= jumpY;

            ++jumpCount;
        }
    }
    bool getJumped()
    {
        if(jumpCounter == 1)
        {
            return true;
        }
        return false;
    }
};
class CupHeadV
{
private:
    std::shared_ptr<CupHeadM> cupM;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
public:
    CupHeadV(const std::shared_ptr<CupHeadM> cupheadM):cupM(cupheadM)

};
#endif
