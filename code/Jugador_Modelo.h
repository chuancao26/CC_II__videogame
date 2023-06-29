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
        float getPosx() const;
        float getPosy() const;
        int getSize() const;
        virtual void mover(const float& px, const float& py)=0;
};
class Cup: public Jugador {
public:
    bool saltando,enplataforma;
    float salto;
    int currentJumps, jumps, vidas;
public:
    Cup(const int &px, const int& py, const int& size_);
    virtual void mover(const float& px, const float& py) override;
    void moverIzquierda();
    void moverDerecha();
    void moverArriba();
    void moverAbajo();
    void saltar();
    void actualizar();
    void estaSaltando(bool t);
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