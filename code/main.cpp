#include "GameController.h"
int main()
{   
    GameController gameController;
    gameController.Run();
}





























// class Cup
// {
//     private:
//         float posx, posy, speed = 0.1, salto = 100, gravedad = 5;
//         int size;
//         Color color;
//         RectangleShape cup; 
//         int xedge, yedge;
//         int currentJumps, jumps = 2;
//     public: 
//         Cup(const int &px, const int& py, const int& size_, const Color& a, const int& limitx, const int& limity)
//         {
//             xedge = limitx; yedge = limity;
//             posx = px; posy = py; size = size_;
//             color = a;
//             cup.setPosition(posx, posy);
//             cup.setFillColor(color);
//             cup.setSize(Vector2f(size,size));
//         }
//         void draw(RenderWindow& a)
//         {
//             caida();
//             a.draw(cup);
//         }
//        void move(const int& px, const int& py)
//         {
//             cup.setPosition(posx, posy);
//         }       
//         void moveController(const bool& xclickRight, const bool& xclickLeft, const bool& yclickDown )
//         {
//             if (xclickLeft && posx >= 0)
//             {
//                 posx -= speed;
//             }
//             if (xclickRight && posx <= xedge - size)
//             {
//                 posx = posx + speed;
//             }
//             if (yclickDown && posy <= yedge - size)
//             {
//                 posy += speed;
//             }
//             move(posx, posy);
//         }
//         float getPosx() {return posx;}
//         float getPosy() {return posy;}
//         #include <SFML/System.hpp>

//         void jump(bool& yclickUp)
//         {
//             static int jumpCount = 0; // Contador de saltos
//             static Clock jumpTimer; // Temporizador para controlar el tiempo de espera
            
//             if (yclickUp && jumpCount < 2 && jumpTimer.getElapsedTime().asSeconds() >= 0.8f)
//             {                
//                 if (jumpCount == 0)
//                 {
//                     posy -= salto;
//                     jumpCount++; // Incrementar el contador de saltos

//                 }
//                 else if (jumpCount == 1)
//                 {
//                     posy -= salto;
//                     jumpCount = 0;
//                     // Aquí puedes realizar cualquier acción adicional después del segundo salto
//                 }
//                 jumpTimer.restart(); // Reiniciar el temporizador
//             }
//             move(posx, posy);
//         }

//         void caida()
//         {
//             if (posy < 600)
//                 posy += gravedad;
//             move(posx, posy);
//         }
// };

// int main()
// {
//     int xedge = 1900, yedge = 1080, size = 40;
//     float posx = 20, posy = 600;
//     bool up, down, left, right;
//     Color color = Color::Red;
//     RenderWindow window(VideoMode(xedge, yedge), "SFML works!");
//     Cup a(posx, posy, size, color, xedge, yedge); 
//     while (window.isOpen())
//     {
//         Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == Event::Closed)
//                 window.close();
//         }
//         up = Keyboard::isKeyPressed(Keyboard::Up);
//         down = Keyboard::isKeyPressed(Keyboard::Down);
//         left = Keyboard::isKeyPressed(Keyboard::Left);
//         right = Keyboard::isKeyPressed(Keyboard::Right);
//         window.clear();
//         a.jump(up);
//         a.moveController(right,left,down);
//         a.draw(window);
//         window.display();
//     }
//     return 0;
// }