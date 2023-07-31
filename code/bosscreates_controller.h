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
    void update() {
        model_.update();
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
    void death(sf::RenderWindow& window){
        if (view_.getcurrentState()==4){
            model_.setlineX(window.getSize().x*2/3);
            model_.setlineY(window.getSize().y/2);
        }
        else{
            model_.setlineX(window.getSize().x*2/3);
        }
    }
    float lineX() {
    return model_.getLineX();
    }

    float lineY() {
        return model_.getLineY();
    }

    float getvida(){
        return model_.getVida();
    }
    void Attack(){
        model_.attack();
    }
};
#endif