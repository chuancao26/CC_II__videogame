#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
#include "WorkerBee.h"
class Fist
{
private:
    sf::Color color;
    sf::Sprite sprite;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    // std::shared_ptr<sf::Texture> texture;
    int xBorder, yBorder, size;
    float posx, posy, x, y, radiusX, radiusY, angle, speed;
    bool leftMove, charged;

public:
    Fist(const int& xb, const int& yb)
        : color(sf::Color::Magenta), xBorder(xb), yBorder(yb), leftMove(true), speed(0.1f),
          posx(xBorder / 2), posy(yBorder / 2), size(50), radiusX(200), radiusY(100), angle(0.0f),
          charged(false) //texture(new sf::Texture())
    {
        textures.reserve(16);
        if (!charged)
        {
            load();
            charged = true;
        }
    }
    void load()
    {
        for (size_t i{1}; i < 16; ++i)
        {
            textures.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/nivel_Bee/Bee_Worker/bee_grunt_flying_00" + tmp + std::to_string(i) + ".png";
            std::cout << filename << std::endl;
            if(!textures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }

    }
    void move()
    {
        if (leftMove)
        {
            posx -= speed;
        }
        if (!leftMove)
        {
            posx += speed;
        }
    }
    void update()
    {
        angle += 0.01f;
        if (posx < 0 - size)
        {
            leftMove = false;
            
        }
        if (posx > xBorder + size)
        {
            leftMove = true;
        }
        move();
    }

void draw(sf::RenderWindow& window)
{
    size_t textureIndex = static_cast<size_t>(std::round(angle)) % textures.size();

    sprite.setTexture(*textures[textureIndex]);
    sprite.setPosition(posx, posy);

    sf::FloatRect bounds = sprite.getLocalBounds();

    // Establecer el origen de la rotación en el centro de la textura
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);

    // Establecer la escala del sprite
    sprite.setScale(0.8f, 0.8f); // Puedes ajustar los valores según tu necesidad

    // Rotar la textura para que mire hacia la derecha
    if (!leftMove)
    {
        sprite.setRotation(180.0f);
    }
    else
    {
        sprite.setRotation(0.0f);
    }

    window.draw(sprite);
}


};
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Cuadrado Movimiento Alas de Mariposa");
    std::shared_ptr<WorkerBeeM> workerBeeM;
    std::shared_ptr<WorkerBeeV> workerBeeV;
    window.setFramerateLimit(60);
    workerBeeM = std::make_shared<WorkerBeeM> (800, 800);
    workerBeeV = std::make_shared<WorkerBeeV> (workerBeeM);
    float rate = 0.0f;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        rate += 0.1;
        window.clear();
         workerBeeV->draw(window);
        workerBeeV->update(rate);
        workerBeeM->move();
        
       
        window.display();
    }
    return 0;
}