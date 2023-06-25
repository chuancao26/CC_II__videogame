#include <SFML/Graphics.hpp>
#include <random> // Para generar números aleatorios

class CuadradoSFML
{
public:
    CuadradoSFML() : window(sf::VideoMode(800, 800), "Cuadrado SFML")
    {
        std::random_device rd;
        generator.seed(rd());
        distributionX = std::uniform_real_distribution<float>(0, 800);
        distributionY = std::uniform_real_distribution<float>(0, 800);

        square.setSize(sf::Vector2f(50, 50));
        square.setFillColor(sf::Color::Red);
        square.setPosition(800, getRandomYPosition());
    }

    void run()
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::RectangleShape square;

    std::mt19937 generator;
    std::uniform_real_distribution<float> distributionX;
    std::uniform_real_distribution<float> distributionY;

    float speed = 0.2f;

    void update()
    {
        square.move(-speed, 0);

        if (square.getPosition().x + square.getSize().x < 0 ||
            square.getPosition().y + square.getSize().y < 0)
        {
            square.setPosition(800, getRandomYPosition());
        }
    }

    void render()
    {
        window.clear();
        window.draw(square);
        window.display();
    }

    float getRandomYPosition()
    {
        return distributionY(generator);
    }
};

int main()
{
    CuadradoSFML cuadrado;
    cuadrado.run();

    return 0;
}
