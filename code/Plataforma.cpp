#include "Plataforma.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

sf::FloatRect Platform::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}


Map Map::parseMap(const std::vector<std::string>& mapStrings)
{
    Map map;
    const float platformWidth = 100.f;  // Ancho predeterminado de la plataforma
    const float platformHeight = 20.f;  // Alto predeterminado de la plataforma
    const float platformSpacing = 50.f; // Espacio predeterminado entre plataformas

    float currentX = 50.f;
    float currentY = 300.f;

    for (const auto& mapString : mapStrings)
    {
        currentX = 50.f; // Reiniciar la posición X para cada línea de mapa

        for (char c : mapString)
        {
            if (c == 'P') // Carácter que representa una plataforma
            {
                Platform platform;
                platform.x = currentX;
                platform.y = currentY;
                platform.width = platformWidth;
                platform.height = platformHeight;
                platform.shape.setPosition(platform.x, platform.y);
                platform.shape.setSize(sf::Vector2f(platform.width, platform.height));
                platform.shape.setFillColor(sf::Color::Red);

                map.platforms.push_back(platform);
            }
            if (c == 'A') // Carácter que representa otra plataforma
            {
                Platform platform;
                platform.x = currentX;
                platform.y = currentY;
                platform.width = platformWidth;
                platform.height = platformHeight;
                platform.shape.setPosition(platform.x, platform.y);
                platform.shape.setSize(sf::Vector2f(platform.width, platform.height));
                platform.shape.setFillColor(sf::Color::Blue);

                map.platforms.push_back(platform);
            }

            // Mueve las coordenadas X hacia la derecha
            currentX += platformWidth + platformSpacing;
        }

        // Mueve las coordenadas Y hacia abajo para la siguiente línea de mapa
        currentY += platformHeight + platformSpacing;
    }

    return map;
}
