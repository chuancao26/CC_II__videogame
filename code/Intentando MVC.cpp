#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string>

// Modelo
class CuadradoModel {
private:
    float x;
    float y;
    float size;
    float maxY;
    float velocidad;

    bool esperando;
    sf::Clock relojEspera;
    bool eliminado;

public:
    bool llegoMaximo;
    CuadradoModel(float ventanaAncho = 0.0f, float ventanaAlto = 0.0f)
        : x(0.0f), y(ventanaAlto / 20), size(50.0f),
          maxY(ventanaAlto * 7 / 9), velocidad(4.0f),
          llegoMaximo(false), esperando(false), eliminado(false) {}

    void setX(float posX) {
        x = posX;
    }

    void caer() {
        if (!llegoMaximo) {
            if (y < maxY) {
                y += velocidad;
            } else {
                llegoMaximo = true;
                relojEspera.restart();
                esperando = true;
            }
        } else {
            if (esperando) {
                if (relojEspera.getElapsedTime().asSeconds() >= 5.0f) {
                    esperando = false;
                    llegoMaximo = false;
                    setX(static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (x * 3 / 5)));
                    eliminado = true;
                }
            } else {
                if (y < maxY) {
                    y += velocidad;
                }
            }
        }
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getSize() const {
        return size;
    }

    bool isEliminado() const {
        return eliminado;
    }
};

class BoomerangModel {
private:
    float x;
    float y;
    float width;
    float height;
    int direction;
    bool deleteFlag;

public:
    BoomerangModel(float startX, float startY, float width, float height) :
        x(startX), y(startY), width(width), height(height), direction(1), deleteFlag(false)
    {
    }

    void moveRight(float windowWidth) {
        x += 7.0f;
        if (x >= windowWidth - width) {  // Extremo derecho
            direction--;  // Cambiar dirección a izquierda
        }
    }

    void moveLeft() {
        x -= 7.0f;
        if (x <= -2 * width) {  // Punto de inicio
            direction = 0;  // Cambiar dirección a derecha
        }
    }

    void update(float windowWidth) {
        if (direction == 1) {
            moveLeft();
        }
        else if (direction == 0) {
            moveRight(windowWidth);
        }
        else {
            deleteFlag = true;
        }
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getWidth() const {
        return width;
    }

    float getHeight() const {
        return height;
    }

    bool shouldDelete() const {
        return deleteFlag;
    }

    void deleteBoomerang() {
        deleteFlag = true;
    }

    bool reachedRightEdge(float windowWidth) const {
        return (x >= windowWidth - width);
    }
};


// Vista
class CuadradoView {
private:
    sf::Sprite sprite;
    sf::Texture texturaCae;
    sf::Texture texturaPiso;
    sf::RenderWindow window;

public:
    CuadradoView() {
        if (!texturaCae.loadFromFile("bombaCae.png")) {
            std::cout << "Error al cargar la imagen bombaCae.png" << std::endl;
        }

        if (!texturaPiso.loadFromFile("bombaPiso.png")) {
            std::cout << "Error al cargar la imagen bombaPiso.png" << std::endl;
        }

        sprite.setTexture(texturaPiso);
    }

    void setSize(float size) {
        sprite.setScale(size / texturaPiso.getSize().x, size / texturaPiso.getSize().y);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void setTextureCae() {
        sprite.setTexture(texturaCae);
    }

    void setTexturePiso() {
        sprite.setTexture(texturaPiso);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

};

class BoomerangView {
private:
    sf::Sprite sprite;
    sf::Texture texture1;
    sf::Texture texture2;


public:
    BoomerangView(float width, float height) {
        // Cargar las texturas desde los archivos
        if (!texture1.loadFromFile("boomerang1.png")) {
            // Manejar el error si la carga de la textura 1 falla
            std::cout << "Error al cargar la imagen boomerang1.png" << std::endl;
        }

        if (!texture2.loadFromFile("boomerang2.png")) {
            // Manejar el error si la carga de la textura 2 falla
            std::cout << "Error al cargar la imagen boomerang2.png" << std::endl;
        }

        // Establecer la textura inicial en el sprite y ajustar su escala
        sprite.setTexture(texture1);
        sprite.setScale(width / texture1.getSize().x, height / texture1.getSize().y * 1.3);
    }

    void updateTexture(float x) {
        if ((x > 100 && x < 200) || (x > 300 && x < 400) || (x > 500 && x < 600) || (x > 700)) {
            sprite.setTexture(texture1);
        }
        else {
            sprite.setTexture(texture2);
        }
    }

    void draw(sf::RenderWindow& window, float x, float y) {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
};

// Controlador

class CuadradoController {
private:
    std::vector<CuadradoModel> cuadrados;
    CuadradoView cuadradoView;

public:
    CuadradoController(float ventanaAncho, float ventanaAlto) : cuadrados(1), cuadradoView(){
        //float elapsedSeconds = 0.0f;
        //elapsedSeconds = clock.getElapsedTime().asSeconds();
        for (int i = 0; i < 1; i++) {
            //if (elapsedSeconds >= interval*i)
            //{
                float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (ventanaAncho * 3 / 5));
                cuadrados[i] = CuadradoModel(ventanaAncho, ventanaAlto);
                cuadrados[i].setX(posicionX);
                cuadrados[i].caer();
            //}
        }
    }

    void update() {
        for (auto& cuadrado : cuadrados) {
            cuadrado.caer();
        }
    }


    void draw(sf::RenderWindow& window) {
        for (const auto& cuadrado : cuadrados) {
            if (!cuadrado.isEliminado()) {
                cuadradoView.setSize(cuadrado.getSize());
                cuadradoView.setPosition(cuadrado.getX(), cuadrado.getY());

                if (cuadrado.llegoMaximo) {
                    cuadradoView.setTexturePiso();
                } else {
                    cuadradoView.setTextureCae();
                }

                cuadradoView.draw(window);
            }
        }
    }

};
class BoomerangController {
private:
    BoomerangModel boomerangModel;
    BoomerangView boomerangView;

public:
    BoomerangController(float startX, float startY, float width, float height) :
        boomerangModel(startX, startY, width, height), boomerangView(width, height)
    {
    }

    void update(float windowWidth) {
        boomerangModel.update(windowWidth);
    }

    void draw(sf::RenderWindow& window) {
        float x = boomerangModel.getX();
        float y = boomerangModel.getY();

        boomerangView.updateTexture(x);
        boomerangView.draw(window, x, y);
    }

    bool shouldDelete() const {
        return boomerangModel.shouldDelete();
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrados");
    window.setFramerateLimit(60);

    BoomerangController boomerang(window.getSize().x * 45 / 64, window.getSize().y / 3, window.getSize().x / 7, window.getSize().y / 10);

    const int maxCuadrados = 5;
    CuadradoController* cuadrados[maxCuadrados] = {}; // Arreglo de punteros a CuadradoController
    float elapsedSeconds = 0.0f;
    float interval = 1.0f; // Intervalo de tiempo entre la aparición de los cuadrados (1 segundo)

    //Boomerang
    sf::Time tiempoAcumulado = sf::Time::Zero;
    sf::Clock relojMovimiento;

    //Cuadrado
    sf::Clock clock;
    sf::Clock timer; // Reloj para controlar el intervalo de tiempo

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
            for (int i = 0; i < maxCuadrados; i++) {
                if (cuadrados[i] == nullptr) {
                    indice = i;
                    break;
                }
            }

            // Si se encontró un espacio disponible, crear un nuevo CuadradoController en esa posición
            if (indice != -1) {
                cuadrados[indice] = new CuadradoController(window.getSize().x, window.getSize().y);
                cuadrados[indice]->update();
                cuadrados[indice]->draw(window);
            }

            // Reiniciar el reloj para el siguiente intervalo
            timer.restart();
        }
        
        boomerang.update(window.getSize().x);
        window.clear(sf::Color::White);
        if (!boomerang.shouldDelete()) {
            boomerang.draw(window);
        }
        // Actualizar y dibujar los cuadrados existentes en el arreglo
        for (int i = 0; i < maxCuadrados; i++) {
            if (cuadrados[i] != nullptr) {
                cuadrados[i]->update();
                cuadrados[i]->draw(window);
            }
        }

        window.display();
    }

    // Liberar la memoria de los CuadradoController creados
    for (int i = 0; i < maxCuadrados; i++) {
        delete cuadrados[i];
    }

    return 0;
}

