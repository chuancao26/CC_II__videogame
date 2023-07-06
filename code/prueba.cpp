#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
int main()
{
// Bucle principal del juego
    int width = 800;
    int height = 800;
    float avance = 0.0f;
    float speed = 0.1f;
    bool moveLeft = false, lateral = true, moveUp = false, avanceFlag = false;
    sf::RenderWindow window(sf::VideoMode(width,height), "Probando el misil");
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(100,50));
    float posx = width * 0.1f, posy = height * 0.9f;
    rect.setPosition(posx, posy);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la ventana
        window.clear(sf::Color::Black);
        window.draw(rect);
        if (lateral)
        {
            if (moveLeft && !moveUp)
            {
                posx -= speed;
            }
            if (!moveLeft && !moveUp)
            {
                posx += speed;
            }
            if (posx >= 0.5 * width)
            {
                moveLeft = true;
                moveUp = true;
                rect.setSize(sf::Vector2f(50,100));
                if (!avanceFlag)
                {
                    avance = posy;
                    avanceFlag = true;
                }
            }
            if (posx <= 0.05 * width)
            {
                moveLeft = false;
                moveUp = true;
                rect.setSize(sf::Vector2f(50,100));
                if (!avanceFlag)
                {
                    avance = posy;
                    avanceFlag = true;
                }
            }
            if (moveUp)
            {
                posy -= speed;
                if (avance - posy >= height * 0.15)
                {
                    avanceFlag = false;
                    moveUp = false;
                    rect.setSize(sf::Vector2f(100,50));
                }
            }
        }
        if (posy <= 0 && !moveUp)
        {
            posy = height * 0.1;
        }
        rect.setPosition(posx,posy);
        
        // Actualizar la ventana
        window.display();
    }

    return 0;
}
