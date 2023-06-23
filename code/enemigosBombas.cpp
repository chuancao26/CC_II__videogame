
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <cmath>

class Cuadrado {
private:
    sf::Sprite* sprite;
    sf::Texture* texturaCae;
    sf::Texture* texturaPiso;
    float x;
    float y;
    float size;
    float maxY;
    float velocidad;
    bool llegoMaximo;
    bool esperando;
    sf::Clock relojEspera;
    bool eliminado;

public:
    Cuadrado(float ventanaAncho, float ventanaAlto) :
        x(0.0f), y(ventanaAlto / 20), size(60.0f),
        maxY(ventanaAlto * 7 / 9), velocidad(4.0f),
        llegoMaximo(false), esperando(false), eliminado(false)
    {
        sprite = new sf::Sprite();
        texturaCae = new sf::Texture();
        texturaPiso = new sf::Texture();

        if (!texturaCae->loadFromFile("bombaCae.png")) {
            std::cout << "Error al cargar la imagen bombaCae.png" << std::endl;
        }

        if (!texturaPiso->loadFromFile("bombaPiso.png")) {
            std::cout << "Error al cargar la imagen bombaPiso.png" << std::endl;
        }

        sprite->setTexture(*texturaPiso);
        sprite->setScale(size / texturaPiso->getSize().x, size / texturaPiso->getSize().y);
        sprite->setPosition(x, y);

        setX(static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (ventanaAncho * 3 / 5)));
    }

    ~Cuadrado() {
        //delete sprite;
        //delete texturaCae;
        //delete texturaPiso;
    }

    void setX(float posX) {
        x = posX;
        sprite->setPosition(x, y);
    }

    void caer() {
        if (!llegoMaximo) {
            if (y < maxY) {
                y += velocidad;
                sprite->setPosition(x, y);
            }
            else {
                llegoMaximo = true;
                relojEspera.restart();
                esperando = true;
            }
        }
        else {
            if (esperando) {
                if (relojEspera.getElapsedTime().asSeconds() >= 5.0f) {
                    esperando = false;
                    llegoMaximo = false;
                    setX(static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (sprite->getPosition().x * 3 / 5)));
                    eliminado = true;
                }
            }
            else {
                if (y < maxY) {
                    y += velocidad;
                    sprite->setPosition(x, y);
                }
            }
        }
    }

    float getX() {
        return x;
    }

    void draw(sf::RenderWindow& window) {
        if (!eliminado) {
            if (llegoMaximo) {
                sprite->setTexture(*texturaPiso);
            }
            else {
                sprite->setTexture(*texturaCae);
            }
            window.draw(*sprite);
        }
    }
};


class Boomerang {
private:
    float x;
    float y;
    float width;
    float height;
    int direction;
    bool deleteFlag;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Sprite sprite;

public:
    Boomerang(float startX, float startY, float width, float height) :
        x(startX), y(startY), width(width), height(height), direction(1), deleteFlag(false)
    {
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
        sprite.setScale(width / texture1.getSize().x, height / texture1.getSize().y*1.3);
    }

    void moveRight(sf::RenderWindow& window) {
        x += 7.0f;
        if (x >= window.getSize().x - width) {  // Extremo derecho
            direction--;  // Cambiar dirección a izquierda
        }
    }

    void moveLeft(sf::RenderWindow& window) {
        x -= 7.0f;
        if (x <= -2 * width) {  // Punto de inicio
            direction = 0;  // Cambiar dirección a derecha
        }
    }

    void update(sf::RenderWindow& window) {
        if (direction == 1) {
            moveLeft(window);
        }
        else if (direction == 0) {
            moveRight(window);
        }
        else {
            deleteFlag = true;
        }
    }

    void draw(sf::RenderWindow& window) {
        if (x>900){
            x=1600;
        }
        if ((x > 100 && x < 200) || (x > 300 && x < 400) || (x > 500 && x < 600) || (x > 700)) {
            sprite.setTexture(texture1);
        }
        else {
            sprite.setTexture(texture2);
        }

        sprite.setPosition(x, y);
        window.draw(sprite);
    }

    bool shouldDelete() {
        return deleteFlag;
    }

    void deleteBoomerang() {
        deleteFlag = true;
    }

    bool reachedRightEdge(sf::RenderWindow& window) {
        return (x >= window.getSize().x - width);
    }
};


class Cabeza {
public:
    Cabeza(sf::RenderWindow& window) : window_(window) {
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

class Background {
public:
    Background(sf::RenderWindow& window) : window_(window) {
        if (!texture_.loadFromFile("fondoFlor.png")) {
            // Error al cargar la imagen fondoFlor.png
            return;
        }

        sprite_.setTexture(texture_);

        // Escala la imagen para que encaje con el tamaño de la ventana
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
int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrados");
    window.setFramerateLimit(60);

    Cuadrado* cuadrados[4];
    for (int i = 0; i < 4; i++) {
        cuadrados[i] = new Cuadrado(window.getSize().x, window.getSize().y);
    }

    Boomerang boomerang(window.getSize().x * 45 / 64, window.getSize().y / 3, window.getSize().x / 7, window.getSize().y / 10);

    sf::Clock clock; //Cuadrados
    float elapsedSeconds = 0.0f;
    float interval = 0.8f;

    Cabeza cabeza(window);

    sf::Clock clock2; //Boomerang
    Background background(window); //Fondo

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        boomerang.update(window);

        float deltaTime2 = clock2.restart().asSeconds();
        cabeza.update(deltaTime2);

        window.clear(sf::Color::White);
        background.draw();

        elapsedSeconds = clock.getElapsedTime().asSeconds();
        for (int i = 0; i < 4; i++) {
            if (elapsedSeconds >= interval*i)
            {
                    cuadrados[i]->caer();
                    cuadrados[i]->draw(window);
            }
        }
        boomerang.draw(window);
        cabeza.draw();

        window.display();
    }

    for (int i = 0; i < 4; i++) {
        delete cuadrados[i];
    }

    cabeza.removeRectangles();

    return 0;
}
