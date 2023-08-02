#ifndef BALA_MODELO_H
#define BALA_MODELO_H
class Bala {
    public:
        Bala():size(60.0f), height(720), width(1280){};
        virtual void setPosx(float px)
        {
            posx=px;
        }
        virtual void setPosy(float py)
        {
            posy=py;
        }
        virtual float getPosx()
        {
            return posx;
        }
        virtual float getPosy()
        {
            return posy;
        }
        virtual void setSize(float s)
        {
            size=s;
        }
        virtual float getSize()
        {
            return size;
        }
        bool isExpired()
        {
            return (posx >= width) ? true:false;
        }
        virtual void mover() = 0;
        virtual void mover(float px, float py) {
        setPosx(getPosx() + px);
        setPosy(getPosy() - py);
    }
    private:
        float posx,posy,direccion,size;
        int height, width;
};

class BalaNormal : public Bala {
public:
    void mover() override {
        
        setPosx(getPosx()+20.0);
    }
};

class BalaBomba : public Bala {
public:
    void mover() override {
        
        setPosx(getPosx()+20.0);

        setSize(getSize()+20.0);
        setPosy(getPosy()-5.0f);
    }
};

class BalaEstrella : public Bala {
public:
    void mover() override {
        
        setPosx(getPosx()+20.0);
        setPosy(getPosy()-20.0);
        
    }
    void mover(float px, float py) override{
        
        setPosx(getPosx()+px);
        setPosy(getPosy()-py);
        
    }
};
#endif