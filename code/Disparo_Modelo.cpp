#ifndef DISPARO_MODELO_H
#define DISPARO_MODELO_H
#include "Bala.cpp"
#include <iostream>

class Disparo {
    public:
        Bala** balas;
        int size;

    public:
        virtual void disparar(const float& x,const float& y) = 0;

        Disparo() : size(0), balas(nullptr) {}

        virtual ~Disparo() {
            for (int i = 0; i < size; i++) {
                delete balas[i];
            }
            delete[] balas;
        }
};

class DisparoNormal : public Disparo { 
    public:
        void disparar(const float& x,const float& y) override {
            size = 1;
            balas = new Bala*[size];
            balas[0] = new BalaNormal();
            balas[0]->setPosx(x);
            balas[0]->setPosy(y);
        }
};

class DisparoBomba : public Disparo {
    public:
        void disparar(const float& x, const float& y) override {
            size = 1;
            balas = new Bala*[size];
            balas[0] = new BalaBomba();
            balas[0]->setPosx(x);
            balas[0]->setPosy(y);
        }
};

class DisparoEstrella : public Disparo {
    public:
        void disparar(const float& x,const  float& y) override {
            size = 3;
            balas = new Bala*[size];
            for (int i = 0; i < size; i++) {
                balas[i] = new BalaEstrella();
                balas[i]->setPosx(x);
                balas[i]->setPosy(y);
            }
        }
};

#endif