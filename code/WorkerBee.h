#ifndef WORKERBEE_H
#define WORKERBEE_H
#include "Enemigos.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
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
        sf::RectangleShape bee;
        std::vector<std::shared_ptr<sf::Texture>> textures;
        sf::Sprite sprite;
        sf::Color color;
        float rateTexture;
        bool charged;

    public:
        WorkerBeeV(std::shared_ptr<WorkerBeeM> wb_): wb(wb_), color(sf::Color::Blue),
        charged(false)
        {
            textures.reserve(16);
        }
        void update(const float& rateTexture_)
        {  
            rateTexture = rateTexture_;
            if (!charged)
            {
                load();
                charged = true;
            }
            if (charged)
            {
                updateTexture();
                move();

            }
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
            if (charged)
            {
                window.draw(sprite);
            }
        }
        void load()
        {
            for (size_t i{1}; i < 16; ++i)
            {
                textures.push_back(std::make_shared<sf::Texture>());
                std::string tmp = (i < 10 ? "0" : "");
                std::string filename = "img/nivel_Bee/Bee_Worker/bee_grunt_flying_00" + tmp + std::to_string(i) + ".png";
                std::cout << filename << std::endl;
                if(!textures[i - 1]->loadFromFile(filename))
                    std::cout << "Problemas para cargar la imagen" << std::endl;
            }
        }
    };
#endif 