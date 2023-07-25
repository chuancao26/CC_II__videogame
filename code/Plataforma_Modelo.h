#ifndef PLATAFORMA_MODELO_H
#define PLATAFORMA_MODELO_H
#include <vector>
#include <string>

class Plataforma
{
    public:
    float x,y, gravedad,width,height;
    public:
    Plataforma();
    float getPosx() const;
    float getPosy() const;
    void setPosition(float px, float py); 
    void caida(float d);
    
};

class Mapa
{
    public:
    float platformWidth ;  // Ancho predeterminado de la plataforma
    float platformHeight;  // Alto predeterminado de la plataforma
    float platformSpacingH; // Espacio predeterminado entre plataformas
    float platformSpacingW ; // Espacio predeterminado entre plataformas
    float currentY;
    bool recorrer;
    int size;
    public:
    Mapa();
    void parseMap(const std::vector<std::string>& mapStrings);
    Plataforma* platforms;
    std::vector<std::string> crearMapa(int n);
    std::string generarSecuenciaFila();
    void eliminarPlataformas();
    void remove(int pos);
    void push_back(const Plataforma&& plat);
    bool se_elimina(const Plataforma& plat);
    void crearPlataformas();
};

#endif