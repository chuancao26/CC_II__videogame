#ifndef JUGADOR_MODELO_H
#define JUGADOR_MODELO_H
#include "Disparo_Modelo.cpp"
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
    Disparo* disparo;
public:
    Cup(float px, float py, int size_)
    :Jugador(px, py, 15.0f, 20.0f, 0.0f, size_, 1, false), saltando(false),
    derecha(false), izquierda(false), enplataforma(false), vidas(3),
    salto(150)
    {
        disparo = new DisparoNormal();
    }
    Cup()
    {

    }
    void setDisparo(Disparo* disparo_);
    void disparar(const float& px, const float& py);
    virtual void mover(const float& px, const float& py) override;
    void moverIzquierda();
    void moverDerecha();
    void moverArriba();
    void moverAbajo();
    void saltar();
    void actualizar();
    void estaSaltando(bool t);
    void vaderecha(bool t);
    void vaizquierda(bool t);
    void estaquieto(bool t);
    void caida();
    void estaColisionando(const float& y);
    void enPlataforma(bool t);
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
#endif