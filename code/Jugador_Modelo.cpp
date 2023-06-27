#include "Jugador_Modelo.h"
using namespace std;
//using namespace sf;

float Jugador::getPosx() const {return posx;}
float Jugador::getPosy() const {return posy;}
int Jugador::getSize() const {return size;}
Cup::Cup(const int &px, const int& py, const int& size_)
{
    posx = px; posy = py; size = size_;
    saltando=false;
    enplataforma=false;
    vidas=3;
    gravedad=3;
    speed=10, salto = 150;
}
/*void Cup::dibujar(RenderWindow& a)
{
    caida();
    a.draw(cup);
}
sf::FloatRect Cup::getGlobalBounds() const
{
    return cup.getGlobalBounds();
}*/
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
    if (posy < 600.0f && !enplataforma && !saltando) {
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
void Cup::estaColisionando(const float& y)
{
    posy = y;
    mover(posx, posy);

}
void Cup::enPlataforma(bool t){
    enplataforma=t;
}
