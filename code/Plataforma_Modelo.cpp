#include "Plataforma_Modelo.h"

float Plataforma::getPosx() const {return x;}
float Plataforma::getPosy() const {return y;}
void Plataforma::setPosition(float px, float py) 
{
    x = px;
    y = py;
}
Plataforma::Plataforma(){}
Mapa Mapa::parseMap(const std::vector<std::string>& mapStrings)
{
    Mapa map;
    const float platformWidth = 80.f;  // Ancho predeterminado de la plataforma
    const float platformHeight = 20.f;  // Alto predeterminado de la plataforma
    const float platformSpacingH = 80.f; // Espacio predeterminado entre plataformas
    const float platformSpacingW = 80.f; // Espacio predeterminado entre plataformas

    float currentX = 50.f;
    float currentY = 600.f; // Cambiamos la posición inicial en Y

    // Obtener la cantidad de filas y columnas del mapa
    size_t numRows = mapStrings.size();
    size_t numCols = 0;
    for (const auto& mapString : mapStrings) {
        if (mapString.size() > numCols) {
            numCols = mapString.size();
        }
    }

    for (size_t row = 0; row < numRows; ++row) {
        const auto& mapString = mapStrings[row];
        currentX = 50.f; // Reiniciar la posición X para cada línea de mapa

        for (size_t col = 0; col < numCols; ++col) {
            char c = (col < mapString.size()) ? mapString[col] : ' ';

            if (c == 'P') // Carácter que representa una plataforma
            {
                Plataforma platform;
                platform.x = currentX;
                platform.y = currentY;
                platform.width = platformWidth;
                platform.height = platformHeight;

                map.platforms.push_back(platform);
            }
            else if (c == 'A') // Carácter que representa otra plataforma
            {
                Plataforma platform;
                platform.x = currentX;
                platform.y = currentY;
                platform.width = platformWidth;
                platform.height = platformHeight;

                map.platforms.push_back(platform);
            }

            // Mueve las coordenadas X hacia la derecha
            currentX += platformWidth + platformSpacingW;
        }

        // Mueve las coordenadas Y hacia arriba para la siguiente línea de mapa
        currentY -= platformHeight + platformSpacingH;
    }

    return map;
}
void Plataforma::caida()
{
    if(y<800)
    {
        gravedad = 10.f; // Ajusta el valor de gravedad según tus necesidades
        y += gravedad;
    }
    
    setPosition(x,y);
}
