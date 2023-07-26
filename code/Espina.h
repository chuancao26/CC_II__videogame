#ifndef ESPINA_H
#define ESPINA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
class EspinaM
{
private:
    float posx, posy, speed, scale, elapsedTime;
    int size, xBorder, yBorder;
    char type;
public:
    // constructor
    EspinaM(const float& posx_, const float& posy_, const char& type_, 
    const int& xBorder_, const int& yBorder_):
    size(30), posx(posx_), posy(posy_), speed(20.0f), scale(1.0f), 
    type(type_), xBorder(xBorder_), yBorder(yBorder_)
    {
    }
    void update(const float& elapsedTime_)
    {
        move();
        elapsedTime = elapsedTime_;
    }
    void move()
    {
        // r is right
        // l is left
        // u is upward
        // d is downward
        // a is upward left
        // b is upward right 
        // c is downward left
        // d is downward right
        if(type == 'a') // is upward left 
        {
            
            posx -= speed;
            posy -= speed; 
        }
        if(type == 'b') // is upward Right
        {
            posx += speed;
            posy -= speed;
        }
        if(type == 'c') // is downward left
        {
            posx -= speed;
            posy += speed;
        }
        if(type == 'e') // is downward right
        {
            posx += speed;
            posy += speed;
        }
        if(type == 'r') 
        {
            posx += speed;
        }
        if(type == 'l')
        {
            posx -= speed;
        }
        if(type == 'u')
        {
            posy -= speed;
        }
        if(type == 'd')
        {
            posy += speed;
        }
    }
    bool isExpired()
    {
        if (posx <= -size || posy <= -size || posx >= xBorder + size || posy >= yBorder + size )
        {
            return true;
        }
        return false;
    }
    float getPosx(){return posx;}
    float getPosy(){return posy;}
    int getSize(){return size;}
    char getType(){return type;}
    float getScale(){return scale;}
    float getTime(){return elapsedTime;}
};
class EspinaV
{
private:
    std::shared_ptr<EspinaM> e;
    sf::Sprite sprite;
    std::vector<std::shared_ptr<sf::Texture>> textures;
public:
    EspinaV(std::shared_ptr<EspinaM>& espina_, const std::vector<std::shared_ptr<sf::Texture>>& textures_):
    e(espina_), textures(textures_)
    {
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
    void move()
    {
        sprite.setPosition(e->getPosx(), e->getPosy());
    }
    void update()
    {
        move();
        updateTexture();
    }
    void updateTexture()
    {
        size_t textureIndex = static_cast<size_t>(std::round(e->getTime() * 6)) % textures.size();
        sprite.setScale(e->getScale(), e->getScale());
        sprite.setTexture(*textures[textureIndex]);
        if(e->getType() == 'l')
        {
            sprite.setScale(-e->getScale(), e->getScale());
        }
        else if(e->getType() == 'u')
        {
           sprite.setRotation(270.0f); 
        }
        else if(e->getType() == 'd')
        {
            sprite.setRotation(90.0f);
        }
        else if(e->getType() == 'c') // is upward left 
        {
            sprite.setRotation(135.0f);
        }
        else if(e->getType() == 'e') // is upward Right
        {
            sprite.setRotation(45.0f);
        }
        else if(e->getType() == 'a') // is downward left
        {
            sprite.setRotation(225.0f);
        }
        else if(e->getType() == 'b') // is downward right
        {
            sprite.setRotation(315.0f);
        }
        sprite.setPosition(e->getPosx(), e->getPosy());
    }
};
#endif