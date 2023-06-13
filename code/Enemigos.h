class Enemigos
{
    private:
        float gravedad, speed, damage, vida;
        int posx, posy, size;
        friend class Tipos_disparo;
        friend class Plataforma;
    public:
        void mover();
        void colision(); //interacción con las balas del jugador//Si el jugador choca pierde una vida
        void textura();
};
class Boss : public Enemigos
{
    private:
        float gravedad, speed, vida;
        int posx, posy, size, estado;
    public:
        void mostrar(); //Aparece en (posx,posy)
        void disparar();
        void mover(); //animación
        void colision(); //Interaccion con las balas del jugador o el jugador
        void textura();
};

class Flor : public Boss
{
    private:
        float vida;
        int posx, posy, size, estado;
        friend class bomba;
    public:
        void mostrar(); //Aparece en (posx,posy)
        void mover(); //animación
        void disparar(); //solo en estado4 y avanza en zigzag en el ancho del tamaño del cup, en dirección al lado izquierdo.
        void ataqueCabeza(); //llena con su cuerpo, la parte superior o inferior
        void colision(); //Si el jugador choca y se mantiene parado 3 segundos, pierde una vida, en caso estar en estado 1, pierte una vida a penas lo toque
        void textura();
        void estado1(); //Ataques con la cabeza
        void estado2(); //lanzar bombas que aparecen en la parte superior de la ventana y caen
        void estado3(); //Lanzar cohetes pequeños que van en dirección al jugador, aparecen en orden y van en línea recta
        void estado4(); //El piso entero es su cuerpo y pueden crecer en "y" aleatoriamente, raíces en cada X donde estén las plataformas
        void desaparecer(); //para el cambio de estados o la cabeza
};
class Bomba : public Enemigos
{
    private:
        float gravedad, speed, vida;
        int posx, posy, size;
        friend class Mounstro;
    public:
        void mostrar(); //Aparece en (posx,posy)
        void move(); //Empieza arriba y cae hasta el piso
        void colision(); //Si el jugador choca pierde una vida
        void morder(); //al tocar el piso se mantiene el objeto ahí por un tiempo y desaparece
        void desaparecer();
};


class Bee : public Boss
{
    private:
        float speed, vida;
        int posx, posy, size, estado;
        friend class Tipos_disparo;
        friend class Plataforma;
        friend class bomba;
    public:
        void mostrar(); //Aparece en (posx,posy)
        void llamada();
        void disparar(); //desdeabajo
        void desaparecer();
        void posicion();
        void mover(); //animación
        void colision(); //interacción con las balas del jugador
        void textura();
        void estado1(); //Lanzar un triángulo, como objeto que si se tca, pierdes na vida
        void estado2(); //Cabeza cadena y lanza bombas con direccion
        void estado3(); //avion, también dispara

};
class Mounstro : public Enemigos
{
    private:
        float speed, vida;
        int posx, posy, size;
    public:
        void mover(); //Empieza arriba y cae hasta el piso en donde
        void colision(); //Si el jugador choca pierde una vida
        void textura();
        void posicion();
        void desaparecer(); //se va del mapa, solo "desaparece" al salir de la ventana
};
class BombBee : public Enemigos
{
    private:
        float speed, vida, temporizador;
        int posx, posy, size;
        friend class Bala();
    public:
        void mostrar();
        void explotar();
|       void desaparecer();
};

