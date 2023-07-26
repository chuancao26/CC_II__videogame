#ifndef POLICE_H
#define POLICE_H
#include <SFML/Graphics.hpp>
#include "BombaPolice.h"
#include "Enemigos.h"
#include "Espina.h"
#include <memory>
#include <vector>
#include <iostream>
class PoliceM : public Enemigo
{
private:
    float life, speed, scale;
    int HeightSize, WidthSize, xBorder, yBorder;
    bool movingLeft;

    public:
    PoliceM(const int& limitx, const int& limity):
    Enemigo(limitx * 0.8, limity * 0.5, 200), life(100), speed(8.0f),
    WidthSize(100), HeightSize(100), xBorder(limitx),
    yBorder(limity), movingLeft(false), scale(0.60f)
    {
    }
    void move()
    {
        if (movingLeft) {
            posx -= speed;
            if (posx <= xBorder * 0.1) {
                movingLeft = false;
            }
        } else {
            posx += speed;
            if (posx >= xBorder * 0.9 - WidthSize) {
                movingLeft = true;
            }
        }
    }
    float getPosx(){return posx;}
    float getPosy(){return posy;}
    int getSize(){return size;}
    int getWidth(){return WidthSize;}
    int getHeight(){return HeightSize;}
    int getXborder(){return xBorder;}
    int getYborder(){return yBorder;}
    float getScale(){return scale;}
    bool getMoveLeft(){return movingLeft;}
};
class PoliceV
{
private:
    bool activeBomb, activeEspinas;
    sf::Clock clock;
    float elapsedTime;
    std::shared_ptr<PoliceM> p; 
    std::shared_ptr<BombaPoliceM> bombM;
    std::shared_ptr<BombaPoliceV> bombV;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    std::vector<std::shared_ptr<sf::Texture>> texturesEspinas;
    std::vector<std::shared_ptr<sf::Texture>> texturesBomb;
    sf::Sprite sprite;
    std::vector<std::shared_ptr<EspinaM>> espinasM;
    std::vector<std::shared_ptr<EspinaV>> espinasV;
    
public:
    PoliceV(std::shared_ptr<PoliceM> police_, 
            const std::vector<std::shared_ptr<sf::Texture>>& textures_,
            const std::vector<std::shared_ptr<sf::Texture>>& texturesEspi, 
            const std::vector<std::shared_ptr<sf::Texture>>& texturesBomb_):
     p(police_),texturesBomb(texturesBomb_), activeBomb(false), activeEspinas(false), textures(textures_), texturesEspinas(texturesEspi)
    {
    }
    void updateTexture()
    {
        size_t textureIndex = static_cast<size_t>(std::round(elapsedTime * 6)) % textures.size();
        sprite.setScale(p->getScale(), p->getScale());
        sprite.setTexture(*textures[textureIndex]);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    void move()
    {
        if (!p->getMoveLeft())
        {
            sprite.setScale(-p->getScale(),p->getScale());
        }
        else
        {
            sprite.setScale(p->getScale(),p->getScale());
        }
        sprite.setPosition(p->getPosx(), p->getPosy());
    }
    void updateBomb()
    {
        if(activeBomb)
        {
            bombM -> update(elapsedTime);
            if (bombM -> isExpired())
            {
                activeBomb = false;
                crearEspinas();
                activeEspinas = true;
            }
        }
    }
    void updateEspinas()
    {
        if (activeEspinas)
        {
            if(espinasM[0])
            {
                espinasM[0] ->update(elapsedTime);
                espinasV[0] ->update();

            }
            if(espinasM[1])
            {
                espinasM[1] ->update(elapsedTime);
                espinasV[1] ->update();
            }
            if(espinasM[2])
            {
                espinasM[2] ->update(elapsedTime);
                espinasV[2] ->update();
            }
            if(espinasM[3])
            {
                espinasM[3] ->update(elapsedTime);
                espinasV[3] ->update();
            }
            if(espinasM[4])
            {
                espinasM[4] ->update(elapsedTime);
                espinasV[4] ->update();
            }
            if(espinasM[5])
            {
                espinasM[5] ->update(elapsedTime);
                espinasV[5] ->update();
            }
            if(espinasM[6])
            {
                espinasM[6] ->update(elapsedTime);
                espinasV[6] ->update();
            }
            if(espinasM[7])
            {
                espinasM[7] ->update(elapsedTime);
                espinasV[7] ->update();
            }
            if (espinasM[0]->isExpired() && espinasM[1]->isExpired() && espinasM[2]->isExpired() && espinasM[3]->isExpired() && espinasM[4]->isExpired() && espinasM[5]->isExpired() && espinasM[6]->isExpired() && espinasM[7]->isExpired())
            {
                espinasM.clear();
                espinasV.clear();
                activeEspinas = false;
            }
        }  
    }
    void update(const float& timeDelta)
    {
        updateTexture();
        updateBomb();
        updateEspinas();
        elapsedTime = timeDelta;
        move();
        
    }
    void drawBomb(sf::RenderWindow& window)
    {
        if (!activeBomb)
        {
            bombM = std::make_shared<BombaPoliceM>(p->getPosx(), p->getPosy(), elapsedTime);
            bombV = std::make_shared<BombaPoliceV>(bombM, texturesBomb);
            
            activeBomb = true;
        }
        if (activeBomb)
        {
            bombV->draw(window);
        }
    }
    void draw(sf::RenderWindow& window)
    {
        drawBomb(window);
        drawEspinas(window);
        window.draw(sprite);
    }
    void crearEspinas()
    {
        if(bombM)
        {
            if (!activeEspinas)
            {
                espinasM.reserve(8);
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'r', p->getXborder(), p->getYborder()));
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'l', p->getXborder(), p->getYborder()));
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'u', p->getXborder(), p->getYborder()));
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'d', p->getXborder(), p->getYborder()));
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'b', p->getXborder(), p->getYborder()));
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'a', p->getXborder(), p->getYborder()));
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'c', p->getXborder(), p->getYborder()));
                espinasM.push_back(std::make_shared<EspinaM>(bombM->getPosx(), bombM->getPosy(),'e', p->getXborder(), p->getYborder()));

                espinasV.reserve(8);
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[0], texturesEspinas));
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[1], texturesEspinas));
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[2], texturesEspinas));
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[3], texturesEspinas));
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[4], texturesEspinas));
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[5], texturesEspinas));
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[6], texturesEspinas));
                espinasV.push_back(std::make_shared<EspinaV>(espinasM[7], texturesEspinas));
                activeEspinas = true;
            }
        }
    }
    void drawEspinas(sf::RenderWindow& window)
    {
        if (activeEspinas)
        {
            if(espinasV[0])
            {
                espinasV[0] ->draw(window);
            }
            if(espinasV[1])
            {
                espinasV[1] ->draw(window);
            }
            if(espinasV[2])
            {
                espinasV[2] ->draw(window);
            }
            if(espinasV[3])
            {
                espinasV[3] ->draw(window);
            }
            if(espinasV[4])
            {
                espinasV[4] ->draw(window);
            }
            if(espinasV[5])
            {
                espinasV[5] ->draw(window);
            }
            if(espinasV[6])
            {
                espinasV[6] ->draw(window);
            }
            if(espinasV[7])
            {
                espinasV[7] ->draw(window);
            }
        }
    }
    ~PoliceV()
    {
 
    }

};
#endif
