#include "Controlador.cpp"
#include <iostream>
using namespace std;
using namespace sf;
int main() {
    int xedge = 1280, yedge = 720, size = 60;
    float posx = 20, posy = 600;
    std::vector<std::string> mapStrings =
    {
        "A   A  A",
        "  A    A",
        " P P   A",
        "PPPPPP  "
    };
    Cup a(posx, posy, size); 
    Controlador controlador(a,mapStrings);
    controlador.ejecutar();
    return 0;
}