#include <SFML/Graphics.hpp>
#include <iostream>
class GameManager
{
    private:
        Cup* jugadores;
        Obstaculo* obstaculos;
        Monstruo* monstruos;
        Mapa* mapa;
        int limitx, limity; /// Limites de la pantalla en x e y 
        string windowName;

    public: 
        GameManager(const int& limitx_, const int& limity_, const string& windowName_); // Constructor
        void draw(); // Metodo en donde se mostraran los objetos que apareceran en el mapa
        void crearWindow(); // Metodo para setear la pantalla de juego
        void setup(); // Configurar 
        void run(); // Comenzar a dibujar si es que la window esta abierta 
        void eventos(); // Manejar todos los eventos que los jugadores hagan
        void update(); // Actualizar la logica del videojuego
        void teclasDirecciones(); // Evento teclas de direccion
        void teclasEspeciales(); // evento teclas de disparo, slash
        
        // Manejar la estadistica del juego
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
    Mapa(const string& imagenFondo)
    void Mostrar()
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



