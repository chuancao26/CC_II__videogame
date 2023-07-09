#include <SFML/Graphics.hpp>
#include "Jugador_Modelo.cpp"
#include "Plataforma_Vista.cpp"

class JugadorVista {
public:
    sf::Texture texture1;
    sf::Sprite cupShape;
    
    
public:
    JugadorVista(){}
    void cargar(int n)
    {
        switch (n)
        {
        case 1:
            if (!texture1.loadFromFile("img\\cup\\jugador.png")) {
                cout << "Error al cargar la imagen jugador.png" <<endl;
            }
            break;
        case 2:
            if (!texture1.loadFromFile("img\\cup\\jugador2.png")) {
                cout << "Error al cargar la imagen jugador2.png" <<endl;
            }
            break;
        case 3:
            if (!texture1.loadFromFile("img\\cup\\jugador3.png")) {
                cout << "Error al cargar la imagen jugador3.png" <<endl;
            }
            break;
        default:
            break;
        }
        
        cupShape.setTexture(texture1);
        cupShape.setScale(80.f/cupShape.getLocalBounds().width, 80.f/cupShape.getLocalBounds().height);
    }
    
    void dibujar(const Cup& jugador,sf::RenderWindow& window) {
        cupShape.setPosition(jugador.getPosx(), jugador.getPosy()-jugador.getSize());
        window.draw(cupShape);
    }
    void actualizar(Cup& jugador) {

    }
};

