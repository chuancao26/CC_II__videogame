
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>

class Cuadrados
{
private:
    sf::RectangleShape cuadrado;
    float velocidad;
    bool enColision;
    sf::Clock relojColision;
    sf::Clock relojDesaparicion;

public:
    Cuadrados(float posX, const sf::Color& color, const sf::Vector2f& size)
    {
        cuadrado.setPosition(posX, 0);
        cuadrado.setSize(size);
        cuadrado.setFillColor(color);
        velocidad = 200.0f;
        enColision = false;
        relojColision.restart();
        relojDesaparicion.restart();
    }

    void actualizar(float deltaTime)
    {
        if (!enColision)
        {
            cuadrado.move(0, velocidad * deltaTime);
        }

        if (relojDesaparicion.getElapsedTime().asSeconds() >= 5.0f)
        {
            resetear();
        }
    }

    bool colisionaCon(const sf::RectangleShape& rectangulo)
    {
        return cuadrado.getGlobalBounds().intersects(rectangulo.getGlobalBounds());
    }

    void aumentarTiempoEnColision(float deltaTime)
    {
        relojColision.restart();
        enColision = true;
    }

    bool estaEnColisionPorTiempo(float segundos)
    {
        return (relojColision.getElapsedTime().asSeconds() >= segundos);
    }

    void setEnColision(bool colision)
    {
        enColision = colision;
    }

    void resetear()
    {
        cuadrado.setPosition(-100, -100); // Fuera de la ventana
    }

    void dibujar(sf::RenderWindow& window)
    {
        window.draw(cuadrado);
    }

    void pushBack()
    {
        cuadrado.setPosition(-100, -100); // fuera de la ventana
    }
};

std::vector<Cuadrados*> inicializarCuadrados(int numCuadrados, const sf::RenderWindow& window)
{
    std::vector<Cuadrados*> listaCuadrados;

    for (int i = 0; i < numCuadrados; i++)
    {
        float posX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (window.getSize().x * 11 / 16 - window.getSize().x / 20))) + window.getSize().x / 16;
        listaCuadrados.push_back(new Cuadrados(posX, sf::Color::Red, sf::Vector2f(20, 20)));
    }

    return listaCuadrados;
}

void caenBombas(sf::RenderWindow& window, std::vector<Cuadrados*>& listaCuadrados)
{
    sf::RectangleShape rectanguloGris;
    rectanguloGris.setSize(sf::Vector2f(window.getSize().x, (window.getSize().y * 2) / 9));
    rectanguloGris.setFillColor(sf::Color(128, 128, 128)); // Gris
    rectanguloGris.setPosition(0, window.getSize().y - rectanguloGris.getSize().y);

    sf::RectangleShape rectanguloVerde;
    rectanguloVerde.setSize(sf::Vector2f(window.getSize().x / 4, (window.getSize().y * 2) / 3));
    rectanguloVerde.setFillColor(sf::Color::Green);
    rectanguloVerde.setPosition(window.getSize().x - rectanguloVerde.getSize().x, (window.getSize().y / 9));

    sf::Clock relojMovimiento;
    sf::Time tiempoAcumulado = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = relojMovimiento.restart();
        tiempoAcumulado += deltaTime;

        for (auto cuadrado : listaCuadrados)
        {
            cuadrado->actualizar(deltaTime.asSeconds());

            if (cuadrado->colisionaCon(rectanguloGris))
            {
                cuadrado->aumentarTiempoEnColision(deltaTime.asSeconds());
                if (cuadrado->estaEnColisionPorTiempo(5.0f))
                {
                    cuadrado->resetear();
                    cuadrado->setEnColision(false);
                }
            }

            if (cuadrado->colisionaCon(rectanguloVerde))
            {
                cuadrado->pushBack();
            }
        }

        if (tiempoAcumulado.asSeconds() >= 1.0f)
        {
            tiempoAcumulado = sf::Time::Zero;
            float rangoX = (window.getSize().x * 11 / 16 - window.getSize().x / 20) / 20;
            float posXMin = window.getSize().x / 16;
            float posXMax = posXMin + rangoX ;
            float posX = (static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / rangoX))) * 20 + posXMin;
            listaCuadrados.push_back(new Cuadrados(posX, sf::Color::Red, sf::Vector2f(20, 20)));

        }

        window.clear();
        window.draw(rectanguloGris);
        window.draw(rectanguloVerde);

        for (auto cuadrado : listaCuadrados)
        {
            cuadrado->dibujar(window);
        }

        window.display();
    }

    for (auto cuadrado : listaCuadrados)
    {
        delete cuadrado;
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Enemigo");
    window.setFramerateLimit(90);

    const int NUM_CUADRADOS = 1;
    std::vector<Cuadrados*> listaCuadrados = inicializarCuadrados(NUM_CUADRADOS, window);

    caenBombas(window, listaCuadrados);

    return 0;
}

