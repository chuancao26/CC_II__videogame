
#ifndef BOSSCREATES_CONTROLLER_H
#define BOSSCREATES_CONTROLLER_H
#include "bosscreates_view.h"
#include "bosscreates_model.h"
#include <iostream>
class BossController {
private:
    BossModel model_;
    FlorBossView view_;

public:
    BossController(sf::RenderWindow& window) : view_(window, model_) {}

    void update(float deltaTime) {
        model_.update(deltaTime);

        if (model_.isGrowing()) {
            view_.startGrowing();
        }
    }

    void draw() {
        view_.draw();
    }

    void setState(int state) {
        view_.setcurrentState(state);
    }
};

#endif