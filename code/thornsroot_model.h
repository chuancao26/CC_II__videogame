#ifndef THORNSROOT_MODEL_H
#define THORNSROOT_MODEL_H

#include <iostream>
#include <cmath>
#include <random>

class ThornsRootModel {
private:
    float R1;
    float R2;

public:
    ThornsRootModel() : R1(0.f), R2(0.f) {}

    void update(float windowWidth, float windowHeight) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 3);

        float rectX1 = windowWidth / 6;

        int value = dist(gen);
        if (value == 1) {
            float rectX2 = windowWidth / 6;
            R1 = rectX1 - 20;
            R2 = rectX2 - 20;
        } else if (value == 2) {
            float rectX2 = windowWidth * 2 / 6;
            R1 = rectX1 - 20;
            R2 = rectX2 - 20;
        } else {
            float rectX2 = windowWidth * 3 / 6;
            R1 = rectX1 - 20;
            R2 = rectX2 - 20;
        }
    }

    float getR1() const {
        return R1;
    }

    float getR2() const {
        return R2;
    }
};

#endif