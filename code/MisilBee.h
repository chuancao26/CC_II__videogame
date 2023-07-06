#ifndef MISILBEE_H
#define MISILBEE_H
#include "Enemigos.h"
class MisilM : public Enemigo
{
    private:
        int width, height, sizeY;
        float avance, speed;
        bool moveLeft, moveUp, avanceFlag;
    public:
        // Constructor
        MisilM(const int& width, const int& height):width(width),
        height(height), avance(0.0f), speed(0.01f), moveLeft(true), moveUp(false),
        avanceFlag(false), Enemigo(width* 0.5f, height * 0.9f, 100), sizeY(50)
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
                rect.setSize(sf::Vector2f(50,100));
                if (!avanceFlag)
                {
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
                    avance = posy;
                    avanceFlag = true;
                }
            }
            if (moveUp)
            {
                posy -= speed;
                if (avance - posy >= height * 0.15)
                {
                    avanceFlag = false;
                    moveUp = false;
                    rect.setSize(sf::Vector2f(100,50));
                }
            }
            if (posy <= 0 && !moveUp)
            {
                posy = height * 0.1;
            }
        }
        int getWidth(){return width;}
        int getHeight(){return height;}
        float getAvance(){return avance;}
        float getSpeed(){return speed;}
        bool getMoveLeft(){return moveLeft;}
        int getGetYsize(){return sizeY;}
        int getGetXsize(){return size;}
        float getPosX(){return posx;}
        float getPosY(){return posy;}
};
class MisilV
{
    private:
    sf::RectangleShape misil;
    sf::Color color;
    MisilM* misilm;
    public:
    MisilV(MisilM*& a): color(sf::Color::Yellow), misilm(a)
    {
        misil.setFillColor(color);
        misil.setSize(sf::Vector2f(misilm->getGetXsize, misilm->getGetYsize()));
        misil.setPosition(misilm->getPosX(), misilm->getPosY());
    }
    void update()
    {
        
    }
    void move()
    {
        if ( misilm->getPosX() = 0.5 * misilm->getWidth)
        {
            rect.setSize(sf::Vector2f(50,100));
        }
    }
    void draw(sf::RenderWindow& window)
    {

    }
};

#endif