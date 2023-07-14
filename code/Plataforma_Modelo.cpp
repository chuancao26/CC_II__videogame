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
    size=0;
    platformWidth = 200.f;  // Ancho predeterminado de la plataforma
    platformHeight = 30.f;  // Alto predeterminado de la plataforma
    platformSpacingH = 90.f; // Espacio predeterminado entre plataformas
    platformSpacingW = 300.f; // Espacio predeterminado entre plataformas
    currentY = 720.f;
    recorrer=false;
    platforms= new Plataforma[size];
}
std::string Mapa::generarSecuenciaFila() 
{
    std::string fila;
    int numA = rand() % 3 + 1;  // Número aleatorio de letras 'A' (entre 1 y 3)
    for (int i = 0; i < numA; i++) {
        fila += 'A';
    }
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
    size_t numRows = mapStrings.size();
    size_t numCols = 0;
    for (const auto& mapString : mapStrings) {
        if (mapString.size() > numCols) {
            numCols = mapString.size();
        }
    }
    float currentX;
    if(currentY!=720)
    {
        currentY-=platforms[size].getPosy()+platformHeight+platformSpacingH;
        
    }

    for (size_t row = 0; row < numRows; ++row) {
        const auto& mapString = mapStrings[row];
        if(!recorrer)
        {
            currentX = 40.f;
            recorrer=true;
        }
        else{
           currentX = 290.f; // Reiniciar la posición X para cada línea de mapa 
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

                push_back(std::move(platform));
            }

            // Mueve las coordenadas X hacia la derecha
            currentX += platformWidth + platformSpacingW;
        }

        // Mueve las coordenadas Y hacia arriba para la siguiente línea de mapa
        currentY -= platformHeight + platformSpacingH;
    }
}

void Plataforma::caida(float d)
{
    if(y<800)
    {
        gravedad = 50.f*d; // Ajusta el valor de gravedad según tus necesidades
        y += gravedad;
    }
    
    setPosition(x,y);
}

void Mapa::push_back(const Plataforma&& plat)
{
    Plataforma *newplat= new Plataforma[size+1];
    for(int i=0;i<size;i++)
        newplat[i]=std::move(platforms[i]);
    newplat[size] = plat;
    size++;
    delete[] platforms;
    this->platforms=newplat;
}

bool Mapa::se_elimina(const Plataforma& plat)
{
    if(plat.getPosy()>800)
        return true;
    else
        return false;
}

void Mapa::remove(int pos)
{
    Plataforma *newdata= new Plataforma[size-1];
    for(int i=pos;i<size-1;i++)
        newdata[i]=std::move(platforms[i+1]);
    for(int i=0;i<pos;i++)
        newdata[i]=std::move(platforms[i]);
    size--;
    delete[] platforms;
    this->platforms=newdata;
}

void Mapa::eliminarPlataformas()
{
    auto it = platforms[0];
    for(int i=0;i<size;i++)
    {
        if(se_elimina(platforms[i]))
        {
            remove(i);
        }
    }
    
}

void Mapa::crearPlataformas()
{
    vector<string> m = crearMapa(1);
    parseMap(m);

}