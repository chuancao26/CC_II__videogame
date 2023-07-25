#include <SFML/Graphics.hpp>
#include <iostream>

class Background {
public:
    void cargar(sf::RenderWindow& window, int n){
        switch (n)
        {
        case 0:
            if (!texture_.loadFromFile("img\\menu\\menuInicio.png")) {
            std::cout<<"Error al cargar la imagen menuInicio.png"<<std::endl;
            }
            break;
        case 1:
            if (!texture_.loadFromFile("img\\menu\\fondoBee.png")) {
                std::cout<<"Error al cargar la imagen fondoBee2.png"<<std::endl;
            }
            break;
        case 2:
            if (!texture_.loadFromFile("img\\menu\\fondoFlor.png")) {
                std::cout<<"Error al cargar la imagen fondoFlor.png"<<std::endl;
            }
            break;
        case 3:
            if (!texture_.loadFromFile("img\\menu\\menuGano.png")) {
                std::cout<<"Error al cargar la imagen menuGano.png"<<std::endl;
            }
            break;
        case 4:
            if(!texture_.loadFromFile("img\\menu\\menuPerdio.png")) {
            std::cout<<"Error al cargar la imagen menuPerdio.png"<<std::endl;
            }
            break;
        }

        sprite_.setTexture(texture_);
        float scaleX = static_cast<float>(window.getSize().x) / sprite_.getLocalBounds().width;
        float scaleY = static_cast<float>(window.getSize().y) / sprite_.getLocalBounds().height;
        sprite_.setScale(scaleX, scaleY);
        gravedad_ = 50.0f;
        altura_ = sprite_.getLocalBounds().height;
    }

    void draw1(sf::RenderWindow& window) {
        sprite_.setPosition(sprite_.getPosition().x, 0);
        window.draw(sprite_);
    }

    void draw2(sf::RenderWindow& window)
    {
        float alturaVentana = static_cast<float>(window.getSize().y);

        // Obtener la posición actual y anterior del fondo
        float posYActual = sprite_.getPosition().y;
        float posYAnterior = posYActual - altura_;

        // Dibujar el fondo repetidamente para cubrir toda la pantalla
        float y = posYAnterior;
        while (y < alturaVentana) {
            sprite_.setPosition(sprite_.getPosition().x, y);
            window.draw(sprite_);
            y += altura_;
        }

        // Dibujar el fondo nuevamente en la posición actual
        sprite_.setPosition(sprite_.getPosition().x, posYActual);
        window.draw(sprite_);
    }

    void actualizar(sf::RenderWindow& window,float d)
    {
        float nuevaPosicion = sprite_.getPosition().y + gravedad_*d;// desplazamiento;

        if (nuevaPosicion >= altura_) {
            nuevaPosicion -= altura_;
        }

        sprite_.setPosition(sprite_.getPosition().x, nuevaPosicion);
    }

private:
    sf::Texture texture_;
    sf::Sprite sprite_;
    float gravedad_,altura_;
};