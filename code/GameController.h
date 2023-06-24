#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "vistaBee.h"
#include <iostream>
class GameController 
{
private:
    VistaBee view;    
public:
    void Run() 
    {
        while (view.isOpen()) {
            view.handleInput();
            view.render();
        }
    }
};
#endif