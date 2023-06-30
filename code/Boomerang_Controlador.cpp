#include "Boomerang_Modelo.cpp"
#include "Boomerang_Vista.cpp"
class BoomerangController {
private:
    BoomerangModel boomerangModel;
    BoomerangView boomerangView;

public:
    BoomerangController(float startX, float startY, float width, float height) :
        boomerangModel(startX, startY, width, height), boomerangView(width, height)
    {
    }

    void update(float windowWidth) {
        boomerangModel.update(windowWidth);
    }

    void draw(sf::RenderWindow& window) {
        float x = boomerangModel.getX();
        float y = boomerangModel.getY();

        boomerangView.updateTexture(x);
        boomerangView.draw(window, x, y);
    }

    bool shouldDelete() const {
        return boomerangModel.shouldDelete();
    }
};
