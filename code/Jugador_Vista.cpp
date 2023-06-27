#include <SFML/Graphics.hpp>
#include "Jugador_Modelo.cpp"
#include "Plataforma_Modelo.cpp"
#include "Plataforma_Vista.cpp"

class JugadorVista {
public:
    sf::RenderWindow& window;
    //sf::RectangleShape cupShape;
    vector<PlataformaVista> plataformas;
    sf::View vista;
    sf::Texture texture1;
    sf::Sprite cupShape;
    float width, height;
    
public:
    JugadorVista(sf::RenderWindow& window)
        : window(window) {
        width=window.getSize().x;
        height=window.getSize().y;
        //cupShape.setSize(sf::Vector2f(40.f, 40.f));
        //cupShape.setFillColor(sf::Color::Red);
        if (!texture1.loadFromFile("img\\jugador.png")) {
            cout << "Error al cargar la imagen jugador.png" <<endl;
        }
        cupShape.setTexture(texture1);
        cupShape.setScale(60.f/cupShape.getLocalBounds().width, 60.f/cupShape.getLocalBounds().height);
        vista.setSize(window.getSize().x, window.getSize().y);
        vista.setCenter((window.getSize().x)/2, (window.getSize().y)/2);
        window.setView(vista);
    }
    
    void dibujar(const Cup& jugador) {
        //jugadorSprite.setPosition(jugador.getPosx(), jugador.getPosy());
        cupShape.setPosition(jugador.getPosx(), jugador.getPosy()-jugador.getSize());
        window.draw(cupShape);
    }
    void dibujarPlat(const Plataforma& plataforma) {
        //jugadorSprite.setPosition(jugador.getPosx(), jugador.getPosy());
        PlataformaVista plat(plataforma);
        plat.setPosition(plataforma.getPosx(), plataforma.getPosy());
        window.draw(plat.get());
        plataformas.push_back(plat);
    }
    void actualizar(Cup& jugador) {
        if (jugador.getPosy() < 100) {
            vista.move(0, jugador.getPosy() - 500);
            vista.setCenter((window.getSize().x)/2, (jugador.getPosy() - 500)/2);
            window.setView(vista);
        }
    }
    bool colision(sf::Sprite& jugador,const PlataformaVista& platform)
    {
        sf::FloatRect jugadorBounds = jugador.getGlobalBounds();
        sf::FloatRect plataformaBounds = platform.getGlobalBounds();

        return jugadorBounds.intersects(plataformaBounds);
        /*if(jugador.getPosy()>=platform.pla.getPosy() || jugador.getPosy()+jugador.getSize()<= platform.pla.getPosy()+platform.pla.height)
        {
            return true;
        }
        
        return false;*/
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

