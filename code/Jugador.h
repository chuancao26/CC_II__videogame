#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Jugador
{
    private:
        float gravedad, speed;
        int posx, posy, size;
    public:
        //clase abstracta
        virtual void mover()=0;
        virtual void textura()=0;
        virtual void colision()=0;
};
class Cup : public Jugador
{
    private:
        float damage, tarjeta;
        int posx, posy, size, vidas;
        Keyboard::Key left, right, up, down, saltar, apuntar, disparar, dash, cambiar_arma;
        vector<Poderes>  poderes;
        friend class CupMuerto;
        friend class Tipos_disparo;
        friend class Plataforma;
    public:
        virtual void mover() override;
        void controlarTeclas();//donde se implemetará las acciones de las teclas
        void disparar(); //dispara balas
        virtual void colision() override; //se implementará los diferentes tipos de colision
        void posicion(); // Ubicar el mapa
        void saltar(); //el jugador salta al presionar una tecla
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
class Poderes
{
    public:
        string Nombre;
        int costo;
}