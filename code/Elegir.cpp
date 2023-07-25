#ifndef ELEGIR_H
#define ELEGIR_H

#include <SFML/Graphics.hpp>
#include "CuadradoSeleccion.cpp"
#include <iostream>
#include <vector>

class ElegirPlayer{
    public:
    sf::Texture texture1,texture2,texture3;
    sf::Sprite sprite1,sprite2,sprite3;
    vector<int> elegidos;
    int seleccion;
    float size;
    CuadroSeleccion cuadro1;
    CuadroSeleccion cuadro2;
    CuadroSeleccion cuadro3;

    public:
    ElegirPlayer()
    {
        size=200;
        if (!texture1.loadFromFile("img\\cup\\cup1\\jugador.png")) {
            cout << "Error al cargar la imagen jugador.png" <<endl;
        }
        sprite1.setTexture(texture1);
        sprite1.setPosition(100, 100);
        sprite1.setScale(size/sprite1.getLocalBounds().width, size/sprite1.getLocalBounds().height);

        if (!texture2.loadFromFile("img\\cup\\cup2\\jugador.png")) {
                cout << "Error al cargar la imagen jugador2.png" <<endl;
        }
        sprite2.setTexture(texture2);
        sprite2.setPosition(400, 100);
        sprite2.setScale(size/sprite2.getLocalBounds().width, size/sprite2.getLocalBounds().height);

        if (!texture3.loadFromFile("img\\cup\\cup3\\jugador.png")) {
            cout << "Error al cargar la imagen jugador3.png" <<endl;
        }
        sprite3.setTexture(texture3);
        sprite3.setPosition(700, 100);
        sprite3.setScale(size/sprite3.getLocalBounds().width, size/sprite3.getLocalBounds().height);
    }
    
    void dibujar(sf::RenderWindow& window)//,const sf::Vector2f& mousePos, bool clic)
    {
        cuadro1.dibujar(sprite1);
        cuadro2.dibujar(sprite2);
        cuadro3.dibujar(sprite3);
        window.draw(sprite1);
        window.draw(sprite2);
        window.draw(sprite3);
        window.draw(cuadro1.marco);
        window.draw(cuadro2.marco);
        window.draw(cuadro3.marco);

    }

    vector<int> elegir(sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePos(mousePosition.x, mousePosition.y);
                        elegidos.push_back(seleccionar(mousePos,true));
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        // Código para el clic derecho del mouse
                        std::cout << "Clic derecho del mouse" << std::endl;
                    }
                }
            } 
        }  
        return elegidos;
    }
    int seleccionar(const sf::Vector2f& mousePos, bool clic)
    {
        if (sprite1.getGlobalBounds().contains(mousePos)) {
            if (clic) {
                cuadro1.seleccionado = !cuadro1.seleccionado;
                return 1;
            }
        }
        if (sprite2.getGlobalBounds().contains(mousePos)) {
            if (clic) {
                cuadro2.seleccionado = !cuadro2.seleccionado;
                return 2;
            }
        }
        if (sprite3.getGlobalBounds().contains(mousePos)) {
            if (clic) {
                cuadro3.seleccionado = !cuadro3.seleccionado;
                return 3;
            }
        }
        return 0; 
    }

};
#endif
