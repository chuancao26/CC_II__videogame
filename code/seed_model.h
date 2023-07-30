#ifndef SEED_MODEL_H
#define SEED_MODEL_H

#include <cmath>


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
            speedX = 8.f;
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

        position.x += 8.f*speedX;
        position.y += 8.f*speedY;

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
#endif