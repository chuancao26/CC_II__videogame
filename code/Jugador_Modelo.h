#ifndef JUGADOR_MODELO_H
#define JUGADOR_MODELO_H
#include <iostream>
using namespace std;

class Jugador
{
    public:
        float posx, posy, gravedad, speed, clock_salto;
        int size,saltos;
        bool vulnerable;
    public:
        Jugador(float px, float py, float grav, float spd, float clk_salto, int sz, int s, bool v)
        : posx(px), posy(py), gravedad(grav), speed(spd), clock_salto(clk_salto),
          size(sz), saltos(s), vulnerable(v)
        {
        }
        Jugador()
        {
            
        }
        float getPosx() const;
        float getPosy() const;
        int getSize() const;
        virtual void mover(const float& px, const float& py)=0;
};

class Cup: public Jugador {
public:
    bool saltando,enplataforma,derecha,izquierda,quieto;
    float salto;
    int jumps, vidas;
public:
    Cup(float px, float py, int size_)
    :Jugador(px, py, 15.0f, 20.0f, 0.0f, size_, 1, false), saltando(false),
    derecha(false), izquierda(false), enplataforma(false), vidas(3),
    salto(150)
    {
    }
    Cup()
    {

    }
    virtual void mover(const float& px, const float& py);
    void moverIzquierda();
    void moverDerecha();
    void moverArriba();
    void moverAbajo();
    void saltar();
    void actualizar();
    void estaSaltando(const bool& t);
    void vaderecha(const bool& t);
    void vaizquierda(const bool& t);
    void estaquieto(const bool& t);
    void caida();
    void estaColisionando(const float& y);
    void enPlataforma(const bool& t);
};

class CupMuerto : public Jugador
{
    public:
        void mover();
        void posicion(); // Ubicar el mapa
        // void volar(); creo que solo se esta moviendo
        void revivir();  //se revive y el fantasma regresa al pool Cup cup1 cup.es_invulnerable=True;
        void colision(); //tocado por la tecla saltar de amigo, o si llega al borde superior de la ventana
};
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
void Cup::estaSaltando(const bool& t)
{
    saltando=t;
}
void Cup::vaderecha(const bool& t)
{
    derecha=t;
}
void Cup::vaizquierda(const bool& t)
{
    izquierda=t;
}
void Cup::estaquieto(const bool& t)
{
    quieto=t;
}
void Cup::estaColisionando(const float& y)
{
    posy = y+10;
    mover(posx, posy);

}
void Cup::enPlataforma(const bool& t){
    enplataforma=t;
}

#endif