#ifndef BOOMERANGMODEL_H
#define BOOMERANGMODEL_H
#include <iostream>

class BoomerangModel {
private:
    float x;
    float y;
    float width;
    float height;
    int direction;
    bool deleteFlag;

public:
    BoomerangModel(float startX, float startY, float width, float height) :
        x(startX), y(startY), width(width), height(height), direction(1), deleteFlag(false)
    {
    }

    void moveRight(float windowWidth) {
        x += 7.0f;
        if (x >= windowWidth - width) {  // Extremo derecho
            direction--;  // Cambiar dirección a izquierda
        }
    }

    void moveLeft() {
        x -= 7.0f;
        if (x <= -2 * width) {  // Punto de inicio
            direction = 0;  // Cambiar dirección a derecha
        }
    }

    void update(float windowWidth) {
        if (direction == 1) {
            moveLeft();
        }
        else if (direction == 0) {
            moveRight(windowWidth);
        }
        else {
            deleteFlag = true;
        }
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getWidth() const {
        return width;
    }

    float getHeight() const {
        return height;
    }

    bool shouldDelete() const {
        return deleteFlag;
    }

    void deleteBoomerang() {
        deleteFlag = true;
    }

    bool reachedRightEdge(float windowWidth) const {
        return (x >= windowWidth - width);
    }
};
#endif