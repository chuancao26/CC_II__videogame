#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string>

class AtaqueCabeza
{
private:
    sf::RenderWindow& window_;
    sf::Texture caraTexture_;
    sf::Sprite caraSprite_;
    sf::Texture cuelloTexture_;
    sf::Sprite cuelloSprite_;
    sf::Textu
    re inicioCabezaTexture_;
    sf::Sprite inicioCabezaSprite_;
    float originalWidth_;
    float originalHeight_;
    float greenRectX_;
    float greenRectY_;
    float purpleRectY_;
    float velocity_;
    sf::Clock clock_;
    sf::Time elapsedTime_;
    int state_;

public:
    AtaqueCabeza(sf::RenderWindow& window)
        : window_(window),
          originalWidth_(window_.getSize().x / 3),
          originalHeight_(window_.getSize().y / 4),
          greenRectX_(window_.getSize().x - (originalWidth_ / 1.1f)),
          greenRectY_(window_.getSize().y / 2),
          purpleRectY_(window_.getSize().y / 2),
          velocity_(0.2),
          elapsedTime_(sf::Time::Zero),
          state_(1)
    {
        caraTexture_.loadFromFile("cara.png");
        caraSprite_.setTexture(caraTexture_);
        caraSprite_.setScale(sf::Vector2f(originalWidth_ / caraTexture_.getSize().x, originalHeight_ / caraTexture_.getSize().y));
        caraSprite_.setPosition(greenRectX_, purpleRectY_);

        cuelloTexture_.loadFromFile("cuello.png");
        cuelloSprite_.setTexture(cuelloTexture_);
        cuelloSprite_.setPosition(greenRectX_, purpleRectY_);
        cuelloSprite_.setScale(sf::Vector2f(originalWidth_ / cuelloTexture_.getSize().x, originalHeight_ / cuelloTexture_.getSize().y));

        inicioCabezaTexture_.loadFromFile("inicioCabeza.png");
        inicioCabezaSprite_.setTexture(inicioCabezaTexture_);
        inicioCabezaSprite_.setScale(sf::Vector2f(originalWidth_ / inicioCabezaTexture_.getSize().x, originalHeight_ / inicioCabezaTexture_.getSize().y));
        inicioCabezaSprite_.setPosition(greenRectX_, greenRectY_);
    }

    void update()
    {
        elapsedTime_ = clock_.getElapsedTime();

        switch (state_)
        {
            case 1:
                if (elapsedTime_.asSeconds() < 2)
                {
                    cuelloSprite_.setPosition(window_.getSize().x*2, window_.getSize().y);
                    caraSprite_.setPosition(window_.getSize().x*2, window_.getSize().y);
                    inicioCabezaSprite_.setPosition(greenRectX_, greenRectY_);
                }

                else if (elapsedTime_.asSeconds() > 2 && greenRectX_ > 0)
                {
                    inicioCabezaSprite_.setPosition(window_.getSize().x, greenRectY_);
                    greenRectX_ -= velocity_;
                    //inicioCabezaSprite_.setPosition(greenRectX_, greenRectY_);
                    caraSprite_.setPosition(greenRectX_, greenRectY_);

                    float cuelloSpriteWidth = window_.getSize().x + (originalWidth_) + greenRectX_;
                    cuelloSprite_.setScale(sf::Vector2f(cuelloSpriteWidth / cuelloTexture_.getSize().x, originalHeight_ / cuelloTexture_.getSize().y));
                    cuelloSprite_.setPosition(greenRectX_, purpleRectY_);

                }
                else if (greenRectX_ <= 0 && elapsedTime_.asSeconds() > 4)
                {
                    //inicioCabezaSprite_.setScale(sf::Vector2f(0.0f, 0.0f));
                    elapsedTime_ = sf::Time::Zero;
                    state_ = 2;
                }

                break;

            case 2:
                //inicioCabezaSprite_.setScale(sf::Vector2f(0.0f, 0.0f));
                if (elapsedTime_.asSeconds() > 4 && elapsedTime_.asSeconds() < 8)
                {
                    if (greenRectX_ <= window_.getSize().x - (originalWidth_))
                    {
                        greenRectX_ += velocity_;
                        float cuelloSpriteWidth = window_.getSize().x + (originalWidth_) + greenRectX_;
                        cuelloSprite_.setScale(sf::Vector2f(cuelloSpriteWidth / cuelloTexture_.getSize().x, originalHeight_ / cuelloTexture_.getSize().y));
                        cuelloSprite_.setPosition(greenRectX_, purpleRectY_);
                    }
                    caraSprite_.setPosition(greenRectX_, greenRectY_);
                }
                else
                {
                    state_ = 3;
                }
                break;

            case 3:
                caraSprite_.setScale(sf::Vector2f(0.0f, 0.0f));
                cuelloSprite_.setScale(sf::Vector2f(0.0f, 0.0f));
                break;

            default:
                break;
        }
    }

    void draw()
    {
        window_.draw(cuelloSprite_);
        window_.draw(caraSprite_);
        window_.draw(inicioCabezaSprite_);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ataque de Cabeza");

    AtaqueCabeza ataqueCabeza(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ataqueCabeza.update();
        window.clear();
        ataqueCabeza.draw();
        window.display();
    }

    return 0;
}


