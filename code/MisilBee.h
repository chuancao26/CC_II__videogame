#ifndef MISILBEE_H
#define MISILBEE_H
#include "Enemigos.h"
#include <iostream>
#include <memory>
class MisilM : public Enemigo
{
    private:
        int width, height, sizeY, sizeX;
        float avance, speed, scale, elapsedTime, factorSpeed;
        bool moveLeft, moveUp, avanceFlag, change;
    public:
        // Constructor
        MisilM(const int& width, const int& height):width(width), change(false),
        height(height), avance(0.0f), speed(10.0f), moveLeft(true), moveUp(false),
        scale(1.0f), avanceFlag(false), Enemigo(width* 0.5f, height * 0.9f, 100), sizeY(50), sizeX(size)
        {
        }
        void update(const float& elapsedTime_)
        {
            elapsedTime = elapsedTime_;
            move();
        }
        void move()
        {
            if (moveLeft && !moveUp)
            {
                posx -= speed;
            }
            if (!moveLeft && !moveUp)
            {   
                posx += speed;
            }
            if (posx >= 0.5 * width)
            {
                moveLeft = true;
                moveUp = true;
                if (!avanceFlag)
                {
                    change = false;
                    avance = posy;
                    avanceFlag = true;
                }
            }
            if (posx <= 0.05 * width)
            {
                moveLeft = false;
                moveUp = true;
                
                if (!avanceFlag)
                {
                    change = false;
                    avance = posy;
                    avanceFlag = true;
                }
            }
            if (moveUp)
            {
                posy -= speed;
                if (avance - posy >= height * 0.15)
                {
                    change = true;
                    avanceFlag = false;
                    moveUp = false;
                }
            }

            if (posy <= 0 && !moveUp)
            {
                posy = height * 0.1;
            }
        }
        bool isExpired()
        {
            return posy <= 0 - sizeY ? true : false; 
        }
        int getWidth(){return width;}
        int getHeight(){return height;}
        float getAvance(){return avance;}
        float getSpeed(){return speed;}
        bool getMoveLeft(){return moveLeft;}
        int getGetYsize(){return sizeY;}
        int getGetXsize(){return sizeX;}
        float getPosX(){return posx;}
        float getPosY(){return posy;}
        bool getavanceFlag(){return avanceFlag;}
        bool getChange(){return change;}
        void setPosX(const float& posx_){posx = posx_;}
        void setPosY(const float& posy_){posy = posy_;}
        float getScale(){return scale;}
};
class MisilV
{
    private:
    std::shared_ptr<MisilM> misilm;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    float elapsedTime;
    public:
    MisilV(std::shared_ptr<MisilM> a, std::vector<std::shared_ptr<sf::Texture>> textures_):misilm(a), 
    textures(textures_)
    {
        
    }
    void update(const float& elapsedTime_)
    {
        elapsedTime = elapsedTime_;
        move();
        updateTextures();
    }
    void updateTextures()
    {
        size_t textureIndex = static_cast<size_t>(std::round(elapsedTime * 6)) % textures.size();
        sprite.setScale(misilm->getScale(), misilm->getScale());
        sprite.setTexture(*textures[textureIndex]);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    void move()
    {
        if ( misilm->getPosX() >= 0.5 * misilm->getWidth())
        {
            // misil.setSize(sf::Vector2f(misilm->getGetYsize(),misilm->getGetXsize()));
            sprite.setRotation(90.0f);
            if(!misilm -> getavanceFlag())
            {
                misilm->setPosY(misilm->getPosY() - 50);
            }
        }
        if ( misilm->getPosX() <= 0.05 * misilm->getWidth())
        {
            // misil.setSize(sf::Vector2f(misilm->getGetYsize(),misilm->getGetXsize()));
            sprite.setRotation(90.0f);
            if(!misilm -> getavanceFlag())
            {
                misilm->setPosY(misilm->getPosY() - 50);
            }
        }
        if (misilm->getChange())
        {
            if (!misilm->getMoveLeft())
            {
                sprite.setRotation(180.f);
            }
            else
            {
                sprite.setRotation(0.0f);
            }
        }
        sprite.setPosition(misilm->getPosX(), misilm->getPosY());

    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

#endif