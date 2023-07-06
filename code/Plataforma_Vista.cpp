#ifndef PLATAFORMA_VISTA_H
#define PLATAFORMA_VISTA_H
#include <SFML/Graphics.hpp>
#include "Plataforma_Modelo.cpp"

class PlataformaVista
{
    public:
        sf::RectangleShape platformShape;
        Plataforma pla;
        float gravedad;
        float posx,posy;
    public:
        PlataformaVista(const Plataforma& plat):pla(plat)
        {
            platformShape.setSize(sf::Vector2f(pla.width, pla.height));
            platformShape.setFillColor(sf::Color::Green);
            posx=pla.getPosx();
            posy=pla.getPosy();
        }
        sf::RectangleShape& get(){
            return platformShape;
        }
        void setPosition(float x, float y) 
        {
            platformShape.setPosition(x, y);
        }
        void dibujarPlat(const Plataforma& plataforma,sf::RenderWindow& window) 
        {
            //jugadorSprite.setPosition(jugador.getPosx(), jugador.getPosy());
            PlataformaVista plat(plataforma);
            plat.setPosition(plataforma.getPosx(), plataforma.getPosy());
            window.draw(plat.get());
        }

};
#endif