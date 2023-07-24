#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Cup.h"
#include "Textures.h"
int main()
{
    Textures textures;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Cuadrado en SFML");
    std::shared_ptr<CupHeadM> cupM = std::make_shared<CupHeadM>(400,400,800,800);
    std::shared_ptr<CupHeadV> cupV = std::make_shared<CupHeadV>(cupM, textures.getRedRunTextures(),
                                                                textures.getRedJumpTextures(),
                                                                textures.getRedStandingTextures());
    bool inPlatform = true;
    sf::Clock clock;
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && inPlatform)
        {
            inPlatform = false;
        }
        // Verificar si el cuadrado ha llegado al piso
        if (cupM->getPosY() >= 700)
        {
            inPlatform = true;
        }
        float deltaTime = clock.restart().asSeconds();
        cupM->update(deltaTime
                    , sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                    , sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    , sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
                    , inPlatform);
        cupV->update();
        window.clear();
        cupV->draw(window);
        window.display();
    }

    return 0;
}
