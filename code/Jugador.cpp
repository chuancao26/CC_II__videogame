#include <SFML/Graphics.hpp>
#include "Jugador.h"
using namespace std;
using namespace sf;

    Cup::Cup(const int &px, const int& py, const int& size_, const Color& a, const int& limitx, const int& limity)
    {
        xedge = limitx; yedge = limity;
        posx = px; posy = py; size = size_;
        color = a;
        cup.setPosition(posx, posy);
        cup.setFillColor(color);
        cup.setSize(Vector2f(size,size));
    }
    void Cup::dibujar(RenderWindow& a)
    {
        caida();
        a.draw(cup);
    }
    sf::FloatRect Cup::getGlobalBounds() const
    {
        return cup.getGlobalBounds();
    }
    void Cup::mover(const int& px, const int& py)
    {
        cup.setPosition(posx, posy);
    }       
    void Cup::controlarMovimiento(const bool& xclickRight, const bool& xclickLeft, const bool& yclickDown )
    {
        if (xclickLeft && posx >= 0)
        {
            posx -= speed;
        }
        if (xclickRight && posx <= xedge - size)
        {
            posx = posx + speed;
        }
        if (yclickDown && posy <= yedge - size)
        {
            posy += speed;
        }
        mover(posx, posy);
    }
    float Cup::getPosx() {return posx;}
    float Cup::getPosy() {return posy;}
    void Cup::saltar(const bool& yclickUp)
    {
        if (yclickUp)
        {
            posy -= salto;
        }
        mover(posx, posy);
    }
    void Cup::caida()
    {
        if (posy < 600)
            posy += gravedad;
        mover(posx, posy);
    }
    bool Cup::isColliding(const Platform& platform)
    {
        sf::FloatRect rect1 = cup.getGlobalBounds();

        // Obtener el rectángulo del shape2
        sf::FloatRect rect2 = platform.getGlobalBounds();
        
        if (rect1.intersects(rect2))
        {
            // Verifica si la colisión ocurre en la parte superior de la plataforma
            if (posy + size <= platform.y + platform.height)
            {
                // Ajusta la posición vertical de la Cup para que se quede encima de la plataforma
                posy = platform.y - size;
                mover(posx, posy);
                return true;
            }
        }
        // Si no hay colisión, devuelve falso
        return false;
    }