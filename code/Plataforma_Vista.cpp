#include <SFML/Graphics.hpp>
#include "Plataforma_Modelo.h"

class PlataformaVista
{
    public:
        sf::RectangleShape platformShape;
        Plataforma pla;
    public:
        PlataformaVista(const Plataforma& plat):pla(plat)
        {
            platformShape.setSize(sf::Vector2f(100.f, 20.f));
            platformShape.setFillColor(sf::Color::Green);
        }
        sf::RectangleShape& get(){
            return platformShape;
        }
        void setPosition(float x, float y) 
        {
            platformShape.setPosition(x, y);
        }
        sf::FloatRect getGlobalBounds() const
        {
            return platformShape.getGlobalBounds();
        }

};
