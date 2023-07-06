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
            if (!texture_.loadFromFile("img\\menu\\fondoFlor.png")) {
                std::cout<<"Error al cargar la imagen fondoFlor.png"<<std::endl;
            }
            break;
        case 2:
            if (!texture_.loadFromFile("img\\menu\\fondoBee.png")) {
                std::cout<<"Error al cargar la imagen fondoBee.png"<<std::endl;
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

        // Escala la imagen para que encaje con el tama�o de la ventana
        float scaleX = static_cast<float>(window.getSize().x) / sprite_.getLocalBounds().width;
        float scaleY = static_cast<float>(window.getSize().y) / sprite_.getLocalBounds().height;
        sprite_.setScale(scaleX, scaleY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite_);
    }

private:
    sf::Texture texture_;
    sf::Sprite sprite_;
};