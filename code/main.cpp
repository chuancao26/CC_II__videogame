#include "Jugador.cpp"
#include "Plataforma.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    std::vector<std::string> mapStrings = {
    "APAP",
    "PAAP",
    "AAPA"
    };
    Map map = map.parseMap(mapStrings);
    float gravedad = 0.1;
    int xedge = 800, yedge = 800, size = 40;
    float posx = 20, posy = 600;
    bool up, down, left, right;
    Color color = Color::Red;
    RenderWindow window(VideoMode(xedge, yedge), "CUPHEAD!");
    Cup a(posx, posy, size, color, xedge, yedge); 
    bool collision = false;
    bool onPlatform = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        up = Keyboard::isKeyPressed(Keyboard::Up);
        down = Keyboard::isKeyPressed(Keyboard::Down);
        left = Keyboard::isKeyPressed(Keyboard::Left);
        right = Keyboard::isKeyPressed(Keyboard::Right);
        window.clear();
        // cout << a.getPosx() << " ; " << a.getPosy() << endl;
        a.saltar(up);
        a.controlarMovimiento(right,left,down);
        a.dibujar(window);
        a.previousPosition = a.getGlobalBounds();
        if (!onPlatform)
        {
            // Si la Cup no está en una plataforma, aplicamos la gravedad
            posy += gravedad;
        }
        collision = false;
        onPlatform = false;

        for (const auto& platform : map.platforms)
        {
            window.draw(platform.shape);
        }
        for (const auto& platform : map.platforms)
        {
            if (a.isColliding(platform))
            {
                // Si hay colisión, ajusta la posición vertical de la Cup
                collision = true;
                //onPlatform = true;
        
                if (a.getPosy() <= platform.y) // Verifica si la Cup está cayendo
                {
                    // Ajusta la posición vertical de la Cup para que no pueda atravesar la plataforma
                    posy = platform.y - size;
                    a.mover(posx, posy);
                }
                if (a.previousPosition.top >= platform.y + platform.height) 
                {
                    // Movimiento desde abajo
                    posy = platform.y + platform.height;
                }
                break;

            }
        }
        if (!collision)
        {
            // Si no hubo colisión, actualiza la posición vertical de la Cup
            posy += gravedad;
        }
        if (!onPlatform)
        {
            a.caida();
        }

        a.mover(posx, posy); // Actualiza la posición de cup

        window.display();
    }
    return 0;
}