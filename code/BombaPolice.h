#ifndef BOMBAPOLICE_H
#define BOMBAPOLICE_H
#include <SFML/Graphics.hpp>
#include "Espina.h"
#include "Enemigos.h"
#include <iostream>
#include <memory>
class BombaPoliceM : public Enemigo
{
private:
    float lifetime, elapsedTime, inicio, scale;
public:
    // constructor
    BombaPoliceM(const float& px, const float& py, const float& elapsedTime_):
    Enemigo(px, py, 20), lifetime(2.0f), elapsedTime(elapsedTime_), scale(0.70f),
    inicio(elapsedTime_)
    {
    }
    void update(const float& deltaTime)
    {
        elapsedTime = deltaTime;
    }
    void move()
    {
        std::cout << "There's no movement" << std::endl;
    }
    bool isExpired()
    {
        if (elapsedTime - inicio <= lifetime)
        {
            return false;
        }
        return true;
    };
    float getPosx() {return posx; }
    float getPosy() {return posy; }
    int getSize() {return size;}
    float getElapsedTime(){return elapsedTime;}
    float getStart(){return inicio;}
    float getLifetime(){return lifetime;}
    float getScale(){return scale;}
};
class BombaPoliceV
{
private:
    std::shared_ptr<BombaPoliceM> bombaM;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
public:
    BombaPoliceV(std::shared_ptr<BombaPoliceM> bp,
                std::vector<std::shared_ptr<sf::Texture>> textures_): bombaM(bp), textures(textures_)
    {
        sprite.setPosition(bombaM->getPosx(),bombaM->getPosy());
    }
    void updateTextures()
    {
        size_t textureIndex = static_cast<size_t>(std::round(bombaM->getElapsedTime() * 6)) % textures.size();
        sprite.setScale(bombaM->getScale(), bombaM->getScale());
        sprite.setTexture(*textures[textureIndex]);
    }
    void draw(sf::RenderWindow& window)
    {
        if (bombaM->getElapsedTime() - bombaM->getStart() <= bombaM->getLifetime())
        {  
            window.draw(sprite);
            updateTextures();
        }
    }
    sf::Sprite& getSprite()
    {
        return sprite;
    }
};

#endif


