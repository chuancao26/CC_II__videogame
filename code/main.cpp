#include "Controlador.cpp"
#include "GameController.h"
#include <iostream>
using namespace std;
using namespace sf;
void ejecutar(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrados");
    window.setFramerateLimit(60);

    BoomerangController boomerang(window.getSize().x * 45 / 64, window.getSize().y / 3, window.getSize().x / 7, window.getSize().y / 10);

    const int maxBombs = 5;
    BombController* bombs[maxBombs] = {}; // Arreglo de punteros a CuadradoController
    float elapsedSeconds = 0.0f;
    float interval = 1.0f; // Intervalo de tiempo entre la aparición de los cuadrados (1 segundo)

    //Boomerang
    sf::Time tiempoAcumulado = sf::Time::Zero;
    sf::Clock relojMovimiento;

    //Cuadrado
    sf::Clock clock;
    sf::Clock timer; // Reloj para controlar el intervalo de tiempo

    FlorBossView florBoss(window); //Crear view del Boss
    sf::Clock clock2;

    Background background(window); //Fondo del juego "Cagney Carnation"

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calcular el tiempo transcurrido desde la última aparición de un cuadrado
        float deltaTime = timer.getElapsedTime().asSeconds();
        if (deltaTime >= interval) {
            // Generar una nueva posición aleatoria para el cuadrado
            float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (window.getSize().x * 3 / 5));

            // Buscar un espacio disponible en el arreglo de punteros
            int indice = -1;
            for (int i = 0; i < maxBombs; i++) {
                if (bombs[i] == nullptr) {
                    indice = i;
                    break;
                }
            }

            // Si se encontró un espacio disponible, crear un nuevo CuadradoController en esa posición
            if (indice != -1) {
                bombs[indice] = new BombController(window.getSize().x, window.getSize().y);
                bombs[indice]->update();
                bombs[indice]->draw(window);
            }

            // Reiniciar el reloj para el siguiente intervalo
            timer.restart();
        }
        
        boomerang.update(window.getSize().x);

        float deltaTime2 = clock2.restart().asSeconds();
        florBoss.update(deltaTime2);

        window.clear(sf::Color::White);
        background.draw();
        if (!boomerang.shouldDelete()) {
            boomerang.draw(window);
        }
        // Actualizar y dibujar los cuadrados existentes en el arreglo
        for (int i = 0; i < maxBombs; i++) {
            if (bombs[i] != nullptr) {
                bombs[i]->update();
                bombs[i]->draw(window);
            }
        }

        florBoss.draw();
        
        window.display();
    }

    // Liberar la memoria de los CuadradoController creados
    for (int i = 0; i < maxBombs; i++) {
        delete bombs[i];
    }
}
int main() {
    int xedge = 1280, yedge = 720, size = 60;
    float posx = 20, posy = 600;
    std::vector<std::string> mapStrings =
    {
        "A   A  A",
        "  A    A",
        " P P   A",
        "PPPPPP  "
    };
    Cup a(posx, posy, size); 
    Controlador controlador(a,mapStrings);
    controlador.ejecutar();
    
    GameController gameController;
    gameController.Run();

    ejecutar();
    return 0;
}