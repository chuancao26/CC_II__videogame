#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Fist
{
private:
    sf::RectangleShape cuad;
    sf::Color color;
    int xBorder, yBorder, size;
    float posx, posy, x, y, radiusX, radiusY, angle;

public:
    Fist(const int& xb, const int& yb)
        : color(sf::Color::Magenta), xBorder(xb), yBorder(yb),
          posx(xBorder / 2), posy(yBorder / 2), size(50), radiusX(200), radiusY(100), angle(0.0f)
    {
        cuad.setSize(sf::Vector2f(size, size));
        cuad.setFillColor(color);
        cuad.setPosition(posx, posy);
    }

    void move()
    {
        x = posx + std::sin(2 * angle) * std::pow(std::abs(std::cos(angle)), 0.5f) * radiusX;
        y = posy - std::sin(angle) * std::pow(std::abs(std::cos(2 * angle)), 0.5f) * radiusY;
        cuad.setPosition(x, y);
    }

    void update(const bool& tecla)
    {
        angle += 0.01f;
        move();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(cuad);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Cuadrado Movimiento Alas de Mariposa");
    Fist a(800, 800);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        a.update();

        // window.clear();
        a.draw(window);
        window.display();
    }

    return 0;
}
