#ifndef MODEL_H
#define MODEL_H
#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Vista.cpp"
#include "Boss_Vista.cpp"
#include "Background_Vista.cpp"
#include "Boomerang_Controlador.cpp"
#include "Bomba_Controlador.cpp"
#include "Elegir.cpp"
#include <thread>
#include <iostream> 
#include <memory>
#include <vector>
#include "vistaBee.h"
class Model
{
private:
    Cup player1;
    std::shared_ptr<Mapa> map;
    Plataforma pla;
    float elapsedTime, platDeleteTime, platCreatTime;
public:
    Model():player1(20,100,80), platDeleteTime(0.0f), platCreatTime(0.0f)
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
    Cup& getPlayer1()
    {
        return player1;
    }
};

#endif
