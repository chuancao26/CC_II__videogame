#ifndef SEED_CONTROLLER_H
#define SEED_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "seed_model.h"
#include "seed_view.h"
#include <memory>

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

#endif