#include <SFML/Graphics.hpp>

class Espina
{
private:
    float posx, posy, speed;
    int size, points, xBorder, yBorder;
    char type;
    sf::ConvexShape triangle;
    sf::Color color;

public:
    Espina(const float& posx_, const float& posy_, const char& type_, const int& xBorder_, const int& yBorder_):
        size(50), posx(posx_), posy(posy_), points(3), color(sf::Color::Magenta), speed(3.0f), 
        type(type_), xBorder(xBorder_), yBorder(yBorder_)
    {
        // Crear el triángulo de la espina
        triangle.setPointCount(points);
        triangle.setFillColor(color);
        
        // Establecer los puntos del triángulo según el tipo de espina
        if (type == 'r')
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx, posy - size));
            triangle.setPoint(2, sf::Vector2f(posx + 100, posy - size / 2));
        }
        else if (type == 'l')
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx, posy - size));
            triangle.setPoint(2, sf::Vector2f(posx - 100, posy - size / 2));
        }
        else if (type == 'd')
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx - size, posy));
            triangle.setPoint(2, sf::Vector2f(posx - size / 2, posy + 100));
        }
        else if (type == 'u')
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx - size, posy));
            triangle.setPoint(2, sf::Vector2f(posx - size / 2, posy - 100));
        }
        else if (type == 'a') // is upward left 
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx + size, posy - size / 2));
            triangle.setPoint(2, sf::Vector2f(posx - 100, posy - 100 / 2));
        }
        else if (type == 'b') // is upward right
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx + size, posy - size / 2));
            triangle.setPoint(2, sf::Vector2f(posx + 100, posy - 100 / 2));
        }
        else if (type == 'c') // is downward left
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx + size / 2, posy + size));
            triangle.setPoint(2, sf::Vector2f(posx - 100, posy + 100 / 2));
        }
        else if (type == 'e') // is downward right
        {
            triangle.setPoint(0, sf::Vector2f(posx, posy));
            triangle.setPoint(1, sf::Vector2f(posx + size / 2, posy + size));
            triangle.setPoint(2, sf::Vector2f(posx + 100, posy + 100 / 2));
        }
    }

    void move()
    {
        if (type == 'a') // is upward left 
        {
            posx -= speed;
            posy -= speed; 
        }
        else if (type == 'b') // is upward right
        {
            posx += speed;
            posy -= speed;
        }
        else if (type == 'c') // is downward left
        {
            posx -= speed;
            posy += speed;
        }
        else if (type == 'e') // is downward right
        {
            posx += speed;
            posy += speed;
        }
        else if (type == 'r') 
        {
            posx += speed;
        }
        else if (type == 'l')
        {
            posx -= speed;
        }
        else if (type == 'u')
        {
            posy -= speed;
        }
        else if (type == 'd')
        {
            posy += speed;
        }
        
        // Actualizar la posición del triángulo
        triangle.setPosition(posx, posy);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(triangle);
    }

    bool isExpired()
    {
        if (posx <= -size || posy <= -size || posx >= xBorder + size || posy >= yBorder + size)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Espinas");

    // Crear las espinas de los ocho tipos
    Espina espinaR(100, 100, 'r', screenWidth, screenHeight);
    Espina espinaL(200, 200, 'l', screenWidth, screenHeight);
    Espina espinaD(300, 300, 'd', screenWidth, screenHeight);
    Espina espinaU(400, 400, 'u', screenWidth, screenHeight);
    Espina espinaA(500, 500, 'a', screenWidth, screenHeight);
    Espina espinaB(600, 100, 'b', screenWidth, screenHeight);
    Espina espinaC(700, 200, 'c', screenWidth, screenHeight);
    Espina espinaE(800, 300, 'e', screenWidth, screenHeight);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Mover y dibujar las espinas

        espinaB.move();
        espinaB.draw(window);


        // Comprobar si alguna espina ha expirado (está fuera de la pantalla)
        if (espinaR.isExpired())
            espinaR = Espina(100, 100, 'r', screenWidth, screenHeight);

        if (espinaL.isExpired())
            espinaL = Espina(200, 200, 'l', screenWidth, screenHeight);

        if (espinaD.isExpired())
            espinaD = Espina(300, 300, 'd', screenWidth, screenHeight);

        if (espinaU.isExpired())
            espinaU = Espina(400, 400, 'u', screenWidth, screenHeight);

        if (espinaA.isExpired())
            espinaA = Espina(500, 500, 'a', screenWidth, screenHeight);

        if (espinaB.isExpired())
            espinaB = Espina(600, 100, 'b', screenWidth, screenHeight);

        if (espinaC.isExpired())
            espinaC = Espina(700, 200, 'c', screenWidth, screenHeight);

        if (espinaE.isExpired())
            espinaE = Espina(800, 300, 'e', screenWidth, screenHeight);

        window.display();
    }

    return 0;
}
