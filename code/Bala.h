#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Bala
{
    private:
        float speed, damage, tarjeta, distancia;
        int posx, posy, size;
        KeyBoard::Key D_left, D_right, D_up, D_down;
        bool activa;
    public:
    	Bala()
   	    {
     	   activa = false;
    	}
	    void activar();
	    void desactivar();
    	bool EstaActiva(){
            return activa;
    	}
        void move();
        void colision(); //SOLO con enemigos o desaparece
        void textura();
        void posicion();
        //void desaparecer(); si es con pool solo se regresa con "devolver bala"
};

class Tipos_disparo : Bala
{
private:
    int tipo;
public:
    void disparoLinea();//la bala sale en linea recta a la direccion asignada
    void disparoCincoEnUno();//salen cinco balas en forma de escudo
    void disparoBoomerang();//la bala sale en forma de curva
    void disparoPelota();//se dispara una gran bala
    void disparoRecargar();//hay un tiempo de recarga entre balas especialmente para la gran bala
    void disparoCercano();//
    void disparoBoss();//balas que genera el jefe
    void disparoenemigo();//balas de los monstritos
};
