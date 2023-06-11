#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Cup
{
    private:
        float posx, posy, speed = 0.1, salto = 1, gravedad = 0.1;
        int size;
        Color color;
        RectangleShape cup; 
        int xedge, yedge;
        int currentJumps, jumps = 2;
    public: 
        Cup(const int &px, const int& py, const int& size_, const Color& a, const int& limitx, const int& limity)
        {
            xedge = limitx; yedge = limity;
            posx = px; posy = py; size = size_;
            color = a;
            cup.setPosition(posx, posy);
            cup.setFillColor(color);
            cup.setSize(Vector2f(size,size));
        }
        void draw(RenderWindow& a)
        {
            caida();
            a.draw(cup);
        }
       void move(const int& px, const int& py)
        {
            cup.setPosition(posx, posy);
        }       
        void moveController(const bool& xclickRight, const bool& xclickLeft, const bool& yclickDown )
        {
            if (xclickLeft && posx >= 0)
            {
                posx -= speed;
            }
            if (xclickRight && posx <= xedge - size)
            {
                posx = posx + speed;
            }
            if (yclickDown && posy <= yedge - size)
            {
                posy += speed;
            }
            move(posx, posy);
        }
        float getPosx() {return posx;}
        float getPosy() {return posy;}
        void jump(const bool& yclickUp)
        {
            if (yclickUp)
            {
                posy -= salto;
            }
            move(posx, posy);
        }
        void caida()
        {
            if (posy < 600)
                posy += gravedad;
            move(posx, posy);
        }
};

int main()
{
    int xedge = 800, yedge = 800, size = 40;
    float posx = 20, posy = 600;
    bool up, down, left, right;
    Color color = Color::Red;
    RenderWindow window(VideoMode(xedge, yedge), "SFML works!");
    Cup a(posx, posy, size, color, xedge, yedge); 
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
        a.jump(up);
        a.moveController(right,left,down);
        a.draw(window);
        window.display();
    }
    return 0;
}