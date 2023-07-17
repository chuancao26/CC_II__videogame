#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
#include "WorkerBee.h"
class Textures
{
    private:
        std::vector<std::shared_ptr<sf::Texture>> workerBeeTextures;
        std::vector<std::shared_ptr<sf::Texture>> policeBeeTextures;
        std::vector<std::shared_ptr<sf::Texture>> misilTextures;
        std::vector<std::shared_ptr<sf::Texture>> trianguloTextures;
        int cantWB, cantPolice, cantMisil, cantTriangle;
    public:
    Textures():cantWB(5), cantMisil(9), cantPolice(5), cantTriangle(4)
    {
        loadTextures();
    }
    void loadTextures()
    {
        // WorkerBee
        workerBeeTextures.reserve(cantWB);
        for (size_t i{1}; i < cantWB; ++i)
        {
            workerBeeTextures.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/nivel_Bee/Bee_Worker/bee_grunt_flying_00" + tmp + std::to_string(i) + ".png";
            std::cout << filename << std::endl;
            if(!workerBeeTextures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }    
        // PoliceBee
        policeBeeTextures.reserve(cantPolice);
        for (size_t i{1}; i < cantPolice; ++i)
        {
            policeBeeTextures.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/nivel_Bee/PoliceBee/security_bee_move_00" + tmp + std::to_string(i) + ".png";
            std::cout << filename << std::endl;
            if(!policeBeeTextures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }  
        // MisilBee
        misilTextures.reserve(cantMisil);
        for (size_t i{1}; i < cantMisil; ++i)
        {
            misilTextures.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/nivel_Bee/MisilBee/bullet_bee_00" + tmp + std::to_string(i) + ".png";
            std::cout << filename << std::endl;
            if(!misilTextures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }  
        // Triangle
        trianguloTextures.reserve(cantTriangle);
        for (size_t i{1}; i < cantTriangle; ++i)
        {
            trianguloTextures.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/nivel_Bee/BeeTriangle/bee_triangle_magic_attack_00" + tmp + std::to_string(i) + ".png";
            std::cout << filename << std::endl;
            if(!trianguloTextures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }  
    }
    std::vector<std::shared_ptr<sf::Texture>> getTriangleTextures()
    {
            return trianguloTextures;
    }
    std::vector<std::shared_ptr<sf::Texture>> getPoliceTextures()
    {
            return policeBeeTextures;
    }
    std::vector<std::shared_ptr<sf::Texture>> getMisilBeeTextures()
    {
            return misilTextures;
    }
    std::vector<std::shared_ptr<sf::Texture>> getWorkerTextures()
    {
            return workerBeeTextures;
    }
};
class Fist
{
private:
    sf::Sprite sprite;
    std::vector<std::shared_ptr<sf::Texture>> textures;
    // std::shared_ptr<sf::Texture> texture;
    int xBorder, yBorder, size;
    float posx, posy, x, y, radiusX, radiusY, angle, speed;
    bool leftMove, charged;

public:
    Fist(const int& xb, const int& yb, const std::vector<std::shared_ptr<sf::Texture>>& textures_)
        : textures(textures_), xBorder(xb), yBorder(yb), leftMove(true), speed(2.0f),
          posx(xBorder / 2), posy(yBorder / 2), size(50), radiusX(200), radiusY(100), angle(0.0f),
          charged(false) //texture(new sf::Texture())
    {

    }
    // void load()
    // {
    //     for (size_t i{1}; i < 16; ++i)
    //     {
    //         textures.push_back(std::make_shared<sf::Texture>());
    //         std::string tmp = (i < 10 ? "0" : "");
    //         std::string filename = "img/nivel_Bee/Bee_Worker/bee_grunt_flying_00" + tmp + std::to_string(i) + ".png";
    //         std::cout << filename << std::endl;
    //         if(!textures[i - 1]->loadFromFile(filename))
    //             std::cout << "Problemas para cargar la imagen" << std::endl;
    //     }

    // }
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
        angle += 0.2f;
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
    // std::vector<std::shared_ptr<sf::Texture>> workerBeeTextures = ;
    Textures textures;
    window.setFramerateLimit(60);
    std::shared_ptr<Fist> fist = std::make_shared<Fist>(800,800,textures.getTriangleTextures());
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        //  workerBeeV->draw(window);
        // workerBeeV->update(rate);
        // workerBeeM->move();
        fist->update();
        fist->draw(window);
        window.display();
    }
    return 0;
}