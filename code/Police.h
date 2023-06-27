#ifndef POLICE_H
#define POLICE_H
#include <SFML/Graphics.hpp>
#include "BombaPolice.h"
#include "Enemigos.h"
#include <iostream>
class Police : public Enemigo
{
private:
    float life, speed;
    int HeightSize, WidthSize, xBorder, yBorder;
    bool movingLeft, activeBomb, activeEspinas;
    sf::Color color;
    sf::RectangleShape police;
    sf::Clock clock;
    sf::Time elapsedTime;
    BombaPolice* bomb;
    Espina** espinas;
    public:
    Police(const int& limitx, const int& limity):
    Enemigo(limitx * 0.8, limity * 0.75, 200), life(100), speed(0.2),
    WidthSize(200), HeightSize(200),color(sf::Color::Cyan), xBorder(limitx),
    yBorder(limity), movingLeft(false), activeBomb(false), activeEspinas(false)
    {
        police.setPosition(posx, posy);
        police.setFillColor(color);
        police.setSize(sf::Vector2f(WidthSize, HeightSize));
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
        police.setPosition(posx, posy);
    }
    void colocarBomba(sf::RenderWindow& window)
    {
        if (!activeBomb)
        {
            bomb = new BombaPolice(posx, posy, elapsedTime);
            activeBomb = true;
        }
    }
    void update(sf::Time& timeDelta)
    {
        elapsedTime = timeDelta;
        move();
        if(bomb)
        {
            bomb -> update(timeDelta);
            if (bomb->isExpired())
            {
                activeBomb = false;
                drawEspinas();

                delete bomb;

            }
        }
        if (espinas)
        {
            espinas[0]->move();
            espinas[1]->move();
            espinas[2]->move();
            espinas[3]->move();
            espinas[4]->move();
            espinas[5]->move();
            espinas[6]->move();
            espinas[7]->move();
            if (espinas[0]->isExpired() && espinas[1]->isExpired() && espinas[2]->isExpired() && espinas[3]->isExpired() && espinas[4]->isExpired() && espinas[5]->isExpired() && espinas[6]->isExpired() && espinas[7]->isExpired())
            {
                delete[] espinas;
                std::cout << "Se Elimino" << std::endl;
                activeEspinas = false;
            }
        }
    }
    void draw(sf::RenderWindow& window)
    {
        colocarBomba(window);
        if (bomb)
        {
            bomb->draw(window);
        }
        if (espinas)
        {
            espinas[0]->draw(window);
            espinas[1]->draw(window);
            espinas[2]->draw(window);
            espinas[3]->draw(window);
            espinas[4]->draw(window);
            espinas[5]->draw(window);
            espinas[6]->draw(window);
            espinas[7]->draw(window);

        }
        window.draw(police);
    }
    void drawEspinas()
    {
        if(bomb)
        {
            if (!activeEspinas)
            {
                std::cout << "Se creo" << std::endl;
                espinas = new Espina*[8];
                espinas[0] = new Espina(bomb->getPosx(), bomb->getPosy(),'r', xBorder, yBorder);
                espinas[1] = new Espina(bomb->getPosx(), bomb->getPosy(),'l', xBorder, yBorder);
                espinas[2] = new Espina(bomb->getPosx(), bomb->getPosy(),'u', xBorder, yBorder);
                espinas[3] = new Espina(bomb->getPosx(), bomb->getPosy(),'d', xBorder, yBorder);
                espinas[4] = new Espina(bomb->getPosx(), bomb->getPosy(),'a', xBorder, yBorder);
                espinas[5] = new Espina(bomb->getPosx(), bomb->getPosy(),'b', xBorder, yBorder);
                espinas[6] = new Espina(bomb->getPosx(), bomb->getPosy(),'c', xBorder, yBorder);
                espinas[7] = new Espina(bomb->getPosx(), bomb->getPosy(),'e', xBorder, yBorder);
                activeEspinas = true;
            }
        }

    }
    ~Police()
    {
        delete bomb;
        delete[] espinas;
    }
};
#endif
