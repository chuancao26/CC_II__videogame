#include "Jugador_Modelo.h"
using namespace std;

float Jugador::getPosx() const {return posx;}
float Jugador::getPosy() const {return posy;}
int Jugador::getSize() const {return size;}
Cup::Cup(const int &px, const int& py, const int& size_)
{
    posx = px; posy = py; size = size_;
    saltando=false;
    derecha=false;
    izquierda=false;
    enplataforma=false;
    vidas=3;saltos=1;
    gravedad=100;
    speed=10, salto = 150;
    clock_salto=0.f;
}

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
void Cup::caida(float d)
{
    if (posy < 800.0f && !enplataforma && !saltando) {
        posy += gravedad*d;
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
    posy = y;
    mover(posx, posy);

}
void Cup::enPlataforma(bool t){
    enplataforma=t;
}
