#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;
using namespace sf;
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
    Texture* mapas;
    float velocidad;
    int largex, largey;
    Sprite sprite;
    string pathImage;

public:
    Mapa(const string& pathImagenFondo, const float& velocidad_);
    void Mostrar();
    void getPosicionX(); // captura la posicion que va en x
    void actualizar(); // de acuerdo a como se muevan los jugadores se actualizara la pos en x 
    void draw(); // Dibujar el objeto en el while del Game Manager
    void setVelocidad(const float& velocidad_); // Cambiar la velocidad a la que se movera en el mapa
    void reiniciar(); // Reiniciar el mapa a su posición inicial
    void detener(); // Parar el movimiento en el mapa
    void setPosicionInicial(); // Manejar la posicion inicial en el mapa 
    void moverIzquierda(float deltaTiempo); // Mover el mapa hacia la izquierda
    void moverDerecha(float deltaTiempo); // Mover el mapa hacia la derecha
    void cambiarMapa(const string& pathImageFondo);
};
class Plataforma
{
    private:
        float posx, posy, speed = 0.1, salto = 1, gravedad = 0.1;
        float ancho, alto;
        Color color;
        RectangleShape plataforma; 
        int xedge, yedge;
    public:
	Plataforma(float x, float y, float w, float h) : posx(x), posy(y), ancho(w), alto(h) {}
	void interaccion_jugador();
	void interaccion_mounstro();
    void draw();
    void 


};



