
#ifndef BOSSCREATES_MODEL_H
#define BOSSCREATES_MODEL_H

#include <iostream>
class BossModel {
private:
    int state;
    int currentImageIndex;
    float timer_;
    float duration_;
    bool isGrowing_;
    float growthTimer_;
    float growthDuration_;

public:
    BossModel() : state(1), currentImageIndex(0), timer_(0.0f), duration_(0.2f), isGrowing_(false), growthTimer_(0.0f), growthDuration_(0.042f) {}

    void update(float deltaTime) {
        timer_ += deltaTime;
        growthTimer_ += deltaTime;

        if (timer_ >= duration_) {
            if (state == 1) {
                state = 0;
            } else if (state == 0) {
                state = 1;
            }
            currentImageIndex = 0;
            timer_ = 0.0f;
        }
    }

    void startGrowing() {
        if (!isGrowing_) {
            isGrowing_ = true;
            growthTimer_ = 0.0f;
        }
    }

    bool isGrowing() const {
        return isGrowing_;
    }

    void stopGrowing() {
        isGrowing_ = false;
    }

    int getState() const {
        return state;
    }

    int getCurrentImageIndex() const {
        return currentImageIndex;
    }

    void incrementImageIndex() {
        currentImageIndex++;
    }
    
};
#endif