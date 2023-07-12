#ifndef MISILBEE_H
#define MISILBEE_H
#include "Enemigos.h"
#include <iostream>
#include <memory>
class MisilM : public Enemigo
{
    private:
        int width, height, sizeY, sizeX;
        float avance, speed;
        bool moveLeft, moveUp, avanceFlag, change;
    public:
        // Constructor
        MisilM(const int& width, const int& height):width(width), change(false),
        height(height), avance(0.0f), speed(0.1f), moveLeft(true), moveUp(false),
        avanceFlag(false), Enemigo(width* 0.5f, height * 0.9f, 100), sizeY(50), sizeX(size)
        {
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
};
class MisilV
{
    private:
    sf::RectangleShape misil;
    sf::Color color;
    std::shared_ptr<MisilM> misilm;
    public:
    MisilV(std::shared_ptr<MisilM> a): color(sf::Color::Yellow), misilm(a)
    {
        misil.setFillColor(color);
        misil.setSize(sf::Vector2f(misilm->getGetXsize(), misilm->getGetYsize()));
        misil.setPosition(misilm->getPosX(), misilm->getPosY());
    }
    void update()
    {
        move();
    }
    void move()
    {
        if ( misilm->getPosX() >= 0.5 * misilm->getWidth())
        {
            misil.setSize(sf::Vector2f(misilm->getGetYsize(),misilm->getGetXsize()));
            if(!misilm -> getavanceFlag())
            {
                misilm->setPosY(misilm->getPosY() - 50);
            }
        }
        if ( misilm->getPosX() <= 0.05 * misilm->getWidth())
        {
            misil.setSize(sf::Vector2f(misilm->getGetYsize(),misilm->getGetXsize()));
            if(!misilm -> getavanceFlag())
            {
                misilm->setPosY(misilm->getPosY() - 50);
            }
        }
        if (misilm->getChange())
        {
            misil.setSize(sf::Vector2f(misilm->getGetXsize(),misilm->getGetYsize()));
        }
        misil.setPosition(misilm->getPosX(), misilm->getPosY());

    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(misil);
    }
};

#endif