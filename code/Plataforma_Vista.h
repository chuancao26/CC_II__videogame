#ifndef PLATAFORMA_VISTA_H
#define PLATAFORMA_VISTA_H
#include <SFML/Graphics.hpp>
#include "Plataforma_Modelo.h"

class PlataformaVista
{
    public:
        sf::Texture texture;
        sf::Sprite platformShape;
        Plataforma pla;
        float gravedad;
        float posx,posy;
    public:
        PlataformaVista()=default;
        PlataformaVista(PlataformaVista&& other)
        : texture(std::move(other.texture)), platformShape(std::move(other.platformShape))
        {
            posx=std::move(other.posx);
            posy=std::move(other.posy);
        }

        PlataformaVista(const Plataforma& plat):pla(plat)
        {
            if (!texture.loadFromFile("img/plataforma/plataforma.png")) {
                std::cout << "Error al cargar la imagen plataforma.png" << std::endl;
            }
            platformShape.setTexture(texture);
            platformShape.setPosition(plat.getPosx(), plat.getPosy());
            platformShape.setScale(plat.width/platformShape.getLocalBounds().width, plat.height/platformShape.getLocalBounds().height);
            posx=pla.getPosx();
            posy=pla.getPosy();
        }

        sf::Sprite& get(){
            return platformShape;
        }
        void setPosition(float x, float y) 
        {
            platformShape.setPosition(x, y);
        }
        void dibujarPlat(const Plataforma& plataforma,sf::RenderWindow& window) 
        {
            //jugadorSprite.setPosition(jugador.getPosx(), jugador.getPosy());
            platformShape.setPosition(plataforma.getPosx(), plataforma.getPosy());
            window.draw(platformShape);
        }

};
#endif