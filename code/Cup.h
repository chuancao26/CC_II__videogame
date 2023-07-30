#ifndef CUP_H
#define CUP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "Textures.h"
#include <random> 
class CupHeadM
{
private:
    float posx, posy, speed, gravity, deltaTime, elapsedTime, sizeX, sizeY, jumpY, scale;
    bool left, right, jump, bottom, inPlatform;
    int xBorder, yBorder;

public:
    CupHeadM(const float& posx_, const float& posy_, const int& xBorder_, const int& yBorder_) : 
    posx(posx_),posy(posy_), speed(200.0f), deltaTime(0.0f), gravity(5.0f), left(false), right(false),
    jump(false), bottom(false), xBorder(xBorder_), yBorder(yBorder_), jumpY(200.f), inPlatform(false),
    scale(0.50f)
    {
    }
    void move()
    {
        direction();
    }
    void direction()
    {
        if (left)
        {
            posx -= speed * deltaTime;
        }
        if (right)
        {
             posx += speed * deltaTime;
        }
        if (jump && inPlatform)
        {
            posy -= jumpY;
        }
        if (bottom)
        {
            posy += speed * deltaTime;
        }
    }
    void update(const float& deltaTime_,const bool& left_, const bool& right_, const bool& jump_, const bool& inPlatform_) 
    {
        elapsedTime += deltaTime_; 
        deltaTime = deltaTime_;
        left = left_;
        right = right_;
        jump = jump_;
        inPlatform = inPlatform_;
        move();
        gravedad();
    }
    void gravedad()
    {  
        if (!inPlatform)
            posy += gravity;
    }
    float getPosX(){return posx;}
    float getPosY(){return posy;}
    bool isJumping(){return jump;}
    bool isLeft(){return left;}
    bool isRight(){return right;}
    float getScale(){return scale;}
    float getDeltaTime(){return deltaTime;}
    float getElapsedTime(){return elapsedTime;}
    bool isInPlatform(){return inPlatform;}
    // bool isLeft(){return left;}

};
class CupHeadV
{
private:
    sf::Sprite sprite;
    std::shared_ptr<CupHeadM> cupM; 
    std::vector<std::shared_ptr<sf::Texture>> runTexture;
    std::vector<std::shared_ptr<sf::Texture>> jumpTexture;
    std::vector<std::shared_ptr<sf::Texture>> standingTexture;
public:
    CupHeadV(const std::shared_ptr<CupHeadM>& cupM_, std::vector<std::shared_ptr<sf::Texture>> runTexture_,
            std::vector<std::shared_ptr<sf::Texture>> jumpTexture_,
            std::vector<std::shared_ptr<sf::Texture>> standingTexture_):cupM(cupM_), runTexture(runTexture_),
            jumpTexture(jumpTexture_), standingTexture(standingTexture_)
    {
    }
    void update()
    {
        updateTextures();
    }
    void updateTextures()
    {
        std::cout << cupM->isInPlatform() << std::endl;
        if (cupM->isLeft())
        {
            size_t textureIndex = static_cast<size_t>(std::round(cupM->getElapsedTime()* 10)) % (runTexture.size());
            sprite.setScale(-cupM->getScale(), cupM->getScale());
            sprite.setTexture(*runTexture[textureIndex]);

            sprite.setPosition(cupM->getPosX(), cupM->getPosY());
        }
        if (cupM->isRight())
        {
            size_t textureIndex = static_cast<size_t>(std::round(cupM->getElapsedTime()* 10)) % (runTexture.size());
            sprite.setScale(cupM->getScale(), cupM->getScale());
            sprite.setTexture(*runTexture[textureIndex]);
            sprite.setPosition(cupM->getPosX(), cupM->getPosY());
        }
        if (cupM->isJumping() || !cupM->isInPlatform())
        {
            size_t textureIndex = static_cast<size_t>(std::round(cupM->getElapsedTime()* 10)) % (jumpTexture.size());
            sprite.setScale(cupM->getScale(), cupM->getScale());
            sprite.setTexture(*jumpTexture[textureIndex]);
            sprite.setPosition(cupM->getPosX(), cupM->getPosY());
        }
        if (!cupM->isLeft() && !cupM->isRight() && !cupM->isJumping())
        {
            size_t textureIndex = static_cast<size_t>(std::round(cupM->getElapsedTime()* 10)) % (standingTexture.size());
            sprite.setScale(cupM->getScale(), cupM->getScale());
            sprite.setTexture(*standingTexture[textureIndex]);
        }
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
        sprite.setPosition(cupM->getPosX(), cupM->getPosY());
        
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};
#endif
