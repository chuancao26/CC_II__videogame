#include "Modelo.cpp"
#include "Vista.cpp"
#include <thread>
#include <future>
#include <memory>
using FloatPtr = std::shared_ptr<float>;

class Controlador {
private:
    //Modelo
    Modelo modelo;
    //Vista
    Vista vista;

    bool elegidos;
    float elapsedTime;
    float clock5, clock;
    //float clock,clock2,clock5;
    int nivel,j1,j2;
    vector<int> jugadores;
    std::mutex modeloMutex;

public:
    Controlador()
        : vista(1280, 720)
    {
        nivel = 0;
        elegidos=false;
    }
    void EventoMouse()
    {
        std::vector<FloatPtr> Posicion=std::vector<FloatPtr>();
        int m=vista.procesarEventosMouse(Posicion);
        if(m==16)
        {
            FloatPtr primerElemento = Posicion.front();
            FloatPtr segundoElemento = Posicion.back();
            sf::Vector2f mousePos(*primerElemento, *segundoElemento);
            switch(nivel)
            {
                case 0:
                    if(*primerElemento>=750 && *primerElemento<=1100 && *segundoElemento>=220 && *segundoElemento<=250)
                    {
                        nivel=1;
                    }
                    else if(*primerElemento>=750 && *primerElemento<=980 && *segundoElemento>=320 && *segundoElemento<=360)
                    {
                        nivel=3;
                    }
                    else if(*primerElemento>=750 && *primerElemento<=1130 && *segundoElemento>=425 && *segundoElemento<=460)
                    {
                        nivel=4;
                    }
                    else if(*primerElemento>=750 && *primerElemento<=870 && *segundoElemento>=520 && *segundoElemento<=565)
                    {
                        vista.window.close();
                    }
                    break;
                case 1:
                    if(*primerElemento>=1180 && *primerElemento<=1221 && *segundoElemento>=628 && *segundoElemento<=656)
                    {
                        nivel=0;
                    }
                    else if(*primerElemento>=1233 && *primerElemento<=1270 && *segundoElemento>=628 && *segundoElemento<=654)
                    {
                        nivel=2;
                    }
                    break;
                case 2:
                    if(*primerElemento>=1180 && *primerElemento<=1221 && *segundoElemento>=628 && *segundoElemento<=656)
                    {
                        nivel=0;
                    }
                    break;
                case 3:
                    if(*primerElemento>=195 && *primerElemento<=378 && *segundoElemento>=51 && *segundoElemento<=98)
                    {
                        nivel=0;
                    }
                    else if(*primerElemento>=899 && *primerElemento<=1082 && *segundoElemento>=60 && *segundoElemento<=105)
                    {
                        nivel=1;
                    }
                    break;
                case 4:
                    jugadores.push_back(vista.elegir.seleccionar(mousePos,true));
                    if(jugadores.size()==2)
                        elegidos=true;
                    if(*primerElemento>=130 && *primerElemento<=294 && *segundoElemento>=415 && *segundoElemento<=455)
                    {
                        nivel=1;
                    }
                    else if(*primerElemento>=133 && *primerElemento<=278 && *segundoElemento>=582 && *segundoElemento<=620)
                    {
                        nivel=0;
                    }  
                    break;
            }
        }
        
    }
    void manejarEventos(int m) {
        switch (m)
        {
            case 1:
                modelo.jugador1->estaSaltando(true);
                modelo.jugador1->saltar();
                break;
            case 2:
                modelo.jugador1->vaizquierda(true);
                modelo.jugador1->moverIzquierda();
                break;
            case 3:
                modelo.jugador1->vaderecha(true);
                modelo.jugador1->moverDerecha();
                break;
            case 4:
                modelo.jugador1->moverAbajo();
                break;
            case 5:
                nivel += 1;
                break;
            case 6:
                modelo.jugador1->disparar(modelo.jugador1->getPosx(), modelo.jugador1->getPosy());
                break;
            case 7:
                modelo.jugador2->estaSaltando(true);
                modelo.jugador2->saltar();
                break;
            case 8:
                modelo.jugador2->vaizquierda(true);
                modelo.jugador2->moverIzquierda();
                break;
            case 9:
                modelo.jugador2->vaderecha(true);
                modelo.jugador2->moverDerecha();
                break;
            case 10:
                modelo.jugador2->moverAbajo();
                break;
            case 11:
                modelo.jugador2->disparar(modelo.jugador2->getPosx(),modelo.jugador2->getPosy());
                break;
            case 12:
                modelo.jugador1->vaizquierda(false);
                modelo.jugador1->vaderecha(false);
                modelo.jugador1->estaSaltando(false);
                break;
            case 13:
                modelo.jugador1->estaSaltando(false);
                break;
            case 14:
                modelo.jugador2->vaizquierda(false);
                modelo.jugador2->vaderecha(false);
                modelo.jugador2->estaSaltando(false);
                break;
            case 15:
                modelo.jugador2->estaSaltando(false);
                break;
                               
        }
        modelo.jugador1->caida();
        modelo.jugador2->caida();
    }

    void Menu()
    {
        switch (nivel)
        {
            case 0:
                vista.background.cargar(vista.window, nivel);
                vista.background.draw1(vista.window);
                elegidos=false;
                modelo.limpiarPlataformas();
                modelo.eliminarJugadores();
            break;
            case 1:
                if(!elegidos)
                {
                    j1=1;
                    j2=2;
                    modelo.asignarDisparos(j1,*modelo.jugador1);
                    modelo.asignarDisparos(j2,*modelo.jugador2);
                    vista.cargarJugadores(j1,j2); 
                }
                modelo.jugador1->update(vista.getGameTime());
                modelo.jugador2->update(vista.getGameTime());
                vista.background.cargar(vista.window, nivel);
                vista.background.draw2(vista.window);
                modelo.crearplataformas(nivel);
                vista.eliminarplataformas(modelo.map);
                mover_plataformas();
                dibujarPlataformas();
                vista.dibujarBotones(nivel);
                vista.dibujarCup(*modelo.jugador1,*modelo.jugador2);
                vista.loadBeeView(*modelo.jugador1,*modelo.jugador2);
                break;
            case 2:
                modelo.jugador1->update(vista.getGameTime());
                modelo.jugador2->update(vista.getGameTime());
                modelo.limpiarPlataformas();
                vista.background.cargar(vista.window, nivel);
                vista.background.draw1(vista.window);
                vista.dibujarCup(*modelo.jugador1,*modelo.jugador2);
                vista.dibujarBotones(nivel);
                vista.loadFlorView(vista.window,*modelo.jugador1,*modelo.jugador2);
                modelo.crearplataformas(nivel);
                dibujar_Balas_Jugador1();
                dibujar_Balas_Jugador2();
                break;
            case 3:
                vista.background.cargar(vista.window, nivel);
                vista.background.draw1(vista.window);

                break;
            case 4:
                vista.background.cargar(vista.window, nivel);
                vista.background.draw1(vista.window);
                vista.elegir.dibujar(vista.window);
                if(elegidos)
                {
                    j1=jugadores.front();
                    j2=jugadores.back();
                    modelo.asignarDisparos(j1,*modelo.jugador1);
                    modelo.asignarDisparos(j2,*modelo.jugador2);
                    vista.cargarJugadores(j1,j2); 
                }

                break;
            default:
                break;
            }
    }
    void renderizar() {
        vista.window.clear();
        Menu();
        vista.window.display();
    }
    void dibujarPlataformas() {
        for(int i=0;i<modelo.map->size;i++)
        {
            vista.dibujarPlat(modelo.map->platforms[i]);
        }
    }
    void colisiones() {
        for (int i=0;i<modelo.map->size;i++)
        {
            if (vista.colision(vista.jugador_v.cupShape, modelo.map->platforms[i]))
            {
                modelo.jugador1->enPlataforma(true);
                modelo.jugador1->estaColisionando(modelo.map->platforms[i].y);
            }
            else {
                modelo.jugador1->enPlataforma(false);
            }

            if (vista.colision(vista.jugador_v2.cupShape, modelo.map->platforms[i]))
            {
                modelo.jugador2->enPlataforma(true);
                modelo.jugador2->estaColisionando(modelo.map->platforms[i].y);
            }
            else {
                modelo.jugador2->enPlataforma(false);
            }
        }
    }
    void colisionesMounstruos()
    {
        modelo.jugador1->enChoque(vista.colisiones1Bee(*modelo.jugador1));
        modelo.jugador2->enChoque(vista.colisiones1Bee(*modelo.jugador2));
    }
    void mover_plataformas() {
        float delta = vista.clock.restart().asSeconds();
        for(int i=0;i<modelo.map->size;i++)
        {
            modelo.map->platforms[i].caida(delta);
        }
        vista.background.actualizar(vista.window, delta);
    }
    void dibujar_Balas_Jugador1() {
        modelo.moverBalas(*modelo.jugador1,j1);
        for(int i=0;i<modelo.jugador1->disparo->size;i++)
        {
            switch (j1)
            {
            case 1:{
                BalaNormal* balaNormal = dynamic_cast<BalaNormal*>(modelo.jugador1->disparo->balas[i]);
                if (balaNormal) {
                    vista.dibujarBalasNormales(*balaNormal);
                }
                break;}
            case 2:{
                BalaBomba* balaBomba = dynamic_cast<BalaBomba*>(modelo.jugador1->disparo->balas[i]);
                if (balaBomba) {
                    vista.dibujarBalasBombas(*balaBomba);
                }
                break;}
            case 3:{
                BalaEstrella* balaEstrella = dynamic_cast<BalaEstrella*>(modelo.jugador1->disparo->balas[i]);
                if (balaEstrella) {
                    vista.dibujarBalasEstrellas(*balaEstrella);
                }
                break;}
            }
        }
        
    }
    void dibujar_Balas_Jugador2() {
        modelo.moverBalas(*modelo.jugador2,j2);
        for(int i=0;i<modelo.jugador2->disparo->size;i++)
        { 
            switch (j2)
            {
            case 1:{
                BalaNormal* balaNormal = dynamic_cast<BalaNormal*>(modelo.jugador2->disparo->balas[i]);
                if (balaNormal) {
                    vista.dibujarBalasNormales(*balaNormal);
                }
                break;}
            case 2:{
                BalaBomba* balaBomba = dynamic_cast<BalaBomba*>(modelo.jugador2->disparo->balas[i]);
                if (balaBomba) {
                    vista.dibujarBalasBombas(*balaBomba);
                }
                break;}
            case 3:{
                BalaEstrella* balaEstrella = dynamic_cast<BalaEstrella*>(modelo.jugador2->disparo->balas[i]);
                if (balaEstrella) {
                    vista.dibujarBalasEstrellas(*balaEstrella);
                }
                break;}
            }
        }
    }
    void ejecutar() {
        while (vista.window.isOpen()) {
            auto futureCuphead1 = std::async(std::launch::async,[&] { return vista.procesarEventosPlayer1(); });
            auto futureCuphead2 = std::async(std::launch::async,[&] { return vista.procesarEventosPlayer2(); });
            EventoMouse();
            colisiones();
            colisionesMounstruos();
            int m = futureCuphead1.get();
            int n = futureCuphead2.get();
            manejarEventos(m);
            manejarEventos(n);
            renderizar();
        }  
    }
};
