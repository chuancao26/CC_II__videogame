#ifndef WORKERBEE_H
#define WORKERBEE_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
#include "Enemigos.h"
class WorkerBeeM : public Enemigo
{
private:
    float life, xSpeed, ySpeed, scale, isLeft, elapsedTime;
public:
    // constructor
    WorkerBeeM(const float& posx_, const float& posy_, const bool& isLeft_):
    Enemigo(posx_, posy_, 50), xSpeed(9.0f), ySpeed(3.0f), life(100), scale(0.80f), isLeft(isLeft_)// to define
    {
    }
    void move()
    {
        if(isLeft)
        {
            posx -= xSpeed;
            posy -= ySpeed;
        }
        else
        {
            posx += xSpeed;
            posy -= ySpeed;
        }
    }
    void update(const float& elapsedTime_)
    {
        elapsedTime = elapsedTime_;
        move();
    }
    bool isExpired()
    {
        return (posx <= -size || posy <= -size) ? true : false;
    }
    float getPosx(){return posx;}
    float getPosy(){return posy;}
    int getSize(){return size;}
    float getScale(){return scale;}
    float getElapsedTime(){return elapsedTime;}
    bool getIsLeft(){return isLeft;}
};
class WorkerBeeV
{
    private:
        std::shared_ptr<WorkerBeeM> wb;
        std::vector<std::shared_ptr<sf::Texture>> textures;
        sf::Sprite sprite;

    public:
        WorkerBeeV(std::shared_ptr<WorkerBeeM> wb_, const std::vector<std::shared_ptr<sf::Texture>>& textures_): wb(wb_),
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
            size_t textureIndex = static_cast<size_t>(std::round(wb ->getElapsedTime() * 6)) % textures.size();
            if (wb->getIsLeft())
            {
                sprite.setScale(wb->getScale(), wb->getScale());
            }
            else
            {
                sprite.setScale(-wb->getScale(), wb->getScale());
            }
            sprite.setTexture(*textures[textureIndex]);
        }
        void move()
        {
            sprite.setPosition(wb ->getPosx(), wb ->getPosy());
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