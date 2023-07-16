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
    float life, xSpeed, ySpeed, scale;
public:
    // constructor
    WorkerBeeM(const float& posx_, const float& posy_):
    Enemigo(posx_, posy_, 50), xSpeed(0.2), ySpeed(0.1), life(100), scale(1.0f)// to define
    {
    }

    void move()
    {
        posx -= xSpeed;
        posy -= ySpeed;
    }
    void update()
    {
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
};
class WorkerBeeV
{
    private:
        std::shared_ptr<WorkerBeeM> wb;
        std::vector<std::shared_ptr<sf::Texture>> textures;
        sf::Sprite sprite;
        float rateTexture;

    public:
        WorkerBeeV(std::shared_ptr<WorkerBeeM> wb_, const std::vector<std::shared_ptr<sf::Texture>>& textures_): wb(wb_),
        textures(textures_)
        {
        }
        void update(const float& rateTexture_)
        {  
            rateTexture = rateTexture_;
            updateTexture();
            move();
        }
        void updateTexture()
        {
            size_t textureIndex = static_cast<size_t>(std::round(rateTexture)) % textures.size();
            sprite.setScale(wb->getScale(), wb->getScale());
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

    };
#endif 