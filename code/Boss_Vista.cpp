#include <SFML/Graphics.hpp>

class FlorBossView {
public:
    FlorBossView(sf::RenderWindow& window) : window_(window) {
        if (!textureGreen_.loadFromFile("img\\nivel_flor\\normal1.png")) {
            // Error al cargar la imagen normal1.png
            return;
        }

        if (!texturePurple_.loadFromFile("img\\nivel_flor\\normal2.png")) {
            // Error al cargar la imagen normal2.png
            return;
        }

        spriteGreen_.setTexture(textureGreen_);
        spritePurple_.setTexture(texturePurple_);

        spriteGreen_.setScale(window.getSize().x / 3 / spriteGreen_.getLocalBounds().width,
                              ((window.getSize().y * 4) / 5) / spriteGreen_.getLocalBounds().height);
        spritePurple_.setScale(window.getSize().x / 3 / spritePurple_.getLocalBounds().width,
                               ((window.getSize().y * 4) / 5) / spritePurple_.getLocalBounds().height);

        spriteGreen_.setPosition(window_.getSize().x - (spriteGreen_.getLocalBounds().width)/1.1,
                                 window.getSize().y / 12);
        spritePurple_.setPosition(window_.getSize().x - (spritePurple_.getLocalBounds().width)/1.1,
                                  window.getSize().y / 12);
        textureGreen_.setSmooth(true);
        texturePurple_.setSmooth(true);
        rectThird_.setSize(sf::Vector2f(200.0f, 250.0f));
        rectThird_.setFillColor(sf::Color::Blue);
        rectThird_.setPosition(window_.getSize().x, (window_.getSize().y - rectThird_.getSize().y) / 2.0f);

        isGreenActive_ = true;
        timer_ = 0.0f;
        duration_ = 0.5f;
        isGrowing_ = false;
        growthTimer_ = 0.0f;
        growthDuration_ = 2.0f;
    }

    void update(float deltaTime) {
        timer_ += deltaTime;
        growthTimer_ += deltaTime;

        if (timer_ >= duration_) {
            isGreenActive_ = !isGreenActive_;
            timer_ = 0.0f;
        }

        if (isGrowing_) {
            float growthAmount = (window_.getSize().x - rectThird_.getSize().x) / growthDuration_ * deltaTime;
            rectThird_.setSize(rectThird_.getSize() + sf::Vector2f(growthAmount, 0.0f));
            rectThird_.setPosition(rectThird_.getPosition().x - growthAmount, rectThird_.getPosition().y);

            if (growthTimer_ >= growthDuration_) {
                rectThird_.setSize(sf::Vector2f(200.0f, 250.0f));
                rectThird_.setPosition(window_.getSize().x, (window_.getSize().y - rectThird_.getSize().y) / 2.0f);

                growthTimer_ = 0.0f;
                isGrowing_ = false;
            }
        }
    }

    void draw() {
        if (isGreenActive_) {
            window_.draw(spriteGreen_);
        } else {
            window_.draw(spritePurple_);
        }

        window_.draw(rectThird_);
    }
    void removeRectangles() {
        spriteGreen_.setScale(0.0f, 0.0f);
        spritePurple_.setScale(0.0f, 0.0f);
        rectThird_.setSize(sf::Vector2f(0.0f, 0.0f));
    }

    void startGrowing() {
        if (!isGrowing_) {
            isGrowing_ = true;
            growthTimer_ = 0.0f;
        }
    }


private:
    sf::RenderWindow& window_;
    sf::Texture textureGreen_;
    sf::Texture texturePurple_;
    sf::Sprite spriteGreen_;
    sf::Sprite spritePurple_;
    sf::RectangleShape rectThird_;
    bool isGreenActive_;
    float timer_;
    float duration_;
    bool isGrowing_;
    float growthTimer_;
    float growthDuration_;
};
