#ifndef TRIANGULO_H
#define TRIANGULO_H
#include <SFML/Graphics.hpp>
#include "Enemigos.h"
#include <iostream>
#include <memory>
class TrianguloM : public Enemigo
{
private:
    int radius, xBorder, yBorder, type;
    float speed, scale, rotationSpeed;
public:
    TrianguloM(const float& posx_, const float& posy_, const int& xlimit, const int& ylimit, const int& type_):
    Enemigo(posx_, posy_, 100), speed(15.0f), xBorder(xlimit), yBorder(ylimit), scale(0.50f),
    type(type_), rotationSpeed(5.0f)
    {

    } 
    virtual void move()
    {
        if(type == 1) // right
        {
            posx += speed;
        }
        if(type == 2) // left
        {
            posx -= speed;
        }
        if(type == 3) //up
        {
            posy -= speed;
        }
        if(type == 4) //down
        {
            posy += speed;
        }
        if(type == 5) //up left 
        {
            posx -= speed;
            posy -= speed;
        }
        if(type == 6) // up right
        {
            posx += speed;
            posy -= speed;
        }
        if(type == 7) // down left
        {
            posx -= speed;
            posy += speed;
        }
        if(type == 8) // down right
        {
            posx += speed;
            posy += speed;
        }
    }
    bool isExpired()
    {
        return (posx > xBorder + size * 2  || posx < 0 - size * 2 || posy > yBorder + size * 2 
        || posy < 0 - size * 2)? true:false;
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
    TrianguloV(std::shared_ptr<TrianguloM> tm_,std::vector<std::shared_ptr<sf::Texture>> textures_):
    tm(tm_), rotation(0.0f),
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
    sf::Sprite& getSprite()
    {
        return sprite;    
    }
};

#endif