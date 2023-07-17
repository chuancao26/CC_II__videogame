#include <SFML/Graphics.hpp>
#include <cmath>

class Seed {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f direction;
    bool canBeDeleted;
    float ang;

public:
    Seed(float x, float y) : canBeDeleted(false) {
        if (!texture.loadFromFile("seed.png")) {
            // Manejo de error si no se puede cargar la textura
        }

        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        position = sf::Vector2f(x, y);
        sprite.setPosition(position);
        ang=0.f;
    }

    void update() {
        float co = direction.y - position.y;
        float ca = direction.x - position.x;

        float speedX, speedY;

        if (co == 0.f) {
            speedX = 4.f;
            speedY = 0.f;
            ang=0;
        } else {
            float h = std::sqrt(ca * ca + co * co);
            float k1 = ca / h;
            float k2 = co / h;

            speedX = k1;
            speedY = k2;
            ang=std::atan2(-speedY, -speedX) * 180.f / M_PI;
        }

        position.x += speedX;
        position.y += speedY;

        sprite.setPosition(position);

        if (position.x >= sf::VideoMode::getDesktopMode().width) {
            canBeDeleted = true;
        }
    }

    bool canDelete() const {
        return canBeDeleted;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        sprite.setRotation(ang);

    }
    void setDestino(float a, float b){
        direction = sf::Vector2f(a, b);
    }
};
int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Seeds");

    Seed seed1(window.getSize().x * 2.f / 3.f, window.getSize().y * 2.f / 6.f);
    seed1.setDestino(0,500);
    Seed seed2(window.getSize().x * 2.f / 3.f, window.getSize().y * 3.f / 6.f);
    Seed seed3(window.getSize().x * 2.f / 3.f, window.getSize().y * 4.f / 6.f);
    Seed* seeds[3] = {&seed1, &seed2, &seed3};
   

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        for (int i = 0; i < 3; ++i) {
            seeds[i]->update();
        }

        window.clear();

        for (int i = 0; i < 3; ++i) {
            seeds[i]->draw(window);
        }
        
        window.display();

        if (seed1.canDelete() && seed2.canDelete() && seed3.canDelete()) {
            // Todos los objetos se pueden eliminar, se sale del bucle
            break;
        }
    }

    return 0;
}
