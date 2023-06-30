#include "Bomba_Modelo.cpp"
#include "Bomba_Vista.cpp"
class BombController {
private:
    std::vector<BombModel> bombs;
    BombView cuadradoView;

public:
    BombController(float ventanaAncho, float ventanaAlto) : bombs(1), cuadradoView(){
        //float elapsedSeconds = 0.0f;
        //elapsedSeconds = clock.getElapsedTime().asSeconds();
        for (int i = 0; i < 1; i++) {
            //if (elapsedSeconds >= interval*i)
            //{
                float posicionX = static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (ventanaAncho * 3 / 5));
                bombs[i] = BombModel(ventanaAncho, ventanaAlto);
                bombs[i].setX(posicionX);
                bombs[i].caer();
            //}
        }
    }

    void update() {
        for (auto& bomb : bombs) {
            bomb.caer();
        }
    }


    void draw(sf::RenderWindow& window) {
        for (const auto& cuadrado : bombs) {
            if (!cuadrado.isEliminado()) {
                cuadradoView.setSize(cuadrado.getSize());
                cuadradoView.setPosition(cuadrado.getX(), cuadrado.getY());

                if (cuadrado.llegoMaximo) {
                    cuadradoView.setTexturePiso();
                } else {
                    cuadradoView.setTextureCae();
                }

                cuadradoView.draw(window);
            }
        }
    }

};