#include <SFML/Graphics.hpp>
#include "Jugador_Modelo.cpp"
#include "Plataforma_Vista.cpp"

class JugadorVista {
public:
    std::vector<sf::Texture> salto;
    std::vector<sf::Texture> derecha;
    std::vector<sf::Texture> izquierda;
    std::vector<sf::Texture> abajo;
    std::vector<sf::Texture> quieto;
    std::vector<sf::Texture> disparar;
    sf::Sprite cupShape;
    string jugador;
    int indiceAnimacion = 0;
    sf::Clock reloj;
    
public:
    JugadorVista(){}
    void cargar(int n)
    {
        switch (n)
        {
        case 1:
            jugador="cup1";
            break;
        case 2:
            jugador="cup2";
            break;
        case 3:
            jugador="cup3";
            break;
        default:
            break;
        }
        for(int i=1;i<5;i++)
        {
            sf::Texture textura;
            if (!textura.loadFromFile("img/cup/"+jugador+"/salto"+std::to_string(i)+".png")) {
                cout << "Error al cargar la imagen salto.png" <<endl;
            }
            salto.push_back(textura);
        }
        for(int j=1;j<5;j++)
        {
            sf::Texture textura;
            if (!textura.loadFromFile("img/cup/"+jugador+"/derecha"+std::to_string(j)+".png")) {
                cout << "Error al cargar la imagen salto.png" <<endl;
            }
            derecha.push_back(textura);
        }
        for(int k=1;k<5;k++)
        {
            sf::Texture textura;
            if (!textura.loadFromFile("img/cup/"+jugador+"/izquierda"+std::to_string(k)+".png")) {
                cout << "Error al cargar la imagen salto.png" <<endl;
            }
            izquierda.push_back(textura);
        }/*
        for(int l=1;l<5;l++)
        {
            sf::Texture textura;
            if (!textura.loadFromFile("img/cup/"+jugador+"/abajo"+std::to_string(l)+".png")) {
                cout << "Error al cargar la imagen salto.png" <<endl;
            }
            abajo.push_back(textura);
        }
        for(int m=1;m<5;m++)
        {
            sf::Texture textura;
            if (!textura.loadFromFile("img/cup/"+jugador+"/disparar"+std::to_string(m)+".png")) {
                cout << "Error al cargar la imagen salto.png" <<endl;
            }
            disparar.push_back(textura);
        }*/
        for(int n=1;n<5;n++)
        {
            sf::Texture textura;
            if (!textura.loadFromFile("img/cup/"+jugador+"/quieto"+std::to_string(n)+".png")) {
                cout << "Error al cargar la imagen quieto.png" <<endl;
            }
            quieto.push_back(textura);
        }
        
    }
    
    void dibujar(const Cup& jugador,sf::RenderWindow& window) {
        float tiempoPorFrame = 0.2f; // Tiempo entre cada frame de la animación
        if (reloj.getElapsedTime().asSeconds() >= tiempoPorFrame) {
            indiceAnimacion = (indiceAnimacion + 1) % salto.size();
            reloj.restart();
        }

        // Dibujar sprite utilizando la textura actual
        if(jugador.saltando)
        {
            cupShape.setTexture(salto[indiceAnimacion]);
        }
        else if(jugador.derecha)
        {
            cupShape.setTexture(derecha[indiceAnimacion]);
        }
        else if(jugador.izquierda)
        {
            cupShape.setTexture(izquierda[indiceAnimacion]);
        }
        else if(!jugador.derecha && !jugador.izquierda)
        {
            cupShape.setTexture(quieto[indiceAnimacion]);
        }
        cupShape.setPosition(jugador.getPosx(), jugador.getPosy()-jugador.getSize());
        cupShape.setScale(80.f/cupShape.getLocalBounds().width, 80.f/cupShape.getLocalBounds().height);
        window.draw(cupShape);
    }
    void actualizar(Cup& jugador) {

    }
};

