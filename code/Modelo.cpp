#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include <thread>
#include <memory>

class Modelo
{
    public:
    Cup jugador1;
    Cup jugador2;
    Mapa* map;
    Plataforma pla;

    Modelo():jugador1(20,100,80), jugador2(200,100,80)
    {
        map= new Mapa();
    }
};