#ifndef FLYINGFIST_H
#define FLYINGFIST_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Enemigos.h"
class FlyingFistM : public Enemigo
{
private:
    float radiusX, radiusY, x, y, angle, startedTime, elapsedTime;
    int xBorder, yBorder;
public:
    FlyingFistM(const int& xBorder, const int& yBorder, const float& elapsedTime_):xBorder(xBorder), yBorder(yBorder),
    radiusX(xBorder * 0.5f), radiusY(yBorder * 0.5f), angle(0.0f), elapsedTime(elapsedTime_), startedTime(elapsedTime);
    {
    }
    void move()
    {

    }
    void moveRight()
    void moveLeft()
    bool isExpired()

};
#endif 