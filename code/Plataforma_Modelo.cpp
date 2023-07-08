#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <random> 
#include "Plataforma_Modelo.h"

float Plataforma::getPosx() const {return x;}
float Plataforma::getPosy() const {return y;}
void Plataforma::setPosition(float px, float py) 
{
    x = px;
    y = py;
}
Plataforma::Plataforma(){}
Mapa::Mapa()
{
    platformWidth = 200.f;  // Ancho predeterminado de la plataforma
    platformHeight = 30.f;  // Alto predeterminado de la plataforma
    platformSpacingH = 200.f; // Espacio predeterminado entre plataformas
    platformSpacingW = 200.f; // Espacio predeterminado entre plataformas
    currentY = 720.f;
    recorrer=false;
}
std::string Mapa::generarSecuenciaFila() 
{
    std::string fila;
    int numA = rand() % 3 + 1;  // Número aleatorio de letras 'A' (entre 1 y 4)
    int numEspacios = 3 - numA; // Número de espacios en blanco restantes
    for (int i = 0; i < numA; i++) {
        fila += 'A';
    }
    for (int i = 0; i < numEspacios; i++) {
        fila += ' ';
    }
    // Mezcla la secuencia para obtener un orden aleatorio
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(fila.begin(), fila.end(), g);
    return fila;
}
vector<std::string> Mapa::crearMapa(int n)
{
    srand(time(0));  // Semilla aleatoria basada en el tiempo actual
    
    std::vector<std::string> matriz(n);  // Matriz de 5 filas
    for (int i = 0; i < n; i++) {
        matriz[i] = generarSecuenciaFila();
    }
    return matriz;

}
void Mapa::parseMap(const std::vector<std::string>& mapStrings)
{
    float currentX;
    if(currentY!=720)
    {
        currentY-=platforms.back().getPosy()+platformHeight + platformSpacingH;
    }
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
        if(!recorrer)
        {
            currentX = 20.f;
            recorrer=true;
        }
        else{
           currentX = 200.f; // Reiniciar la posición X para cada línea de mapa 
           recorrer=false;
        }
        
        for (size_t col = 0; col < numCols; ++col) {
            char c = (col < mapString.size()) ? mapString[col] : ' ';

            if (c == 'A') // Carácter que representa otra plataforma
            {
                Plataforma platform;
                platform.x = currentX;
                platform.y = currentY;
                platform.width = platformWidth;
                platform.height = platformHeight;

                platforms.push_back(platform);
            }

            // Mueve las coordenadas X hacia la derecha
            currentX += platformWidth + platformSpacingW;
        }

        // Mueve las coordenadas Y hacia arriba para la siguiente línea de mapa
        currentY -= platformHeight + platformSpacingH;
    }
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

bool Mapa::se_elimina(const Plataforma& plat)
{
    if(plat.getPosy()>800)
        return true;
    else
        return false;
}

void Mapa::eliminarPlataformas()
{
    auto it = platforms.begin();
    while (it != platforms.end()) {
        if (se_elimina(*it)) {
            it = platforms.erase(it);
        } else {
            ++it; 
        }
    }
}