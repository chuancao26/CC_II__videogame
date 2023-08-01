#ifndef BALABOMBA_VISTA_H
#define BALABOMBA_VISTA_H
#include <SFML/Graphics.hpp>
#include "Bala.cpp"

class BalaBombaVista
{
    public:
        sf::Texture texture;
        sf::Sprite balaShape;
        BalaBomba bal;
        float posx,posy;
    public:
        BalaBombaVista()=default;
        
        BalaBombaVista(BalaBomba& bala):bal(bala)
        { 
            if (!texture.loadFromFile("img/balas/balaBomba/Bomba1.png")) {
                   std::cout << "Error al cargar la imagen bala bomba.png" <<std::endl;
               }
            balaShape.setTexture(texture);
            balaShape.setPosition(bal.getPosx(), bal.getPosy());
            balaShape.setScale(bala.getSize()/balaShape.getLocalBounds().width, bala.getSize()/balaShape.getLocalBounds().height);
            posx=bal.getPosx();
            posy=bal.getPosy();
        }

        float getPosX(){
            return posx;
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