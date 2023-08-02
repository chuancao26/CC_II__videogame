#ifndef FLYINGFIST_H
#define FLYINGFIST_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Enemigos.h"
#include <random>
class FlyingFistM : public Enemigo
{
private:
    float angle, scale, elapsedTime, speed, upSpeed;
    bool inPosition;
    int xBorder, yBorder, rotationSize, type;
    std::mt19937 generator;
    std::uniform_int_distribution<int> genNum, rotationGen;
    float positionX;

public:
    FlyingFistM(const int& xBorder_, const int& yBorder_, const int& type_): xBorder(xBorder_), yBorder(yBorder_),
    Enemigo(xBorder_ * 1/3, yBorder_, 50), speed(0.02f), inPosition(false), scale(1.0f), angle(0.0f), type(type_),
    upSpeed(5.0f)
    {
        std::random_device rd;
        generator.seed(rd());
        genNum = std::uniform_int_distribution<int>(0,xBorder);
        positionX = static_cast<float>(genNum(generator));
        rotationGen = std::uniform_int_distribution<int>(300,600);
        rotationSize = static_cast<int>(rotationGen(generator));
        (type == 1) ? posx = positionX - cos(angle) * rotationSize : posx = positionX + cos(angle) * rotationSize;
        


    }
    void update(const float& elapsedTime_)
    {
        elapsedTime = elapsedTime_;
        move();
    }
    void move()
    {
        if (!inPosition)
        {
            if (posy >= yBorder / 2 - 3 && posy <= yBorder / 2 + 3)
            {
                inPosition = true;
            }
            if (posy > yBorder / 2 )
            {
                posy -= upSpeed;
            }

        }
        else
        {
            (type == 1) ? posx = positionX - cos(angle) * rotationSize : posx = positionX + cos(angle) * rotationSize;
            posy = yBorder / 2 + sin(angle) * rotationSize/2;

            angle += speed;
        }
    }
    float getPosx()
    {
        return posx;
    }
    float getPosy()
    {
        return posy;
    }
    float getElapsedTime()
    {
        return elapsedTime;
    }
    float getScale()
    {
        return scale;
    }
};
class FlyingFistV
{
private:
    std::shared_ptr<FlyingFistM> fist;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
public:
    FlyingFistV(std::shared_ptr<FlyingFistM> fist_,
                const std::vector<std::shared_ptr<sf::Texture>>& textures_):fist(fist_),
                textures(textures_)
    {

    }
    void update()
    {  
        updateTextures();
        move();
    }
    void updateTextures()
    {
        size_t textureIndex = static_cast<size_t>(std::round(fist ->getElapsedTime() * 6)) % textures.size();
        sprite.setScale(fist->getScale(), fist->getScale());
        sprite.setTexture(*textures[textureIndex]);
    }
    void move()
    {
        sprite.setPosition(fist ->getPosx(), fist ->getPosy());
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
    sf::Sprite& getSprite()
    {
        return sprite;
    }
};
#endif 