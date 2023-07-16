#ifndef TEXTURES_H
#define TEXTURES_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>
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
#endif