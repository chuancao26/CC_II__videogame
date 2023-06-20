#ifndef JUGADOR_H
#define JUGADOR_H
#include "Poderes.h"
#include "Plataforma.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Jugador
{
    public:
        float posx, posy, gravedad, speed;
        Color color;
        RectangleShape cup; 
        int size,xedge, yedge;
    public:
    
        //clase abstracta
        //virtual void mover()=0;
        //virtual void textura()=0;
        //virtual void colision()=0;
};
class Cup : public Jugador
{
    public:
        float gravedad=0.1, speed=0.1, salto = 1;
        int currentJumps, jumps = 2, vidas;
        sf::FloatRect previousPosition;
        //vector<Poderes>  poderes;
        friend class CupMuerto;
        friend class Tipos_disparo;
        friend class Plataforma;
    public:
        Cup(const int &px, const int& py, const int& size_, const Color& a, const int& limitx, const int& limity);
        void mover(const int& px, const int& py);
        sf::FloatRect getGlobalBounds() const;
        void controlarMovimiento(const bool& xclickRight, const bool& xclickLeft, const bool& yclickDown);//donde se implemetará las acciones de las teclas
        void disparar(); //dispara balas
        void dibujar(RenderWindow& a);
        bool isColliding(const Platform& platform);
        void colision(); //se implementará los diferentes tipos de colision
        void posicion(); // Ubicar el mapa
        void saltar(const bool& yclickUp); //el jugador salta al presionar una tecla
        void caida();//el cup esta cayendo
        float getPosx();
        float getPosy();
        void fijar();// se queda inmovil para poder disparar en 8 direcciones
        void agacharse(); //se agacha para esquivar balas
        void desaparecer(); //el jugador se teletransporte
        void invulnerable(); // si es_invulnerable=True
        void utilizarPlataforma(); //moverse en la plataforma
        void recogerMonedas();// recogera las monedas y se sumara a su puntaje
        void activarPoder();// activa un poder adquirido
        void desactivarPoder();// desactiva un poder que este activo
};
class CupMuerto : public Jugador
{
    private:
        bool es_invulnerable;
    public:
        void mover();
        void posicion(); // Ubicar el mapa
        // void volar(); creo que solo se esta moviendo
        void revivir();  //se revive y el fantasma regresa al pool Cup cup1 cup.es_invulnerable=True;
        void colision(); //tocado por la tecla saltar de amigo, o si llega al borde superior de la ventana
};
#endif