#ifndef PLATAFORMA_MODELO_H
#define PLATAFORMA_MODELO_H

#include <vector>
#include <string>

class Plataforma
{
    public:
    float x;
    float y;
    float width;
    float height;
    public:
    float getPosx() const;
    float getPosy() const;
    void setPosition(float px, float py); 
};

class Mapa
{
    public:
    static Mapa parseMap(const std::vector<std::string>& mapStrings);
    public:
    std::vector<Plataforma> platforms;
};

#endif