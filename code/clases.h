#include <SFML/Graphics.hpp>
#include <iostream>
class GameManager
{
    private:
        Cup* jugadores;
        Obstaculo* obstaculos;
        Monstruo* monstruo;
    void direcciones();
    void contarAvance();
    void cantVidas();
};
class Mapa
{

};



class Jugador
{
    private:
        float posx, posy, gravedad, speed;
        int size, vidas;
        KeyBoard left, right, up, down. disparar, desaparecer, ; 
    public:
        virtual void move();
        virtual void textura();
        virtual void revivir();
        virtual void posicion();
};
class Cup : public Jugador
{
    public:
        void move();
        void disparar();
        void colision();
        void textura();
        void revivir();
        void posicion(); // Ubicar el mapa 
        void saltar();
        void desaparecer();

};
class CupMuerto
{
    public:
        void move();
        void textura();
        void revivir();
        void posicion(); // Ubicar el mapa 
        void volar();

};
class Balas
{
    void superBala();
    void 
};


// Eventos
class Obstaculo
{

};
class Poderes
{

};
class Monstruo
{

};
class Boss
{

};
















