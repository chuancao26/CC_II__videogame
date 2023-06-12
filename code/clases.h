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
    void crearMapa();
};

class Mapa
{
private:
    Texture texture;
    Sprite sprite;

public:
    Mapa(const std::string& imagenFondo)
    void Mostrar()
};


class Cup
{
    private:
        float gravedad, speed, damage, tarjeta;
        int posx, posy, size, vidas;
        KeyBoard left, right, up, down, saltar, disparar, dash, cambiar_arma;
	friend class CupMuerto;
	friend class Tipos_disparo;
	friend class Plataforma;
    public:
        void move();
        void disparar();
        void colision();
        void textura();
        void posicion(); // Ubicar el mapa
        void saltar();
        void desaparecer();
	void invulnerable(); // si es_invulnerable=True
	void utilizarPlataforma();
};
class CupMuerto
{
    private:
        float gravedad, speed;
        int posx, posy, size;
	bool es_invulnerable;
    public:
        void move();
        void textura();
        void posicion(); // Ubicar el mapa
        // void volar(); creo que solo se está moviendo
	void revivir();  //se revive y el fantasma regresa al pool Cup cup1 cup.es_invulnerable=True;
	void colision(); //tocado por la tecla saltar de amigo, o si llega al borde superior de la ventana
};

class Bala
{
    private:
        float speed, damage, tarjeta, distancia;
        int posx, posy, size;
	KeyBoard D_left, D_right, D_up, D_down;
	bool activa;
    public:
    	Bala()
   	{
     	   activa = false;
    	}
	void activar();
	void desactivar();
    	bool EstaActiva(){
            return activa;
    	}
        void move();
        //void colision(); //SOLO con enemigos o desaparece
        void textura();
        void posicion();
        //void desaparecer(); si es con pool solo se regresa con "devolver bala"
};

class Tipos_disparo : Bala
{
private:
    int tipo;
public:
    void disparoLinea();
    void disparoCincoEnUno();
    void disparoBoomerang();
    void disparoPelota();
    void disparoRecargar();
    void disparoCercano();
    void disparoBoss();
    void disparoenemigo();
};

class Plataforma
{
    private:
        int posx, posy, ancho, alto;
    public:
	Plataforma(float x, float y, float w, float h) : posx(x), posy(y), ancho(w), alto(h) {}
	void interaccion_jugador();
	void interaccion_mounstro();
};
class Boss
{
    private:
        float gravedad, speed, damage, vida;
        int posx, posy, size;
	friend class Tipos_disparo;
	friend class Plataforma;
    public:
        void move();
        void disparar();
        void colision();
        void textura();
        void posicion();
        void saltar();
        void desaparecer();
	void utilizarPlataforma();
};
class Mounstro : Boss
{
    public:
        void move();
        void disparar();
        void colision();
        void textura();
        void posicion();
        void saltar();
        void desaparecer();
	void utilizarPlataforma();
};














