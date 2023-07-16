#ifndef POLICE_H
#define POLICE_H
#include <SFML/Graphics.hpp>
#include "BombaPolice.h"
#include "Enemigos.h"
#include "Espina.h"
#include <memory>
#include <iostream>
class PoliceM : public Enemigo
{
private:
    float life, speed, scale;
    int HeightSize, WidthSize, xBorder, yBorder;
    bool movingLeft;

    public:
    PoliceM(const int& limitx, const int& limity):
    Enemigo(limitx * 0.8, limity * 0.5, 200), life(100), speed(0.2),
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
    sf::Color color;
    sf::Clock clock;
    float elapsedTime;
    std::shared_ptr<PoliceM> p; 
    std::shared_ptr<BombaPoliceM> bombM;
    std::shared_ptr<BombaPoliceV> bombV;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite sprite;
    EspinaM** espinasM;
    EspinaV** espinasV;
public:
    PoliceV(std::shared_ptr<PoliceM> police_, const std::vector<std::shared_ptr<sf::Texture>>& textures_): p(police_),
    color(sf::Color::Cyan), activeBomb(false), activeEspinas(false), textures(textures_)
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
                espinasM[0] ->move();
                espinasV[0] ->update();

            }
            if(espinasM[1])
            {
                espinasM[1] ->move();
                espinasV[1] ->update();
            }
            if(espinasM[2])
            {
                espinasM[2] ->move();
                espinasV[2] ->update();
            }
            if(espinasM[3])
            {
                espinasM[3] ->move();
                espinasV[3] ->update();
            }
            if(espinasM[4])
            {
                espinasM[4] ->move();
                espinasV[4] ->update();
            }
            if(espinasM[5])
            {
                espinasM[5] ->move();
                espinasV[5] ->update();
            }
            if(espinasM[6])
            {
                espinasM[6] ->move();
                espinasV[6] ->update();
            }
            if(espinasM[7])
            {
                espinasM[7] ->move();
                espinasV[7] ->update();
            }
            if (espinasM[0]->isExpired() && espinasM[1]->isExpired() && espinasM[2]->isExpired() && espinasM[3]->isExpired() && espinasM[4]->isExpired() && espinasM[5]->isExpired() && espinasM[6]->isExpired() && espinasM[7]->isExpired())
            {
                delete espinasM;
                delete espinasV;
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
            bombV = std::make_shared<BombaPoliceV>(bombM);
            
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
                espinasM = new EspinaM*[8];
                espinasM[0] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'r', p->getXborder(), p->getYborder());
                espinasM[1] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'l', p->getXborder(), p->getYborder());
                espinasM[2] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'u', p->getXborder(), p->getYborder());
                espinasM[3] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'d', p->getXborder(), p->getYborder());
                espinasM[4] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'b', p->getXborder(), p->getYborder());
                espinasM[5] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'a', p->getXborder(), p->getYborder());
                espinasM[6] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'c', p->getXborder(), p->getYborder());
                espinasM[7] = new EspinaM(bombM->getPosx(), bombM->getPosy(),'e', p->getXborder(), p->getYborder());

                espinasV = new EspinaV*[8];
                espinasV[0] = new EspinaV(espinasM[0]);
                espinasV[1] = new EspinaV(espinasM[1]);
                espinasV[2] = new EspinaV(espinasM[2]);
                espinasV[3] = new EspinaV(espinasM[3]);
                espinasV[4] = new EspinaV(espinasM[4]);
                espinasV[5] = new EspinaV(espinasM[5]);
                espinasV[6] = new EspinaV(espinasM[6]);
                espinasV[7] = new EspinaV(espinasM[7]);
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
        delete espinasM[0];
        delete espinasM[1];
        delete espinasM[2];
        delete espinasM[3];
        delete espinasM[4];
        delete espinasM[5];
        delete espinasM[6];
        delete espinasM[7];
        delete espinasV[0];
        delete espinasV[1];
        delete espinasV[2];
        delete espinasV[3];
        delete espinasV[4];
        delete espinasV[5];
        delete espinasV[6];
        delete espinasV[7];
        delete[] espinasM;
        delete[] espinasV;
    }

};
#endif
