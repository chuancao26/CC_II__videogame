
#ifndef BOSSCREATES_CONTROLLER_H
#define BOSSCREATES_CONTROLLER_H
#include "bosscreates_view.h"
#include "bosscreates_model.h"
#include <iostream>
class BossController {
private:
    BossModel model_;
    FlorBossView view_;
    sf::Clock clock2;

public:
    BossController(sf::RenderWindow& window) : view_(window) {}

    void update() {
        float deltaTime2 = clock2.restart().asSeconds();
        model_.update(deltaTime2);

        if (model_.isGrowing()) {
            view_.startGrowing();
        }
    }

    void draw() {
        view_.draw(model_.getState());
    }
};
#endif