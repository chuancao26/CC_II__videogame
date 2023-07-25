#ifndef MODEL_H
#define MODEL_H
// #include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include <thread>
#include <iostream> 
#include <memory>
#include <vector>
class Model
{
private:
    // Cup player1;
    std::shared_ptr<Mapa> map;
    Plataforma pla;
    float elapsedTime, platDeleteTime, platCreatTime;
public:
    Model():platDeleteTime(0.0f), platCreatTime(0.0f)
    , map(std::make_shared<Mapa>())
    {

    }
    void update(const float& elapsedTime_)
    {
        elapsedTime = elapsedTime_;
    }
    void crearMapa()
    {
        std::vector<std::string> mapstrings = map->crearMapa(5);
        map ->parseMap(mapstrings);
    }
    void manejarEventos()
    {
        
    }
    void eliminarPlataformas()
    {
        if(elapsedTime - platDeleteTime >= 2.5f)
        {
            map->eliminarPlataformas();
            platDeleteTime = elapsedTime;
        }
    }
    void crearPlataformas()
    {
        if (map->getSize() == 0)
        {
            crearMapa();
        }
        else
        {
            if(elapsedTime - platCreatTime >= 1.0f)
            {
                map -> crearPlataformas();
                platCreatTime = elapsedTime;    
            }
        }
    }
    std::shared_ptr<Mapa> getMap()
    {
        return map;
    }
    // Cup& getPlayer1()
    // {
    //     return player1;
    // }
};

#endif
