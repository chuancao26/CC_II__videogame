#include <iostream>
#include <SFML/Graphics.hpp>
#include "Police.h"
#include "WorkerBee.h"
using namespace std;
using namespace sf;
int main()
{
    int xedge = 1690, yedge = 900;  
    RenderWindow window(VideoMode(xedge, yedge), "Police Window");
    Police a(Color::Red, xedge, yedge);
    WorkerBee wb(1690,900);
    Espina espina(850,450);
    sf::Clock clock;
    sf::Time elapsedTime;
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(); 
        elapsedTime = clock.getElapsedTime();
        a.draw(window);
        a.update(elapsedTime);
        wb.draw(window);
        espina.move(0);
        espina.draw(window);
        window.display();
    }
}
