#ifndef BOMBAPOLICE_H
#define BOMBAPOLICE_H
#include <SFML/Graphics.hpp>
using namespace sf;
class BombaPolice
{
    private:
        float posx, posy;
        sf::CircleShape bomb;
        int size = 50;
        bool exploded = false;
        sf::Clock clock;
        sf::Time elapsedTime;
        float lifetime = 10.0f;
    public:
        BombaPolice(const int& posx_,const int& posy_)
        {
            posx = posx_;
            posy = posy_;
            bomb.setPosition(posx,posy);
            bomb.setRadius(size);
            bomb.setFillColor(Color::Red);
        }
        BombaPolice()
        {
            posx = 0; posy = 0;
        }
        void setPosicion(const int& posx_,const int& posy_)
        {
            posx = posx_;
            posy = posy_;
        }
        void update(sf::Time deltaTime)
        {
            if (deltaTime.asSeconds() >= lifetime)
            {
                exploded = true; 
            }
        }
        bool isExpired()
        {
            return exploded;
        }
        void draw(RenderWindow& window)
        {
            if (exploded == false)
                window.draw(bomb);
        }

};
#endif