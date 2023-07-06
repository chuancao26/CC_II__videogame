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
    void caida();
};

class Mapa
{
    public:
    static Mapa parseMap(const std::vector<std::string>& mapStrings);
    public:
    Plataforma *platforms; 
    int size;
    void eliminarPlataformas();
    Mapa();
    void set(const Plataforma val, int pos);
    Plataforma get(int pos)const;
    void pushback(const Plataforma val);
    void remove(int pos);
    ~Mapa();
};

#endif