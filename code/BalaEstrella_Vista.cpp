#ifndef BALAESTRELLA_VISTA_H
#define BALAESTRELLA_VISTA_H
#include <SFML/Graphics.hpp>
#include "Bala.cpp"

class BalaEstrellaVista
{
    public:
        sf::Texture texture;
        sf::Sprite balaShape;
        BalaEstrella bal;
        float posx,posy;
    public:
        BalaEstrellaVista()=default;
        
        BalaEstrellaVista(BalaEstrella& bala):bal(bala)
        {
            if (!texture.loadFromFile("img/balas/balaEstrella/Estrella1.png")) {
                   std::cout << "Error al cargar la imagen bala estrella.png" <<std::endl;
               }
            balaShape.setTexture(texture);
            balaShape.setPosition(bal.getPosx(), bal.getPosy());
            balaShape.setScale(bal.getSize()/balaShape.getLocalBounds().width, bal.getSize()/balaShape.getLocalBounds().height);
            posx=bal.getPosx();
            posy=bal.getPosy();
        }
        
        void setPosition(float x, float y) 
        {
            balaShape.setPosition(x, y);
        }
        sf::Sprite& get(){
            return balaShape;
        }

};
#endif