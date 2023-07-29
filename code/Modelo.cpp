#include "Jugador_Modelo.h"
#include "Plataforma_Modelo.h"
#include "Disparo_Modelo.cpp"
#include <thread>
#include <memory>

class Modelo
{
    public:
    Cup jugador1;
    Cup jugador2;
    Mapa* map;
    Plataforma pla;
    DisparoNormal d_normal;
    DisparoBomba d_bomba;
    DisparoEstrella d_estrella;

    Modelo():jugador1(20,100,80), jugador2(200,100,80)
    {
        map= new Mapa();
    }
    void crearMapa(int tipo)
    {
        if(tipo==1)
        {
            std::vector<std::string> mapStrings = map->crearMapa(50);
            map->parseMap(mapStrings);
        }
        else if(tipo==2)
        {
            std::vector<std::string> mapStrings = 
            {
                "PPPPPP",
                "PPP"
            };
            map->parseMap2(mapStrings);
        }
        
    }
    void asignarDisparos(int tipo, Cup& jugador)
    {
        switch (tipo)
        {
        case 1:
            jugador.setDisparo(&d_normal);
            break;
        case 2:
            jugador.setDisparo(&d_bomba);
            break;
        case 3:
            jugador.setDisparo(&d_estrella);
            break;
        }
    }
    void crearplataformas(int tipo)
    {
        if(map->size==0)
        {
            crearMapa(tipo);
        }
    }

    void limpiarPlataformas()
    {
        map->size=0;
        Plataforma* plat=new Plataforma[map->size];
        delete [] map->platforms;
        map->platforms=plat;
    }

    void moverBalas(Cup& jugador, int tipo)
    {
        if(jugador.disparo->size>0)
        {
            switch (tipo)
            {
                case 1:
                    jugador.disparo->balas[0]->mover();
                    break;
                case 2:
                    jugador.disparo->balas[0]->mover();
                    break;

                case 3:
                    jugador.disparo->balas[0]->mover(20.0f,0.0f);
                    jugador.disparo->balas[1]->mover(10.0f,10.0f);
                    jugador.disparo->balas[2]->mover(10.0f,-10.0f);
                    break;

            }
        }
        
    }
};