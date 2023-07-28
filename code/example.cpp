#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class BossModel {
private:
    int state;
    int currentImageIndex;
    float timer_;
    float duration_;
    bool isGrowing_;
    float growthTimer_;
    float growthDuration_;

public:
    BossModel() : state(1), currentImageIndex(0), timer_(0.0f), duration_(0.2f), isGrowing_(false), growthTimer_(0.0f), growthDuration_(0.042f) {}

    void update(float deltaTime) {
        timer_ += deltaTime;
        growthTimer_ += deltaTime;

        if (timer_ >= duration_) {
            if (state == 1) {
                state = 0;
            } else if (state == 0) {
                state = 1;
            }
            currentImageIndex = 0;
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

    int getCurrentImageIndex() const {
        return currentImageIndex;
    }

    void incrementImageIndex() {
        currentImageIndex++;
    }
    
};

class FlorBossView {
private:
    sf::RenderWindow& window_;
    std::vector<sf::Texture> normalTextures;
    std::vector<sf::Sprite> normalSprites;
    std::vector<sf::Texture> crearObjetosTextures;
    std::vector<sf::Sprite> crearObjetosSprites;
    std::vector<sf::Texture> crearObjetosbucleTextures;
    std::vector<sf::Sprite> crearObjetosbucleSprites;
    std::vector<sf::Texture> finalTextures;
    std::vector<sf::Sprite> finalSprites;
    sf::Texture bossFinalTexture;
    sf::Sprite bossFinalSprite;
    int numNormalStates;
    int numCrearObjetosStates;
    int numCrearObjetosBucle;
    int numFinalStates;
    int currentState;
    int currentImageIndex;
    BossModel& model_;

    float timeSinceLastImageChange; // Variable para rastrear el tiempo transcurrido desde el último cambio de imagen
    float imageChangeInterval; // Intervalo deseado para cambiar de imagen (en segundos)
    sf::Clock timerClock;

public:
    FlorBossView(sf::RenderWindow& window, BossModel& model) : 
    window_(window), model_(model), currentState(1), 
    currentImageIndex(0), numNormalStates(22), numCrearObjetosStates(20),
    numCrearObjetosBucle(16),
    numFinalStates(4) {
        normalTextures.resize(numNormalStates);
        normalSprites.resize(numNormalStates);

        crearObjetosTextures.resize(numCrearObjetosStates);
        crearObjetosSprites.resize(numCrearObjetosStates);

        crearObjetosbucleTextures.resize(numCrearObjetosBucle);
        crearObjetosbucleSprites.resize(numCrearObjetosBucle);

        finalTextures.resize(numFinalStates);
        finalSprites.resize(numFinalStates);

        // Cargamos las texturas normales
        for (int i = 0; i < numNormalStates; ++i) {
            if (!normalTextures[i].loadFromFile("img\\nivel_flor\\normal\\Idle_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado normal" << i + 1 << std::endl;
            }
            normalSprites[i].setTexture(normalTextures[i]);
            normalSprites[i].setScale(window.getSize().x / 3 / normalSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / normalSprites[i].getLocalBounds().height);
            normalSprites[i].setPosition(window_.getSize().x - (normalSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            normalTextures[i].setSmooth(true);
        }

        // Cargamos las texturas para crearObjetos
        for (int i = 0; i < numCrearObjetosStates; ++i) {
            if (!crearObjetosTextures[i].loadFromFile("img\\nivel_flor\\crearObjetos\\Create_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado crearObjetos" << i + 1 << std::endl;
            }
            crearObjetosSprites[i].setTexture(crearObjetosTextures[i]);
            crearObjetosSprites[i].setScale(window.getSize().x / 3 / crearObjetosSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / crearObjetosSprites[i].getLocalBounds().height);
            crearObjetosSprites[i].setPosition(window_.getSize().x - (crearObjetosSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            crearObjetosTextures[i].setSmooth(true);
        }
        //crearObjetos en bucle
        for (int i = 0; i < numCrearObjetosBucle; ++i) {
            if (!crearObjetosbucleTextures[i].loadFromFile("img\\nivel_flor\\crearObjetos\\bucle\\Create_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado crearObjetos" << i + 1 << std::endl;
            }
            crearObjetosbucleSprites[i].setTexture(crearObjetosbucleTextures[i]);
            crearObjetosbucleSprites[i].setScale(window.getSize().x / 3 / crearObjetosbucleSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / crearObjetosbucleSprites[i].getLocalBounds().height);
            crearObjetosbucleSprites[i].setPosition(window_.getSize().x - (crearObjetosbucleSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            crearObjetosbucleTextures[i].setSmooth(true);
        }

        // Cargamos las texturas para final
        for (int i = 0; i < numFinalStates; ++i) {
            if (!finalTextures[i].loadFromFile("img\\nivel_flor\\faseFinal\\Final_Intro_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado final" << i + 1 << std::endl;
            }
            finalSprites[i].setTexture(finalTextures[i]);
            finalSprites[i].setScale(window.getSize().x / 3 / finalSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / finalSprites[i].getLocalBounds().height);
            finalSprites[i].setPosition(window_.getSize().x - (finalSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            finalTextures[i].setSmooth(true);
        }

        // Cargamos la textura bossFinal
        if (!bossFinalTexture.loadFromFile("img\\nivel_flor\\bossFinal.png")) {
            std::cerr << "Error al cargar la textura bossFinal." << std::endl;
        }
        bossFinalSprite.setTexture(bossFinalTexture);
        bossFinalSprite.setScale(window.getSize().x / 3 / bossFinalSprite.getLocalBounds().width,
            ((window.getSize().y * 4) / 5) / bossFinalSprite.getLocalBounds().height);
        bossFinalSprite.setPosition(window_.getSize().x - (bossFinalSprite.getLocalBounds().width) / 1.1,
            window.getSize().y / 12);
        bossFinalTexture.setSmooth(true);

        timerClock.restart();

        timeSinceLastImageChange = 0.0f;
        imageChangeInterval = 0.048f; // Cambiar la imagen cada cuarto de segundo (0.25 segundos)
        //imageChangeInterval = 1.25f;
    }

    void draw() {
        timeSinceLastImageChange += timerClock.restart().asSeconds();

        if (currentState == 1) {
            if (currentImageIndex < numNormalStates) {
                window_.draw(normalSprites[currentImageIndex]);
                if (timeSinceLastImageChange >= imageChangeInterval) {
                    currentImageIndex++;
                    timeSinceLastImageChange = 0.0f; // Reiniciamos el contador
                }
            } else {
                //currentState = 2; // Cambiamos al siguiente estado
                currentImageIndex = 0; // Reiniciamos el índice de imagen
            }
        } else if (currentState == 2) {
            if (currentImageIndex < numCrearObjetosStates) {
                window_.draw(crearObjetosSprites[currentImageIndex]);
                if (timeSinceLastImageChange >= imageChangeInterval) {
                    currentImageIndex++;
                    timeSinceLastImageChange = 0.0f; // Reiniciamos el contador
                }
            } else {
                currentState = 3; // Cambiamos al siguiente estado
                currentImageIndex = 0; // Reiniciamos el índice de imagen
            }
        } else if (currentState == 3) {
            if (currentImageIndex < numCrearObjetosBucle) {
                window_.draw(crearObjetosbucleSprites[currentImageIndex]);
                if (timeSinceLastImageChange >= imageChangeInterval) {
                    currentImageIndex++;
                    timeSinceLastImageChange = 0.0f; // Reiniciamos el contador
                }
            } else {
                //currentState = 4; // Cambiamos al siguiente estado
                currentImageIndex = 0; // Reiniciamos el índice de imagen
            }
        } else if (currentState == 4) {
            if (currentImageIndex < numFinalStates) {
                window_.draw(finalSprites[currentImageIndex]);
                if (timeSinceLastImageChange >= imageChangeInterval) {
                    currentImageIndex++;
                    timeSinceLastImageChange = 0.0f; // Reiniciamos el contador
                }
            } else {
                //currentState = 4; // Cambiamos al siguiente estado
            }
        } else if (currentState == 5) {
            // Dibujamos la imagen final sin cambiar más
            window_.draw(bossFinalSprite);
        }
    }

    void setcurrentState(int s){
        currentState=s;
    }
    int getcurrentState(){
        return currentState;
    }
    void setimageChangeInterval(float time){
        imageChangeInterval=time;
    }

    void removeRectangles() {
        for (int i = 0; i < numNormalStates; ++i) {
            normalSprites[i].setScale(0.0f, 0.0f);
        }
        bossFinalSprite.setScale(0.0f, 0.0f);
    }

    void startGrowing() {
        // Cambiamos entre los estados 1 y 2
        if (model_.isGrowing()) {
            currentState = currentState == 1 ? 2 : 1;
            model_.incrementImageIndex();
            timerClock.restart();
            timeSinceLastImageChange = 0.0f; // Reiniciamos el contador cuando cambia de estado
        }
    }

    sf::Time getElapsedTime() const {
        return timerClock.getElapsedTime();
    }
    void setStateAndImageIndex(int newState, int newImageIndex) {
        currentState = newState;
        currentImageIndex = newImageIndex;
    }
};
class BossController {
private:
    BossModel model_;
    FlorBossView view_;

public:
    BossController(sf::RenderWindow& window) : view_(window, model_) {}

    void update(float deltaTime) {
        model_.update(deltaTime);

        if (model_.isGrowing()) {
            view_.startGrowing();
        }
    }

    void draw() {
        view_.draw();
    }

    void setState(int state) {
        view_.setcurrentState(state);
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Boss Creates Game");
    BossController bossController(window);


    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //bossController.state(2);
        float deltaTime = 0.042f;
        bossController.update(deltaTime);

        window.clear(); // Limpiar el contenido anterior de la ventana

        bossController.draw();

        window.display();

        // Pausa para reducir la velocidad de actualización
        //sf::sleep(sf::milliseconds(100)); // Ajusta el valor para cambiar la velocidad de actualización
    }

    return 0;
}