#ifndef TRIANGULO_H
#define TRIANGULO_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
#include <iostream>
#include <memory>
class TrianguloM : public Enemigo
{
private:
    int radius, xBorder, yBorder;
    float speed, scale, rotationSpeed;
    char type;
public:
    TrianguloM(const float& posx_, const float& posy_, const int& xlimit, const int& ylimit, const char& type_):
    Enemigo(posx_, posy_, 100), speed(7.0f), xBorder(xlimit), yBorder(ylimit), scale(0.50f),
    type(type_), rotationSpeed(5.0f)
    {

    } 
    virtual void move()
    {
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
        if(type == 'a')
        {
            posx -= speed;
            posy -= speed;
        }
        if(type == 'b')
        {
            posx += speed;
            posy -= speed;
        }
        if(type == 'c')
        {
            posx -= speed;
            posy += speed;
        }
        if(type == 'e')
        {
            posx += speed;
            posy += speed;
        }
    }
    bool isExpired()
    {
        return (posx > xBorder + size * 2  || posx < 0 - size * 2 || posy > yBorder + size * 2 || posy < 0 - size * 2)? true:false;
    }
    float getPosx(){return posx;}
    float getPosy(){return posy;}
    int getSize(){return size;}
    char getType(){return type;}
    float getRotationSpeed(){return rotationSpeed;}
    float getScale(){return scale;}

};

class TrianguloV
{
private:
    std::shared_ptr<TrianguloM> tm;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    float rotation;
    float elapsedTime;
public:
    TrianguloV(std::shared_ptr<TrianguloM> tm_,std::vector<std::shared_ptr<sf::Texture>> textures_):tm(tm_), rotation(0.0f),
    textures(textures_)
    {
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    } 
    void move()
    {
        sprite.setRotation( rotation += tm->getRotationSpeed());
        sprite.setPosition(tm->getPosx(), tm->getPosy());
    }
    void update(const float& elapsedTime_)
    {
        elapsedTime = elapsedTime_;
        updateTexture();
        move();
        
    }
    void updateTexture()
    {
        size_t textureIndex = static_cast<size_t>(std::round(elapsedTime * 4)) % textures.size();
        sprite.setScale(tm->getScale(), tm->getScale());
        sprite.setTexture(*textures[textureIndex]);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    }
};

#endif