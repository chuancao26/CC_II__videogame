#include <SFML/Graphics.hpp>
#include "Jugador_Vista.cpp"
#include "Plataforma_Vista.cpp"
class Vista {
public:
    sf::RenderWindow window;
    vector<PlataformaVista> plataformas;
    JugadorVista jugador_v;
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
    
    void dibujarCup(const Cup& jugador) {
        //jugadorSprite.setPosition(jugador.getPosx(), jugador.getPosy());
        jugador_v.dibujar(jugador,window);
    }
    void dibujarPlat(const Plataforma& plataforma) {
        //jugadorSprite.setPosition(jugador.getPosx(), jugador.getPosy());
        PlataformaVista plat(plataforma);
        plat.setPosition(plataforma.getPosx(), plataforma.getPosy());
        window.draw(plat.get());
        plataformas.push_back(plat);
    }
    void actualizar_Plataformas() {
        
    }
    
    bool colision(sf::Sprite& jugador,const PlataformaVista& platform)
    {
        sf::FloatRect jugadorBounds = jugador.getGlobalBounds();
        sf::FloatRect plataformaBounds = platform.platformShape.getGlobalBounds();
        return jugadorBounds.intersects(plataformaBounds);
    }

    void actualizarPlataformasVistas(vector<Plataforma> plataformas_) {
        for (auto plat : plataformas_) {
            plat.caida();
        }
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

