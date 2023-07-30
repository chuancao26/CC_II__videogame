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
        std::vector<std::shared_ptr<sf::Texture>> espinasTextures;
        std::vector<std::shared_ptr<sf::Texture>> bombTextures;
        std::vector<std::shared_ptr<sf::Texture>> redRun;
        std::vector<std::shared_ptr<sf::Texture>> blueRun;
        std::vector<std::shared_ptr<sf::Texture>> redJump;
        std::vector<std::shared_ptr<sf::Texture>> blueJump;
        std::vector<std::shared_ptr<sf::Texture>> redStanding;

        int cantWB, cantPolice, cantMisil, cantTriangle, cantEspinas, cantBomb,
            cantRedRun, cantRedJump, cantBlueJump, cantBlueRun, cantRedStanding;
    public:
    Textures():cantWB(6), cantMisil(10), cantPolice(6), cantTriangle(5), cantEspinas(7), cantBomb(4),
    cantBlueRun(7), cantRedRun(7), cantRedJump(5), cantBlueJump(5), cantRedStanding(5)
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
            
            if(!trianguloTextures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }  
        // Espinas
        espinasTextures.reserve(cantEspinas);
        for (size_t i{1}; i < cantEspinas; ++i)
        {
            espinasTextures.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/nivel_Bee/Espinas/bee_bomb_stinger_b_00" + tmp + std::to_string(i) + ".png";
            
            if(!espinasTextures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }  
        // Espinas
        bombTextures.reserve(cantBomb);
        for (size_t i{1}; i < cantBomb; ++i)
        {
            bombTextures.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/nivel_Bee/Bomb/bee_bomb_warning_b_00" + tmp + std::to_string(i) + ".png";
            
            if(!bombTextures[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        } 
        redJump.reserve(cantRedJump);
        for (size_t i{1}; i < cantRedJump; ++i)
        {
            redJump.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/cuphead/RedCup/saltar/cuphead_jump_00" + tmp + std::to_string(i) + ".png";
            
            if(!redJump[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        } 
        redRun.reserve(cantRedRun);
        for (size_t i{1}; i < cantRedRun; ++i)
        {
            redRun.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/cuphead/RedCup/caminar/cuphead_run_00" + tmp + std::to_string(i) + ".png";
            
            if(!redRun[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        }
        blueJump.reserve(cantBlueJump);
        for (size_t i{1}; i < cantBlueJump; ++i)
        {
            blueJump.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/cuphead/BlueCup/saltar/mugman_jump_00" + tmp + std::to_string(i) + ".png";
            
            if(!blueJump[i - 1]->loadFromFile(filename))
                std::cout << "Problemas para cargar la imagen" << std::endl;
        } 
        redStanding.reserve(cantRedStanding);
        for (size_t i{1}; i < cantRedStanding; ++i)
        {
            redStanding.push_back(std::make_shared<sf::Texture>());
            std::string tmp = (i < 10 ? "0" : "");
            std::string filename = "img/cuphead/RedCup/quieto/cuphead_idle_00" + tmp + std::to_string(i) + ".png";
            
            if(!redStanding[i - 1]->loadFromFile(filename))
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
    std::vector<std::shared_ptr<sf::Texture>> getEspinasTextures()
    {
        return espinasTextures;
    }
    std::vector<std::shared_ptr<sf::Texture>> getBombTextures()
    {
        return bombTextures;
    }
    std::vector<std::shared_ptr<sf::Texture>> getRedJumpTextures()
    {
        return redJump;
    }
    std::vector<std::shared_ptr<sf::Texture>> getBlueJumpTextures()
    {
        return blueJump;
    }
    std::vector<std::shared_ptr<sf::Texture>> getRedRunTextures()
    {
        return redRun;
    }
    std::vector<std::shared_ptr<sf::Texture>> getBlueRunTextures()
    {
        return blueRun;
    }
    std::vector<std::shared_ptr<sf::Texture>> getRedStandingTextures()
    {
        return redStanding;
    }
    

};
#endif