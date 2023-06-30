#include <SFML/Graphics.hpp>
#include "Jugador_Modelo.cpp"
#include "Plataforma_Vista.cpp"

class JugadorVista {
public:
    sf::Texture texture1;
    sf::Sprite cupShape;
    
public:

    JugadorVista()
    {
        if (!texture1.loadFromFile("img\\cup\\jugador.png")) {
            cout << "Error al cargar la imagen jugador.png" <<endl;
        }
        cupShape.setTexture(texture1);
        cupShape.setScale(60.f/cupShape.getLocalBounds().width, 60.f/cupShape.getLocalBounds().height);
    }
    
    void dibujar(const Cup& jugador,sf::RenderWindow& window) {
        cupShape.setPosition(jugador.getPosx(), jugador.getPosy()-jugador.getSize());
        window.draw(cupShape);
    }
    void actualizar(Cup& jugador) {

    }
};

