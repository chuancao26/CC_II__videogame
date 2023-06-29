#include <SFML/Graphics.hpp>

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 800), "Triángulo móvil");

    // Crear el triángulo
    sf::ConvexShape triangle(3);
    triangle.setPoint(0, sf::Vector2f(0.0f, 0.0f));
    triangle.setPoint(1, sf::Vector2f(0.0f, 100.0f));
    triangle.setPoint(2, sf::Vector2f(100.0f, 50.0f));
    triangle.setFillColor(sf::Color::Green);
    triangle.setOrigin(50.0f, 50.0f);

    // Establecer la posición inicial del triángulo
    sf::Vector2f position(400.0f, 400.0f);
    triangle.setPosition(position);

    // Velocidad del triángulo
    float speed = 0.20f;

    // Rotación del triángulo
    float rotationSpeed = 0.10f;

    // Reloj para medir el tiempo transcurrido
    sf::Clock clock;

    // Bucle principal
    while (window.isOpen())
    {
        // Manejar eventos de la ventana
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar la posición y rotación del triángulo
        position.x += speed;
        triangle.setRotation(triangle.getRotation() + rotationSpeed);
        // Comprobar los límites de la ventana y hacer que el triángulo rebote
        if (position.x + 50.0f > 800.0f || position.x - 50.0f < 0.0f)
            speed = -speed;

        // Establecer la nueva posición del triángulo
        triangle.setPosition(position);

        // Limpiar la ventana
        window.clear();

        // Dibujar el triángulo en la ventana
        window.draw(triangle);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
