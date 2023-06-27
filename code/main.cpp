#include "Controlador.cpp"
#include <iostream>
using namespace std;
using namespace sf;
int main() {
    int xedge = 800, yedge = 800, size = 60;
    float posx = 20, posy = 600;
    std::vector<std::string> mapStrings =
    {
        "PPPPP",
        " P A ",
        "A   A",
        "  PP ",
        "  P  ",
        "A   A",
        "  A  ",
        " P P ",
        "PPPPP",
        " P A ",
        "A   A",
        "  PP ",
        "  P  ",
        "A   A",
        "  A  ",
        " P P ",
        "PPPPP"
    };
    RenderWindow window(VideoMode(xedge, yedge), "CUPHEAD!");
    Cup a(posx, posy, size); 
    JugadorVista jugadorVista(window);
    JugadorControlador controlador(a,jugadorVista,mapStrings);
    controlador.ejecutar();
    return 0;
}