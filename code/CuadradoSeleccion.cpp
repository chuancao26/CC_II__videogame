#include <SFML/Graphics.hpp>
class CuadroSeleccion {
    public:
        bool seleccionado = false;
        sf::Color colorNormal = sf::Color::White;
        sf::Color colorSeleccionado = sf::Color::Green;
        sf::RectangleShape marco;
    public:
    void dibujar(sf::Sprite& sprite) {
        // Dibujar sprite1 con cuadro de selección
        sf::Color colorMarco1 = seleccionado ? colorSeleccionado : colorNormal;
        marco= sf::RectangleShape(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
        marco.setPosition(sprite.getPosition());
        marco.setFillColor(sf::Color::Transparent);
        marco.setOutlineThickness(2.f);
        marco.setOutlineColor(colorMarco1);
    }
};