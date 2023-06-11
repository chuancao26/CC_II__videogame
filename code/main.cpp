#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Cup
{
    private:
        float posx, posy, speed = 0.01;
        int size;
        Color color;
        RectangleShape cup; 
        int xedge, yedge;
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
            a.draw(cup);
        }
       void move(const int& px, const int& py)
        {
            posx = (px + xedge) % xedge;
            posy = (py + yedge) % yedge;
            cup.setPosition(posx, posy);
        }       
        void moveController(const bool& xclickRight, const bool& xclickLeft, const bool& yclickUp, const bool& yclickDown )
        {
            if (xclickLeft)
            {
                posx += speed;
            }
            if (xclickRight)
            {
                posx -= speed;
            }
            if (yclickDown)
            {
                posy -= speed;
            }
            if (yclickUp)
            {
                posy += speed;
            }
            move(posx, posy);
        }
        float getPosx() {return posx;}
        float getPosy() {return posy;}
};

int main()
{
    int xedge = 800, yedge = 800, size = 40;
    float posx = 400, posy = 400;
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
        cout << a.getPosx() << " ; " << a.getPosy() << endl;
        a.moveController(right,left,up,down);
        a.draw(window);
        window.display();
    }
    return 0;
}