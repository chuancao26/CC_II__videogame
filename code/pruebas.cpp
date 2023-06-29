#include <SFML/Graphics.hpp>

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 800), "Cuadrado móvil");

    // Crear el cuadrado
    sf::RectangleShape square(sf::Vector2f(100.0f, 100.0f));
    square.setFillColor(sf::Color::Green);
    square.setOrigin(50.0f, 50.0f);

    // Establecer la posición inicial del cuadrado
    sf::Vector2f position(400.0f, 400.0f);
    square.setPosition(position);

    // Velocidad y rotación del cuadrado
    float speed = 1.0f;
    float rotationSpeed = 1.0f;

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

        // Actualizar la posición y rotación del cuadrado
        position.x += speed * 0.016f; // Multiplicar por un factor de tiempo fijo para un movimiento constante
        square.setRotation(square.getRotation() + rotationSpeed * 0.016f);

        // Comprobar los límites de la ventana y hacer que el cuadrado rebote
        if (position.x + 50.0f > 800.0f || position.x - 50.0f < 0.0f)
            speed = -speed;

        // Establecer la nueva posición del cuadrado
        square.setPosition(position);

        // Limpiar la ventana
        window.clear();

        // Dibujar el cuadrado en la ventana
        window.draw(square);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
