// // #include <SFML/Graphics.hpp>
// // #include <iostream>
// // #include <memory>
// // #include "Cup.h"
// // #include "Textures.h"
// // #include <SFML/Graphics.hpp>
// // #include "FlyingFist.h"
// // #include <cmath>

// // // int main()
// // // {
// // //     const int windowWidth = 1280;
// // //     const int windowHeight = 720;

// // //     sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Cuadrado en forma de elipse");

// // //     sf::RectangleShape square(sf::Vector2f(50.f, 50.f));
// // //     square.setFillColor(sf::Color::Red);

// // //     const float a = 200.f; // Semieje mayor
// // //     const float b = 100.f; // Semieje menor
// // //     float angle = 0.f;
// // //     const float speed = 0.002f;

// // //     std::random_device rd;
// // //     std::mt19937 gen(rd());
// // //     std::uniform_int_distribution<int> dist(100, 1000);
// // //     int initPoint = dist(gen);
// // //     while (window.isOpen())
// // //     {
// // //         sf::Event event;
// // //         while (window.pollEvent(event))
// // //         {
// // //             if (event.type == sf::Event::Closed)
// // //                 window.close();
// // //         }
        
// // //         // Actualizar la posición del cuadrado en forma de elipse
// // //         float x = initPoint + a * cos(angle) * 2;
// // //         float y = windowHeight / 2 + b * sin(angle)* 2;

// // //         square.setPosition(x - square.getSize().x / 2, y - square.getSize().y / 2);

// // //         // Actualizar el ángulo para el siguiente fotograma
// // //         angle += speed;

// // //         // Limpiar la pantalla
// // //         window.clear();

// // //         // Dibujar el cuadrado rojo
// // //         window.draw(square);

// // //         // Mostrar el resultado en pantalla
// // //         window.display();
// // //     }

// // //     return 0;
// // // }

// // int main()
// // {

// //     Textures textures;
// //     std::shared_ptr<FlyingFistM> fm = std::make_shared<FlyingFistM>(1280,720, 1);
// //     std::shared_ptr<FlyingFistV> fv = std::make_shared<FlyingFistV>(fm, textures.getFistTextures());
// //     sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrado en SFML");
// //     std::shared_ptr<CupHeadM> cupM = std::make_shared<CupHeadM>(400,400,800,800);
// //     std::shared_ptr<CupHeadV> cupV = std::make_shared<CupHeadV>(cupM, textures.getRedRunTextures(),
// //                                                                 textures.getRedJumpTextures(),
// //                                                                 textures.getRedStandingTextures());
// //     std::shared_ptr<FlyingFistM> fm2 = std::make_shared<FlyingFistM>(1280,720, 2);
// //     std::shared_ptr<FlyingFistV> fv2 = std::make_shared<FlyingFistV>(fm2, textures.getFistTextures());     
                                                            

// //     bool inPlatform = false;
// //     sf::Clock clock, clock2;
// //     window.setFramerateLimit(60);
// //     while (window.isOpen())
// //     {
// //         sf::Event event;
// //         while (window.pollEvent(event))
// //         {
// //             if (event.type == sf::Event::Closed)
// //                 window.close();
// //         }
// //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && inPlatform)
// //         {
// //             inPlatform = false;
// //         }
// //         // Verificar si el cuadrado ha llegado al piso
// //         if (cupM->getPosY() >= 700)
// //         {
// //             inPlatform = true;
// //         }
// //         window.clear();
// //         float deltaTime = clock.restart().asSeconds();
// //         fm->update(clock2.getElapsedTime().asSeconds());
// //         fv->update();
// //         fm2->update(clock2.getElapsedTime().asSeconds());
// //         fv2->update();
// //         cupM->update(deltaTime
// //                     , sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
// //                     , sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
// //                     , sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
// //                     , inPlatform);
// //         cupV->update();
// //         fv->draw(window);
// //         fv2->draw(window);
// //         cupV->draw(window);
// //         window.display();
// //     }

// //     return 0;
// // }
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>
// #include <SFML/Window.hpp>

// int main()
// {
//     // Crear la ventana
//     sf::RenderWindow window(sf::VideoMode(1280, 720), "Ventana SFML");

//     // Crear el cuadrado
//     sf::RectangleShape square(sf::Vector2f(20, 20));
//     square.setFillColor(sf::Color::Red);
//     square.setPosition(630, 350); // Posición central aproximada

//     // Crear el reloj para medir el tiempo
//     sf::Clock clock;



//     // sf::Text timeText;
//     timeText.setCharacterSize(24);
//     timeText.setFillColor(sf::Color::White);
//     timeText.setPosition(10, 680); // Posición en la parte inferior izquierda

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // Actualizar el contador de tiempo
//         sf::Time elapsedTime = clock.getElapsedTime();
//         int seconds = elapsedTime.asSeconds();
//         int minutes = seconds / 60;
//         seconds %= 60;

//         // Actualizar el texto del contador de tiempo
//         timeText.setString("Tiempo: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));

//         window.clear();
//         window.draw(square);
//         window.draw(timeText);
//         window.display();
//     }

//     return 0;
// }
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ventana SFML");

    // Crear el cuadrado
    sf::RectangleShape square(sf::Vector2f(20, 20));
    square.setFillColor(sf::Color::Red);
    square.setPosition(630, 350); // Posición central aproximada

    // Crear el reloj para medir el tiempo
    sf::Clock clock;

    sf::Text timeText;
    sf::Font font;
    if (!font.loadFromFile("font/arial.ttf")) 
    {
        return -1; // Manejar error al cargar la fuente
    }
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::Yellow);
    timeText.setPosition(10, 680); // Posición en la parte inferior izquierda

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar el contador de tiempo
        sf::Time elapsedTime = clock.getElapsedTime();
        int seconds = elapsedTime.asSeconds();
        int minutes = seconds / 60;
        seconds %= 60;

        // Actualizar el texto del contador de tiempo
        timeText.setString("Tiempo: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));

        window.clear();
        window.draw(square);
        window.draw(timeText);
        window.display();
    }

    return 0;
}
