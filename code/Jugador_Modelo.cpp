#include "Jugador_Modelo.h"
using namespace std;

float Jugador::getPosx() const {return posx;}
float Jugador::getPosy() const {return posy;}
int Jugador::getSize() const {return size;}
void Cup::mover(const float& px, const float& py)
{
    posx = px;
    posy = py;
}
void Cup::moverIzquierda()
{
    if(posx >= 0)
    {
        posx = posx-speed;
    }
    
}
void Cup::moverDerecha()
{
    posx = posx+speed;
    
}
void Cup::moverAbajo()
{
    posy = posy+speed;
}
void Cup::moverArriba()
{
    posy = posy-speed;
}
void Cup::saltar()
{
    if (saltando)
    {
        posy -= salto;
    }
    mover(posx, posy);
}
void Cup::caida()
{
    if (posy < 800.0f && !enplataforma && !saltando) {
        posy += gravedad;
    }
    mover(posx,posy);
}
void Cup::actualizar() {

}
void Cup::estaSaltando(bool t)
{
    saltando=t;
}
void Cup::vaderecha(bool t)
{
    derecha=t;
}
void Cup::vaizquierda(bool t)
{
    izquierda=t;
}
void Cup::estaquieto(bool t)
{
    quieto=t;
}
void Cup::estaColisionando(const float& y)
{
    posy = y+10;
    mover(posx, posy);

}
void Cup::enPlataforma(bool t){
    enplataforma=t;
}
