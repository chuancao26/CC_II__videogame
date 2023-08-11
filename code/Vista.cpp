#include <SFML/Graphics.hpp>
#include "Jugador_Vista.cpp"
#include "Plataforma_Vista.cpp"
#include "Background_Vista.cpp"
#include "Elegir.cpp"
#include "BalaNormal_Vista.cpp"
#include "BalaBomba_Vista.cpp"
#include "BalaEstrella_Vista.cpp"
#include "eventosflor.h"
#include <thread>
#include <memory>
#include "vistaBee.h"
#include <iostream>
using FloatPtr = std::shared_ptr<float>;
class Vista {
public:
    sf::RenderWindow window;
    JugadorVista jugador_v;
    JugadorVista jugador_v2;
    float width,height;
    sf::Time tiempoAcumulado;
    VistaBee vistaBee;
    VistaFlor vistaFlor;
    ElegirPlayer elegir;
    Background background; 
    sf::Clock clock, gameTime, clock5, clockLevel2, clockLevel1;
    sf::Sprite buttonMenu;
    sf::Texture textura,textura2;
    sf::Sprite buttonSiguiente;
    sf::Text time;
    sf::Font font;
    bool level2, level3;

    
public:
    Vista(const int& xedge, const int& yedge) : width(xedge), height(yedge), window(sf::VideoMode(xedge, yedge), "CUPHEAD!")
    , vistaBee(window), vistaFlor(window)
    {
        if (!font.loadFromFile("font/MadnessHyperactive.otf")) 
        {
            std::cout << "error" << std::endl; 
        }
        time.setFont(font);
        time.setCharacterSize(64);
        time.setFillColor(sf::Color::White);
        time.setPosition(1280 / 2 - 64, 5); // Posición en la parte inferior izquierda

        width = window.getSize().x;
        height = window.getSize().y;  
        tiempoAcumulado = sf::Time::Zero;
        if (!textura.loadFromFile("img/menu/botonMenu.png")) {
                cout << "Error al cargar la imagen botonMenu.png" <<endl;
            }
        buttonMenu.setTexture(textura);
        if (!textura2.loadFromFile("img/menu/botonSiguiente.png")) {
                cout << "Error al cargar la imagen botonSiguiente.png" <<endl;
            }
        buttonSiguiente.setTexture(textura2);
    }
    void drawTimeBee()
    {
        if (!level2)
        {
            clockLevel1.restart();
            level2 = true;
        }
        if (level2)
        {
            sf::Time elapsedTime = clockLevel1.getElapsedTime();
            int seconds = elapsedTime.asSeconds();
            int minutes = seconds / 60;
            seconds %= 60;
            time.setString(std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
            window.draw(time);
        }   
    }
    void restartClock1()
    {
        clockLevel1.restart();
    }
    void restartClock2()
    {
        clockLevel2.restart();
    }
    void drawTimeFlower()
    {
        if (!level3)
        {
            clockLevel2.restart();
            level3 = true;
        }
        if (level2)
        {
            sf::Time elapsedTime = clockLevel2.getElapsedTime();
            int seconds = elapsedTime.asSeconds();
            int minutes = seconds / 60;
            seconds %= 60;
            time.setString(std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
            window.draw(time);
        } 
    }
    float getGameTime()
    {
        return gameTime.getElapsedTime().asSeconds();
    }
    void cargarJugadores(int j1,int j2)
    {
        if(j1!=0 && j2!=0)
        {
            jugador_v.cargar(j1);
            jugador_v2.cargar(j2); 
        }
        
    }
    void dibujarCup(const Cup& jugador1,const Cup& jugador2) {
        jugador_v.dibujar(jugador1,window);
        jugador_v2.dibujar(jugador2,window);
    }

    void dibujarPlat(const Plataforma& plataforma) {
       
        PlataformaVista plat(plataforma);
        plat.setPosition(plataforma.getPosx(), plataforma.getPosy());
        window.draw(plat.get());
    }

    void dibujarBalasNormales( BalaNormal& bala) {
       
       BalaNormalVista bal(bala);
       bal.setPosition(bala.getPosx(), bala.getPosy());
       window.draw(bal.getSprite());
    }

    void dibujarBalasBombas(BalaBomba& bala) {
       
       BalaBombaVista bal(bala);
       bal.setPosition(bala.getPosx(), bala.getPosy());
       window.draw(bal.get());
    }
    void dibujarBalasEstrellas(BalaEstrella& bala) {
       
       BalaEstrellaVista bal(bala);
       bal.setPosition(bala.getPosx(), bala.getPosy());
       window.draw(bal.get());
    }

    void dibujarBotones(int n)
    {   
        buttonMenu.setPosition(1177,620);
        buttonSiguiente.setPosition(1228,620);
        window.draw(buttonMenu);
        if(n==1)
        {
            window.draw(buttonSiguiente);
        }
    }

    void actualizar_Plataformas() {
        
    }
    void loadBeeView(Cup& player1,Cup& player2)
    {
        vistaBee.handleInput(player1,player2, clockLevel1.getElapsedTime().asSeconds(), jugador_v.cupShape, jugador_v2.cupShape);
        vistaBee.render();
    }
    bool colisiones1Bee(Cup& player1)
    {
        return vistaBee.colisionesPlayer1Bee(player1);
    }
    bool colisiones2Bee(Cup& player1)
    {
        return vistaBee.colisionesPlayer2Bee(player1);
    }
    void loadFlorView(sf::RenderWindow& win,Cup& player1, Cup& player2)
    {
        vistaFlor.handleInput(win,player1,player2,jugador_v.cupShape, jugador_v2.cupShape);
        vistaFlor.render(win);
    }
    
    bool colision(sf::Sprite& jugador, Plataforma& platform)
    {
        sf::FloatRect jugadorBounds = jugador.getGlobalBounds();
        sf::FloatRect plataformaBounds(platform.x, platform.y, platform.width,platform.height);
        return jugadorBounds.intersects(plataformaBounds);
    }

    bool ventanaAbierta() {
        return window.isOpen();
    }

    int procesarEventosPlayer1() {
        sf::Event event;
        if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    return 1;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    return 2;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    return 3;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    return 4;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    return 5;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                    return 6;
                }
                
                else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
                    return 12;
                }
                else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    return 13;
                }
                
            
        
        return 0;
    }
    int procesarEventosPlayer2() {
        sf::Event event;
        if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    return 7;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    return 8;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    return 9;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    return 10;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    return 11;
                }
            
                else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    return 14;
                }
                else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    return 15;
                }
    
        return 0;
    }
    
    int procesarEventosMouse(std::vector<FloatPtr>& Posicion) {
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos(mousePosition.x, mousePosition.y);
                    Posicion.push_back(std::make_shared<float>(mousePosition.x));
                    Posicion.push_back(std::make_shared<float>(mousePosition.y));
                    return 16;
                }
            }
        }
        return 0;
    }
    sf::RenderWindow& getWindow()
    {
        return window;
    }
    void eliminarplataformas(Mapa*& map)
    {
        if (clock5.getElapsedTime().asSeconds() >= 2.5f)
        {
            map->eliminarPlataformas();
            clock5.restart();
        }
    }
};

