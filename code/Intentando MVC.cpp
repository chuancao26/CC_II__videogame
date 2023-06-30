#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string>

// Modelo
class BombModel {
private:
    float x;
    float y;
    float size;
    float maxY;
    float velocidad;
    bool esperando;
    std::chrono::steady_clock::time_point relojEspera;
    bool eliminado;

public:
    bool llegoMaximo;
    BombModel(float ventanaAncho = 0.0f, float ventanaAlto = 0.0f)
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
                relojEspera = std::chrono::steady_clock::now();
                esperando = true;
            }
        } else {
            if (esperando) {
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                std::chrono::duration<float> elapsed = now - relojEspera;
                if (elapsed.count() >= 5.0f) {
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
class BombView {
private:
    sf::Sprite sprite;
    sf::Texture texturaCae;
    sf::Texture texturaPiso;
    sf::RenderWindow window;

public:
    BombView() {
        if (!texturaCae.loadFromFile("bombaCae.png")) {
            std::cout << "Error al cargar la imagen bombaCae.png" << std::endl;
        }

        if (!texturaPiso.loadFromFile("bombaPiso.png")) {
            std::cout << "Error al cargar la imagen bombaPiso.png" << std::endl;
        }

        sprite.setTexture(texturaPiso);
    }

    void setSize(float size) {
        sprite.setScale(size / texturaPiso.getSize().x*1.2, size / texturaPiso.getSize().y*1.2);
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
        sprite.setScale(width / texture1.getSize().x, height / texture1.getSize().y * 1.5);
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

class BombController {
private:
    std::vector<BombModel> bombs;
    BombView cuadradoView;

public:
    BombController(float ventanaAncho, float ventanaAlto) : bombs(1), cuadradoView(){
        //float elapsedSeconds = 0.0f;
        //elapsedSeconds = clock.getElapsedTime().asSeconds();
        for (int i = 0; i < 1; i++) {
            //if (elapsedSeconds >= interval*i)
            //{
                float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (ventanaAncho * 3 / 5));
                bombs[i] = BombModel(ventanaAncho, ventanaAlto);
                bombs[i].setX(posicionX);
                bombs[i].caer();
            //}
        }
    }

    void update() {
        for (auto& bomb : bombs) {
            bomb.caer();
        }
    }


    void draw(sf::RenderWindow& window) {
        for (const auto& cuadrado : bombs) {
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

//BossView

class FlorBossView {
public:
    FlorBossView(sf::RenderWindow& window) : window_(window) {
        if (!textureGreen_.loadFromFile("normal1.png")) {
            // Error al cargar la imagen normal1.png
            return;
        }

        if (!texturePurple_.loadFromFile("normal2.png")) {
            // Error al cargar la imagen normal2.png
            return;
        }

        spriteGreen_.setTexture(textureGreen_);
        spritePurple_.setTexture(texturePurple_);

        spriteGreen_.setScale(window.getSize().x / 3 / spriteGreen_.getLocalBounds().width,
                              ((window.getSize().y * 4) / 5) / spriteGreen_.getLocalBounds().height);
        spritePurple_.setScale(window.getSize().x / 3 / spritePurple_.getLocalBounds().width,
                               ((window.getSize().y * 4) / 5) / spritePurple_.getLocalBounds().height);

        spriteGreen_.setPosition(window_.getSize().x - (spriteGreen_.getLocalBounds().width)/1.1,
                                 window.getSize().y / 12);
        spritePurple_.setPosition(window_.getSize().x - (spritePurple_.getLocalBounds().width)/1.1,
                                  window.getSize().y / 12);
        textureGreen_.setSmooth(true);
        texturePurple_.setSmooth(true);
        rectThird_.setSize(sf::Vector2f(200.0f, 250.0f));
        rectThird_.setFillColor(sf::Color::Blue);
        rectThird_.setPosition(window_.getSize().x, (window_.getSize().y - rectThird_.getSize().y) / 2.0f);

        isGreenActive_ = true;
        timer_ = 0.0f;
        duration_ = 0.5f;
        isGrowing_ = false;
        growthTimer_ = 0.0f;
        growthDuration_ = 2.0f;
    }

    void update(float deltaTime) {
        timer_ += deltaTime;
        growthTimer_ += deltaTime;

        if (timer_ >= duration_) {
            isGreenActive_ = !isGreenActive_;
            timer_ = 0.0f;
        }

        if (isGrowing_) {
            float growthAmount = (window_.getSize().x - rectThird_.getSize().x) / growthDuration_ * deltaTime;
            rectThird_.setSize(rectThird_.getSize() + sf::Vector2f(growthAmount, 0.0f));
            rectThird_.setPosition(rectThird_.getPosition().x - growthAmount, rectThird_.getPosition().y);

            if (growthTimer_ >= growthDuration_) {
                rectThird_.setSize(sf::Vector2f(200.0f, 250.0f));
                rectThird_.setPosition(window_.getSize().x, (window_.getSize().y - rectThird_.getSize().y) / 2.0f);

                growthTimer_ = 0.0f;
                isGrowing_ = false;
            }
        }
    }

    void draw() {
        if (isGreenActive_) {
            window_.draw(spriteGreen_);
        } else {
            window_.draw(spritePurple_);
        }

        window_.draw(rectThird_);
    }
    void removeRectangles() {
        spriteGreen_.setScale(0.0f, 0.0f);
        spritePurple_.setScale(0.0f, 0.0f);
        rectThird_.setSize(sf::Vector2f(0.0f, 0.0f));
    }

    void startGrowing() {
        if (!isGrowing_) {
            isGrowing_ = true;
            growthTimer_ = 0.0f;
        }
    }


private:
    sf::RenderWindow& window_;
    sf::Texture textureGreen_;
    sf::Texture texturePurple_;
    sf::Sprite spriteGreen_;
    sf::Sprite spritePurple_;
    sf::RectangleShape rectThird_;
    bool isGreenActive_;
    float timer_;
    float duration_;
    bool isGrowing_;
    float growthTimer_;
    float growthDuration_;
};

//FondoView
class Background {
public:
    Background(sf::RenderWindow& window) : window_(window) {
        if (!texture_.loadFromFile("fondoFlor.png")) {
            // Error al cargar la imagen fondoFlor.png
            return;
        }

        sprite_.setTexture(texture_);

        // Escala la imagen para que encaje con el tama�o de la ventana
        float scaleX = static_cast<float>(window.getSize().x) / sprite_.getLocalBounds().width;
        float scaleY = static_cast<float>(window.getSize().y) / sprite_.getLocalBounds().height;
        sprite_.setScale(scaleX, scaleY);
    }

    void draw() {
        window_.draw(sprite_);
    }

private:
    sf::RenderWindow& window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

int main() {
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

    return 0;
}
