#ifndef BALANORMAL_VISTA_H
#define BALANORMAL_VISTA_H
#include <SFML/Graphics.hpp>
#include "Bala.cpp"

class BalaNormalVista
{
    public:
        sf::Texture texture;
        sf::Sprite balaShape;
        BalaNormal bal;
        float posx,posy;
    public:
        BalaNormalVista()=default;
        
        BalaNormalVista(BalaNormal& bala):bal(bala)
        { 
            if (!texture.loadFromFile("img/balas/balaNormal/Normal1.png")) {
                   std::cout << "Error al cargar la imagen bala normal.png" <<std::endl;
               }
            balaShape.setTexture(texture);
            balaShape.setPosition(bala.getPosx(), bala.getPosy());
            balaShape.setScale(bala.getSize()/balaShape.getLocalBounds().width, bala.getSize()/balaShape.getLocalBounds().height);
            posx=bala.getPosx();
            posy=bala.getPosy();
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