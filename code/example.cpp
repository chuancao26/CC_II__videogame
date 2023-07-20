#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <random>


class SeedModel {
private:
    sf::Vector2f position;
    sf::Vector2f direction;
    bool canBeDeleted;
    float ang;

public:
    SeedModel(float x, float y) : canBeDeleted(false) {
        position = sf::Vector2f(x, y);
        ang = 0.f;
    }

    void update() {
        float co = direction.y - position.y;
        float ca = direction.x - position.x;

        float speedX, speedY;

        if (co == 0.f) {
            speedX = 4.f;
            speedY = 0.f;
            ang = 0;
        } else {
            float h = std::sqrt(ca * ca + co * co);
            float k1 = ca / h;
            float k2 = co / h;

            speedX = k1;
            speedY = k2;
            ang = std::atan2(-speedY, -speedX) * 180.f / M_PI;
        }

        position.x += speedX;
        position.y += speedY;

        if (position.x <= 0) {
            canBeDeleted = true;
        }
    }

    bool canDelete() const {
        return canBeDeleted;
    }

    const sf::Vector2f& getPosition() const {
        return position;
    }

    float getAngle() const {
        return ang;
    }

    void setDestino(float a, float b) {
        direction = sf::Vector2f(a, b);
    }
};


class SeedView {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    SeedView(const sf::Vector2f& position) {
        if (!texture.loadFromFile("seed.png")) {
            // Manejo de error si no se puede cargar la textura
        }

        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(position);
    }

    void updatePosition(const sf::Vector2f& position) {
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window, float angle) {
        sprite.setRotation(angle);
        window.draw(sprite);
    }
};

class SeedController {
private:
    SeedModel model;
    SeedView view;

public:
    SeedController(float x, float y) : model(x, y), view(model.getPosition()) {}

    void setDestino(float a, float b) {
        model.setDestino(a, b);
    }

    void update() {
        model.update();
        view.updatePosition(model.getPosition());
    }

    bool canDelete() const {
        return model.canDelete();
    }

    void draw(sf::RenderWindow& window) {
        if (!model.canDelete()){
            view.draw(window, model.getAngle());
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Seeds");

    SeedController seed1(window.getSize().x * 2.f / 3.f, window.getSize().y * 2.f / 6.f);
    seed1.setDestino(0, 500);
    SeedController seed2(window.getSize().x * 2.f / 3.f, window.getSize().y * 3.f / 6.f);
    SeedController seed3(window.getSize().x * 2.f / 3.f, window.getSize().y * 4.f / 6.f);
    SeedController* seeds[3] = {&seed1, &seed2, &seed3};

    sf::Clock clockSeed;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clockSeed.restart();

        for (int i = 0; i < 3; ++i) {
            seeds[i]->update();
        }

        window.clear();

        for (int i = 0; i < 3; ++i) {
            //seeds[i]->draw(window);
           if (!seeds[i]->canDelete()){
            seeds[i]->draw(window);
           }
        }

        window.display();

    }


    return 0;
}
