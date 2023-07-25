#include "eventosflor.h"
#include <vector>
#include <iostream>
int main(){
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Seeds");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Mapa1(window);
    }
    return 0;
}
