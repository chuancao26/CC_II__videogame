/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//BossView
class FlorBoss {
private:
    sf::RenderWindow& window_;
    sf::Texture normal1T;
    sf::Texture normal2T;
    sf::Sprite spriteN1;
    sf::Sprite spriteN2;
    int state;
    float timer_;
    float duration_;
    float growthTimer_;
    float growthDuration_;
public:
    FlorBoss(sf::RenderWindow& window) : window_(window) {
        if ((!normal1T.loadFromFile("normal1.png"))||(!normal2T.loadFromFile("normal2.png"))) {
            // Error al cargar la imagen normal1.png
            std::cerr << "Error al cargar las texturas." << std::endl;
        }
        spriteN1.setTexture(normal1T);
        spriteN2.setTexture(normal2T);

        spriteN1.setScale(window.getSize().x / 3 / spriteN1.getLocalBounds().width,
                              ((window.getSize().y * 4) / 5) / spriteN1.getLocalBounds().height);
        spriteN2.setScale(window.getSize().x / 3 / spriteN2.getLocalBounds().width,
                               ((window.getSize().y * 4) / 5) / spriteN2.getLocalBounds().height);

        spriteN1.setPosition(window_.getSize().x - (spriteN1.getLocalBounds().width)/1.1,
                                 window.getSize().y / 12);
        spriteN2.setPosition(window_.getSize().x - (spriteN2.getLocalBounds().width)/1.1,
                                  window.getSize().y / 12);
        normal1T.setSmooth(true);
        normal2T.setSmooth(true);
        state = 1;
        timer_ = 0.0f;
        duration_ = 0.5f;
        growthTimer_ = 0.0f;
        growthDuration_ = 2.0f;
    }

    void update(float deltaTime) {
        timer_ += deltaTime;
        growthTimer_ += deltaTime;

        if (timer_ >= duration_) {
            if(state == 1){
                state = 0;
            }
            else if(state == 0){
                state = 1;
            }
            timer_ = 0.0f;
        }
    }

    void draw() {
        if (state==1) {
            window_.draw(spriteN1);
        } else if (state==0) {
            window_.draw(spriteN2);
        }
    }
    void removeRectangles() {
        spriteN1.setScale(0.0f, 0.0f);
        spriteN2.setScale(0.0f, 0.0f);
    }
};


//FondoView
class Background {
public:
    Background(sf::RenderWindow& window) : window_(window) {
        if (!texture_.loadFromFile("fondoFlor.png")) {
            // Error al cargar la imagen fondoFlor.png
            return;
        }

        sprite_.setTexture(texture_);

        // Escala la imagen para que encaje con el tama�o de la ventana
        float scaleX = static_cast<float>(window.getSize().x) / sprite_.getLocalBounds().width;
        float scaleY = static_cast<float>(window.getSize().y) / sprite_.getLocalBounds().height;
        sprite_.setScale(scaleX, scaleY);
    }

    void draw() {
        window_.draw(sprite_);
    }

private:
    sf::RenderWindow& window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrados");
    window.setFramerateLimit(60);
   
    FlorBoss florBoss(window); //Crear view del Boss
    sf::Clock clock2;

    Background background(window); //Fondo del juego "Cagney Carnation"

    sf::Clock clockSeed;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calcular el tiempo transcurrido desde la última aparición de un cuadrado

        float deltaTime2 = clock2.restart().asSeconds();
        florBoss.update(deltaTime2);

//WIDOW CLEAR
        window.clear(sf::Color::White);
        background.draw();
        
        florBoss.draw();
      
        window.display();
    
    }

    // Liberar la memoria de los CuadradoController creados
    //for (int i = 0; i < 1; i++) {
    //    delete florBoss[i];
    //}
    
    return 0;
}
*/
/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Boss Model
class BossModel {
private:
    int state;
    float timer_;
    float duration_;
    bool isGrowing_;
    float growthTimer_;
    float growthDuration_;

public:
    BossModel() : state(1), timer_(0.0f), duration_(0.5f), isGrowing_(false), growthTimer_(0.0f), growthDuration_(2.0f) {}

    void update(float deltaTime) {
        timer_ += deltaTime;
        growthTimer_ += deltaTime;

        if (timer_ >= duration_) {
            if (state == 1) {
                state = 0;
            } else if (state == 0) {
                state = 1;
            }
            timer_ = 0.0f;
        }
    }

    void startGrowing() {
        if (!isGrowing_) {
            isGrowing_ = true;
            growthTimer_ = 0.0f;
        }
    }

    bool isGrowing() const {
        return isGrowing_;
    }

    void stopGrowing() {
        isGrowing_ = false;
    }

    int getState() const {
        return state;
    }
};

// Boss View
class FlorBossView {
private:
    sf::RenderWindow& window_;
    sf::Texture normal1T;
    sf::Texture normal2T;
    sf::Sprite spriteN1;
    sf::Sprite spriteN2;
    sf::RectangleShape rectThird_;

public:
    FlorBossView(sf::RenderWindow& window) : window_(window) {
                if ((!normal1T.loadFromFile("normal1.png"))||(!normal2T.loadFromFile("normal2.png"))) {
            // Error al cargar la imagen normal1.png
            std::cerr << "Error al cargar las texturas." << std::endl;
        }
        spriteN1.setTexture(normal1T);
        spriteN2.setTexture(normal2T);

        spriteN1.setScale(window.getSize().x / 3 / spriteN1.getLocalBounds().width,
                              ((window.getSize().y * 4) / 5) / spriteN1.getLocalBounds().height);
        spriteN2.setScale(window.getSize().x / 3 / spriteN2.getLocalBounds().width,
                               ((window.getSize().y * 4) / 5) / spriteN2.getLocalBounds().height);

        spriteN1.setPosition(window_.getSize().x - (spriteN1.getLocalBounds().width)/1.1,
                                 window.getSize().y / 12);
        spriteN2.setPosition(window_.getSize().x - (spriteN2.getLocalBounds().width)/1.1,
                                  window.getSize().y / 12);
        normal1T.setSmooth(true);
        normal2T.setSmooth(true);

    }

    void draw(int state) {
        if (state == 1) {
            window_.draw(spriteN1);
        } else if (state == 0) {
            window_.draw(spriteN2);
        }
        window_.draw(rectThird_);
    }

    void removeRectangles() {
        spriteN1.setScale(0.0f, 0.0f);
        spriteN2.setScale(0.0f, 0.0f);
        rectThird_.setSize(sf::Vector2f(0.0f, 0.0f));
    }

    void startGrowing() {
        // (Remain unchanged, this is a view method)
    }
};

// Boss Controller
class BossController {
private:
    BossModel model_;
    FlorBossView view_;
    sf::Clock clock2;

public:
    BossController(BossModel& model, FlorBossView& view) : model_(model), view_(view) {

    }

    void update() {
        float deltaTime2 = clock2.restart().asSeconds();
        model_.update(deltaTime2);

        if (model_.isGrowing()) {
            // Update the view to start growing animation
            view_.startGrowing();

            if (model_.getState() == 1) {
                view_.draw(model_.getState());
            } else if (model_.getState() == 0) {
                view_.draw(model_.getState());
            }
        } else {
            // Perform any other actions when not growing
        }
    }

    void draw() {
        view_.draw(model_.getState());
    }
};

// ... Rest of the code remains unchanged ...
class Background {
public:
    Background(sf::RenderWindow& window) : window_(window) {
        if (!texture_.loadFromFile("fondoFlor.png")) {
            // Error al cargar la imagen fondoFlor.png
            return;
        }

        sprite_.setTexture(texture_);

        // Escala la imagen para que encaje con el tama�o de la ventana
        float scaleX = static_cast<float>(window.getSize().x) / sprite_.getLocalBounds().width;
        float scaleY = static_cast<float>(window.getSize().y) / sprite_.getLocalBounds().height;
        sprite_.setScale(scaleX, scaleY);
    }

    void draw() {
        window_.draw(sprite_);
    }

private:
    sf::RenderWindow& window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrados");
    window.setFramerateLimit(60);

    BossModel bossModel; // Model
    FlorBossView florBossView(window); // View
    BossController bossController(bossModel, florBossView); // Controller

    Background background(window);

    sf::Clock clockSeed;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        bossController.update();
        
        window.clear(sf::Color::White);
        //background.draw();

        bossController.draw();

        window.display();
    }

    return 0;
}
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Boss Model
class BossModel {
private:
    int state;
    float timer_;
    float duration_;
    bool isGrowing_;
    float growthTimer_;
    float growthDuration_;

public:
    BossModel() : state(1), timer_(0.0f), duration_(0.5f), isGrowing_(false), growthTimer_(0.0f), growthDuration_(2.0f) {}

    void update(float deltaTime) {
        timer_ += deltaTime;
        growthTimer_ += deltaTime;

        if (timer_ >= duration_) {
            if (state == 1) {
                state = 0;
            } else if (state == 0) {
                state = 1;
            }
            timer_ = 0.0f;
        }
    }

    void startGrowing() {
        if (!isGrowing_) {
            isGrowing_ = true;
            growthTimer_ = 0.0f;
        }
    }

    bool isGrowing() const {
        return isGrowing_;
    }

    void stopGrowing() {
        isGrowing_ = false;
    }

    int getState() const {
        return state;
    }
};

// Boss View
class FlorBossView {
private:
    sf::RenderWindow& window_;
    sf::Texture normal1T;
    sf::Texture normal2T;
    sf::Sprite spriteN1;
    sf::Sprite spriteN2;
    sf::RectangleShape rectThird_;

public:
    FlorBossView(sf::RenderWindow& window) : window_(window) {
        if ((!normal1T.loadFromFile("normal1.png")) || (!normal2T.loadFromFile("normal2.png"))) {
            // Error al cargar las texturas.
            std::cerr << "Error al cargar las texturas." << std::endl;
        }
        spriteN1.setTexture(normal1T);
        spriteN2.setTexture(normal2T);

        spriteN1.setScale(window.getSize().x / 3 / spriteN1.getLocalBounds().width,
                          ((window.getSize().y * 4) / 5) / spriteN1.getLocalBounds().height);
        spriteN2.setScale(window.getSize().x / 3 / spriteN2.getLocalBounds().width,
                          ((window.getSize().y * 4) / 5) / spriteN2.getLocalBounds().height);

        spriteN1.setPosition(window_.getSize().x - (spriteN1.getLocalBounds().width) / 1.1,
                             window.getSize().y / 12);
        spriteN2.setPosition(window_.getSize().x - (spriteN2.getLocalBounds().width) / 1.1,
                             window.getSize().y / 12);
        normal1T.setSmooth(true);
        normal2T.setSmooth(true);
    }

    void draw(int state) {
        if (state == 1) {
            window_.draw(spriteN1);
        } else if (state == 0) {
            window_.draw(spriteN2);
        }
        window_.draw(rectThird_);
    }

    void removeRectangles() {
        spriteN1.setScale(0.0f, 0.0f);
        spriteN2.setScale(0.0f, 0.0f);
        rectThird_.setSize(sf::Vector2f(0.0f, 0.0f));
    }

    void startGrowing() {
        // (Remain unchanged, this is a view method)
    }
};

// Boss Controller
class BossController {
private:
    BossModel model_;
    FlorBossView view_;
    sf::Clock clock2;

public:
    BossController(sf::RenderWindow& window) : view_(window) {}

    void update() {
        float deltaTime2 = clock2.restart().asSeconds();
        model_.update(deltaTime2);

        if (model_.isGrowing()) {
            // Update the view to start growing animation
            view_.startGrowing();
        }
    }

    void draw() {
        view_.draw(model_.getState());
    }
};

class Background {
public:
    Background(sf::RenderWindow& window) : window_(window) {
        if (!texture_.loadFromFile("fondoFlor.png")) {
            // Error al cargar la imagen fondoFlor.png
            return;
        }

        sprite_.setTexture(texture_);

        // Escala la imagen para que encaje con el tamaño de la ventana
        float scaleX = static_cast<float>(window.getSize().x) / sprite_.getLocalBounds().width;
        float scaleY = static_cast<float>(window.getSize().y) / sprite_.getLocalBounds().height;
        sprite_.setScale(scaleX, scaleY);
    }

    void draw() {
        window_.draw(sprite_);
    }

private:
    sf::RenderWindow& window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cuadrados");
    window.setFramerateLimit(60);

    BossController bossController(window); // Controller

    Background background(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        bossController.update();

        window.clear(sf::Color::White);
        background.draw();
        bossController.draw();
        window.display();
    }

    return 0;
}
