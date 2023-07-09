#include <SFML/Graphics.hpp>
#include "Jugador_Vista.cpp"
#include "Plataforma_Vista.cpp"
class Vista {
public:
    sf::RenderWindow window;
    vector<PlataformaVista*> plataformas;
    JugadorVista jugador_v;
    JugadorVista jugador_v2;
    float width,height;
    float elapsedSeconds;
    float interval;
    sf::Time tiempoAcumulado;
    sf::Clock relojMovimiento;
    sf::Clock clock;
    sf::Clock timer;
    
public:
    Vista(int xedge, int yedge) : width(xedge), height(yedge), window(sf::VideoMode(xedge, yedge), "CUPHEAD!")
    {
        width = window.getSize().x;
        height = window.getSize().y;
        elapsedSeconds = 0.0f;
        interval = 1.0f;
        tiempoAcumulado = sf::Time::Zero;
    }
    void cargarJugadores(int j1,int j2)
    {
        jugador_v.cargar(j1);
        jugador_v2.cargar(j2);
    }
    
    void dibujarCup(const Cup& jugador1,const Cup& jugador2) {
        //jugadorSprite.setPosition(jugador.getPosx(), jugador.getPosy());
        jugador_v.dibujar(jugador1,window);
        jugador_v2.dibujar(jugador2,window);
        
    }
    void dibujarPlat(const Plataforma& plataforma) {
       
        PlataformaVista* plat = new PlataformaVista(plataforma);
        plat->setPosition(plataforma.getPosx(), plataforma.getPosy());
        window.draw(plat->get());
        plataformas.push_back(plat);
    }
    void actualizar_Plataformas() {
        
    }
    
    bool colision(sf::Sprite& jugador, PlataformaVista* platform)
    {
        sf::FloatRect jugadorBounds = jugador.getGlobalBounds();
        sf::FloatRect plataformaBounds = platform->platformShape.getGlobalBounds();
        return jugadorBounds.intersects(plataformaBounds);
    }

    bool ventanaAbierta() {
        return window.isOpen();
    }

    void procesarEventos() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
        }
    }
};

