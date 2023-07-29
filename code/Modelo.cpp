#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include <thread>
#include <memory>

class Modelo
{
    public:
    Cup jugador1;
    Cup jugador2;
    int vidas; 
    Mapa* map;
    Plataforma pla;

    Modelo():jugador1(20,100,80), jugador2(200,100,80)
    {
        map= new Mapa();
    }
    void crearMapa()
    {
        std::vector<std::string> mapStrings = map->crearMapa(50);
        map->parseMap(mapStrings);
    }
    void crearplataformas()
    {
        if(map->size==0)
        {
            crearMapa();
        }
    }
};