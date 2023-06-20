#include <iostream>
#include <SFML/Graphics.hpp>
#include "Police.h"
using namespace std;
using namespace sf;
int main()
{
    int yedge = 900, xedge = 1690;  
    RenderWindow window(VideoMode(xedge, yedge), "Police Window");
    Police a(Color::Red, xedge, yedge);
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(); 
        a.draw(window);
        window.display();
    }
}
