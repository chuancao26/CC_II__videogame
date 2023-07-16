#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <random>

class ThornsRoot {
private:
    sf::RenderWindow& window;
    sf::Texture finalTexture1;
    sf::Texture finalTexture2;
    sf::Texture finalTexture3;
    sf::Texture finalTexture4;
    sf::Texture finalTexture;
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sf::Sprite spritefinal;
    sf::Texture raizEnganchadaTexture; // Debes proporcionar este archivo de imagen
    sf::Texture raizEnganchadaTexture2;
    sf::RectangleShape raiz;
    std::shared_ptr<float> randomValues[2];

public:
    ThornsRoot(sf::RenderWindow& window) : window(window) {
        if (!finalTexture1.loadFromFile("final1.png") || !finalTexture2.loadFromFile("final2.png") ||
            !finalTexture3.loadFromFile("final3.png") || !finalTexture4.loadFromFile("final4.png") || !raizEnganchadaTexture2.loadFromFile("espina.png") || 
            !raizEnganchadaTexture.loadFromFile("enganchar.png")|| !finalTexture.loadFromFile("final.png") ) {
            std::cerr << "Error al cargar las texturas." << std::endl;
        }
        
        raiz.setSize(sf::Vector2f(window.getSize().x * 3 / 4, window.getSize().y / 3));
        raiz.setPosition(sf::Vector2f(window.getSize().x /4, window.getSize().y * 2 / 3));
        raiz.setFillColor(sf::Color::Transparent);
        
        loadRandomValues();
    }

    void run() {
        sf::Clock clock;
        sf::Clock clock1;
        
        while (window.isOpen()) {
            sf::Time elapsed = clock.getElapsedTime();
            sf::Time elapsed1 = clock1.getElapsedTime();

            handleEvents();
            
            if (elapsed1.asSeconds() <= 2.f) {
                if (elapsed1.asSeconds() < 0.5f) {
                    drawImage(finalTexture1);
                } else if (elapsed1.asSeconds() < 1.f){
                    drawImage(finalTexture2);
                }
                else if (elapsed1.asSeconds() < 1.5f){
                    drawImage(finalTexture3);
                }
                else{
                    drawImage(finalTexture4);
                    
                }
            
            } else {
                drawImage2(finalTexture);
                
                if ((elapsed.asSeconds() <= 6.f)&&(elapsed.asSeconds() > 2.f)) {
                    float deltaTime = elapsed.asSeconds() - 3.f;
                    float rectX = window.getSize().x - (window.getSize().x * 1 / 4) * (deltaTime / 3.f);
                    raiz.setPosition(sf::Vector2f(rectX, window.getSize().y * 2 / 3));
                    //draw();
                } else if (elapsed.asSeconds() <= 7.f) {
                    //drawRectangles(sf::Color::Green, sf::Color::Magenta);
                    drawRaiz(raizEnganchadaTexture,true);
                } else if (elapsed.asSeconds() <= 10.f) {
                    drawRaiz(raizEnganchadaTexture2,false);
                } else if (elapsed.asSeconds() <= 12.f) {
                    //drawRectangles(sf::Color::Yellow, sf::Color::Blue);
                    drawRaiz(raizEnganchadaTexture,true);
                } else {
                    //reset();
                    //drawImage2(finalTexture);
                    loadRandomValues();
                    clock.restart();
                }
            }

        }
    }
    
    
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void drawImage(const sf::Texture& texture) {
        sf::Sprite sprite(texture);
        
         sprite.setPosition(window.getSize().x - (sprite.getLocalBounds().width)/1.1,
                                 window.getSize().y / 12);
        window.clear();                         
        window.draw(sprite);
        window.display();
    }
    void drawImage2(const sf::Texture& texture) {
        sf::Sprite sprite(texture);
        window.clear();
         sprite.setPosition(window.getSize().x - (sprite.getLocalBounds().width)/1.1,
                                 window.getSize().y / 12);
        window.draw(sprite);
        window.display();
    }

    void drawRaiz(const sf::Texture& texture, bool f) {
        sf::Sprite sprite(texture);
        sf::Sprite sprite2(texture);
        float rectX1 = *(randomValues[0]);
        float rectX2 = *(randomValues[1]);
        float rectY = window.getSize().y * 3 / 5;
        if (f==false){
            rectY = window.getSize().y * 1 / 5;
        }        
        
        sprite.setPosition(sf::Vector2f(rectX1, rectY));
        sprite2.setPosition(sf::Vector2f(rectX2, rectY));

        window.draw(sprite);
        window.draw(sprite2);
        window.display();
    }
    
    void drawRectangles(const sf::Color& color1, const sf::Color& color2) {
        float rectX1 = *(randomValues[0]);
        float rectX2 = *(randomValues[1]);
        float rectY = window.getSize().y * 2 / 3;
        
        sf::RectangleShape rect1(sf::Vector2f(50.f, 50.f));
        rect1.setPosition(sf::Vector2f(rectX1, rectY));
        rect1.setFillColor(color1);
        
        sf::RectangleShape rect2(sf::Vector2f(50.f, 50.f));
        rect2.setPosition(sf::Vector2f(rectX2, rectY));
        rect2.setFillColor(color2);
        
        draw();
        window.draw(rect1);
        window.draw(rect2);
        window.display();
        
        sf::sleep(sf::seconds(2.f));
    }
    
    void loadRandomValues() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 3);
        
        randomValues[0] = std::make_shared<float>(window.getSize().x / 6);
        
        int value = dist(gen);
        if (value == 1) {
            randomValues[1] = std::make_shared<float>(window.getSize().x / 6);
        } else if (value == 2) {
            randomValues[1] = std::make_shared<float>(window.getSize().x * 2 / 6);
        } else {
            randomValues[1] = std::make_shared<float>(window.getSize().x * 3 / 6);
        }
    }
    
    void draw() {
        window.clear();
        window.draw(raiz);
        window.display();
    }
    
    void reset() {
        window.clear();
        window.display();
        raiz.setSize(sf::Vector2f(window.getSize().x * 3 / 4, window.getSize().y / 3));
        raiz.setPosition(sf::Vector2f(0, window.getSize().y * 2 / 3));
        raiz.setFillColor(sf::Color::Transparent);
    }

};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ThornsRoot");
    
    ThornsRoot game(window);
    game.run();
    
    return 0;
}