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
void Cup::update(const float& elapsedTime_)
{
    elapsedTime = elapsedTime_;
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
void Cup::setDisparo(Disparo* disparo_) 
{
    disparo = disparo_;
}

void Cup::disparar(const float& px, const float& py) 
{
    disparo->disparar(px, py);
}
void Cup::morir()
{
    vidas-=1;
    std::cout<<vidas<<std::endl;
}
void Cup::enChoque(const bool& t)
{
    choque = t;

    if (choque && !isInvunerable)
    {
        --vidas; 
        //start = elapsedTime;
        //isInvunerable = true;
    }
    /*if (elapsedTime - start > 2.0f)
    {
        isInvunerable = false;
    }*/
}
