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

class BossViewAnimation {
private:
    bool change;
    int numStates;
    float timeSinceLastImageChange; // Variable para rastrear el tiempo transcurrido desde el último cambio de imagen
    float imageChangeInterval; // Intervalo deseado para cambiar de imagen (en segundos)
    sf::Clock timerClock;
public:
    BossViewAnimation() : change(false) {}

    void drawAnimation(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites, int numStates, float imageChangeInterval) {
    int currentImageIndex = 0;

    while (currentImageIndex < numStates) {
        float deltaTime = timerClock.restart().asSeconds();
        timeSinceLastImageChange += deltaTime;

        if (timeSinceLastImageChange >= imageChangeInterval) {
            window.clear(); // Limpiar el contenido anterior de la ventana
            window.draw(sprites[currentImageIndex]); // Dibujar la imagen actual
            window.display();
            currentImageIndex++;
            timeSinceLastImageChange = 0.0f; // Reiniciar el contador
        }
    }

    change = true;
}

    void setNumStates(int T) {
        numStates = T;
    }

    bool canChange() {
        return change;
    }
};

class NormalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numNormalStates = sprites.size();
        float imageChangeInterval = 0.042f;
        setNumStates(numNormalStates);
        drawAnimation(window, sprites, numNormalStates, imageChangeInterval);
    }
};

class CreateObjetosAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numCrearObjetosStates = sprites.size();
        float imageChangeInterval = 0.042f;
        setNumStates(numCrearObjetosStates);
        drawAnimation(window, sprites, numCrearObjetosStates, imageChangeInterval);
    }
};

class AtaqueCabezaAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numAtaqueCabezaStates = sprites.size();
        float imageChangeInterval = 0.1f;
        setNumStates(numAtaqueCabezaStates);
        drawAnimation(window, sprites, numAtaqueCabezaStates, imageChangeInterval);
    }
};

class FaseFinalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numFaseFinalStates = sprites.size();
        float imageChangeInterval = 0.05f;
        setNumStates(numFaseFinalStates);
        drawAnimation(window, sprites, numFaseFinalStates, imageChangeInterval);
    }
};

class FormaFinalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numFormaFinalStates = sprites.size();
        float imageChangeInterval = 0.042f;
        setNumStates(numFormaFinalStates);
        drawAnimation(window, sprites, numFormaFinalStates, imageChangeInterval);
    }
};

class BossFinalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const sf::Sprite& sprite) {
        // Esta función solo dibuja un sprite individual, no necesita un vector
        window.draw(sprite);
    }
};


class CrearObjetosBucleAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numCrearObjetosBucle = sprites.size();
        float imageChangeInterval = 0.042f;

        drawAnimation(window, sprites, numCrearObjetosBucle, imageChangeInterval);
    }
};

class FlorBossView {
public:
    sf::RenderWindow& window_;
    std::vector<sf::Texture> normalTextures;
    std::vector<sf::Sprite> normalSprites;
    std::vector<sf::Texture> crearObjetosTextures;
    std::vector<sf::Sprite> crearObjetosSprites;
    std::vector<sf::Texture> crearObjetosbucleTextures;
    std::vector<sf::Sprite> crearObjetosbucleSprites;
    std::vector<sf::Texture> InicioAtaqueTextures;
    std::vector<sf::Sprite> InicioAtaqueSprites;
    std::vector<sf::Texture> finalTextures;
    std::vector<sf::Sprite> finalSprites;
    std::vector<sf::Texture> formaFinalTextures;
    std::vector<sf::Sprite> formaFinalSprites;
    sf::Texture bossFinalTexture;
    sf::Sprite bossFinalSprite;
    int numNormalStates;
    int numCrearObjetosStates;
    int numCrearObjetosBucle;
    int numInicioAtaque;
    int numFinalStates;
    int numformaFinalStates;
    int currentState;
    int currentImageIndex;
    BossModel& model_;

    float timeSinceLastImageChange;
    float imageChangeInterval;
    sf::Clock timerClock;

    NormalAnimation normalAnimation;
    CreateObjetosAnimation createObjetosAnimation;
    AtaqueCabezaAnimation ataqueCabezaAnimation;
    FaseFinalAnimation faseFinalAnimation;
    FormaFinalAnimation formaFinalAnimation;
    BossFinalAnimation bossFinalAnimation;
    CrearObjetosBucleAnimation crearObjetosBucleAnimation;


public:
    FlorBossView(sf::RenderWindow& window, BossModel& model) :
        window_(window), model_(model), currentState(2),
        currentImageIndex(0), numNormalStates(22), numCrearObjetosStates(20),
        numCrearObjetosBucle(16), numInicioAtaque(19),
        numFinalStates(28), numformaFinalStates(19) {

        // Cargar texturas y configurar sprites
        normalTextures.resize(numNormalStates);
        normalSprites.resize(numNormalStates);

        crearObjetosTextures.resize(numCrearObjetosStates);
        crearObjetosSprites.resize(numCrearObjetosStates);

        crearObjetosbucleTextures.resize(numCrearObjetosBucle);
        crearObjetosbucleSprites.resize(numCrearObjetosBucle);

        InicioAtaqueTextures.resize(numInicioAtaque);
        InicioAtaqueSprites.resize(numInicioAtaque);

        finalTextures.resize(numFinalStates);
        finalSprites.resize(numFinalStates);

        formaFinalTextures.resize(numformaFinalStates);
        formaFinalSprites.resize(numformaFinalStates);

        // Cargar las texturas normales
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

        // Cargar las texturas para crearObjetos
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

        // Cargar las texturas para crearObjetos en bucle
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

        //Ataque cabeza inicio
        for (int i = 0; i < 9; ++i) {
            if (!InicioAtaqueTextures[i].loadFromFile("img\\nivel_flor\\ataqueCabeza\\FA_High_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado crearObjetos" << i + 1 << std::endl;
            }
            InicioAtaqueSprites[i].setTexture(InicioAtaqueTextures[i]);
            InicioAtaqueSprites[i].setScale(window.getSize().x / 3 / InicioAtaqueSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / InicioAtaqueSprites[i].getLocalBounds().height);
            InicioAtaqueSprites[i].setPosition(window_.getSize().x - (InicioAtaqueSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            InicioAtaqueTextures[i].setSmooth(true);
        }
        for (int i = 9; i <10; ++i) {
            if (!InicioAtaqueTextures[i].loadFromFile("img\\nivel_flor\\ataqueCabeza\\FA_High_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado crearObjetos" << i + 1 << std::endl;
            }
            InicioAtaqueSprites[i].setTexture(InicioAtaqueTextures[i]);
            InicioAtaqueSprites[i].setScale(window.getSize().x / 2 / InicioAtaqueSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / InicioAtaqueSprites[i].getLocalBounds().height);
            InicioAtaqueSprites[i].setPosition(window_.getSize().x - (InicioAtaqueSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            InicioAtaqueTextures[i].setSmooth(true);
        }
        for (int i = 10; i < 16; ++i) {
            if (!InicioAtaqueTextures[i].loadFromFile("img\\nivel_flor\\ataqueCabeza\\FA_High_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado crearObjetos" << i + 1 << std::endl;
            }
            InicioAtaqueSprites[i].setTexture(InicioAtaqueTextures[i]);
            InicioAtaqueSprites[i].setScale(window.getSize().x / InicioAtaqueSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / InicioAtaqueSprites[i].getLocalBounds().height);
            InicioAtaqueSprites[i].setPosition(window_.getSize().x - (InicioAtaqueSprites[i].getLocalBounds().width)*9/8,
                window.getSize().y / 12);
            InicioAtaqueTextures[i].setSmooth(true);
        }
        for (int i = 16; i <17; ++i) {
            if (!InicioAtaqueTextures[i].loadFromFile("img\\nivel_flor\\ataqueCabeza\\FA_High_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado crearObjetos" << i + 1 << std::endl;
            }
            InicioAtaqueSprites[i].setTexture(InicioAtaqueTextures[i]);
            InicioAtaqueSprites[i].setScale(window.getSize().x / 2 / InicioAtaqueSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / InicioAtaqueSprites[i].getLocalBounds().height);
            InicioAtaqueSprites[i].setPosition(window_.getSize().x - (InicioAtaqueSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            InicioAtaqueTextures[i].setSmooth(true);
        }
        for (int i = 17; i < numInicioAtaque; ++i) {
            if (!InicioAtaqueTextures[i].loadFromFile("img\\nivel_flor\\ataqueCabeza\\FA_High_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado crearObjetos" << i + 1 << std::endl;
            }
            InicioAtaqueSprites[i].setTexture(InicioAtaqueTextures[i]);
            InicioAtaqueSprites[i].setScale(window.getSize().x / 3 / InicioAtaqueSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / InicioAtaqueSprites[i].getLocalBounds().height);
            InicioAtaqueSprites[i].setPosition(window_.getSize().x - (InicioAtaqueSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            InicioAtaqueTextures[i].setSmooth(true);
        }

        // Cargar las texturas para la fase final
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

        // Cargar las texturas para la forma final
        for (int i = 0; i < numformaFinalStates; ++i) {
            if (!formaFinalTextures[i].loadFromFile("img\\nivel_flor\\formaFinal\\Final_Idle_" + std::to_string(i + 1) + ".png")) {
                std::cerr << "Error al cargar la textura para el estado final" << i + 1 << std::endl;
            }
            formaFinalSprites[i].setTexture(formaFinalTextures[i]);
            formaFinalSprites[i].setScale(window.getSize().x / 3 / formaFinalSprites[i].getLocalBounds().width,
                ((window.getSize().y * 4) / 5) / formaFinalSprites[i].getLocalBounds().height);
            formaFinalSprites[i].setPosition(window_.getSize().x - (formaFinalSprites[i].getLocalBounds().width) / 1.1,
                window.getSize().y / 12);
            formaFinalTextures[i].setSmooth(true);
        }

        // Cargar la textura para el boss final
        if (!bossFinalTexture.loadFromFile("img\\nivel_flor\\BossFinal.png")) {
            std::cerr << "Error al cargar la textura para el boss final" << std::endl;
        }
        bossFinalSprite.setTexture(bossFinalTexture);
        bossFinalSprite.setScale(window.getSize().x / 3 / bossFinalSprite.getLocalBounds().width,
            ((window.getSize().y * 4) / 5) / bossFinalSprite.getLocalBounds().height);
        bossFinalSprite.setPosition(window_.getSize().x - (bossFinalSprite.getLocalBounds().width) / 1.1,
            window.getSize().y / 12);
        bossFinalTexture.setSmooth(true);

        currentState = 0;
        timeSinceLastImageChange = 0.0f;
        imageChangeInterval = 0.042f;
    }

    void update(float deltaTime) {
        // Si el jefe está en estado 1 (atacando) y no se está agrandando, entonces inicia la animación de agrandar
        if (model_.getState() == 1 && !model_.isGrowing()) {
            model_.startGrowing();
        }

        // Si el jefe está en estado 0 (no atacando) y se está agrandando, entonces detiene la animación de agrandar
        if (model_.getState() == 0 && model_.isGrowing()) {
            model_.stopGrowing();
        }

        // Actualizar la animación del jefe dependiendo del estado actual
        switch (currentState) {
        case 0:
            normalAnimation.draw(window_, normalSprites);
            if (normalAnimation.canChange()) {
                currentState++;
            }
            break;
        case 1:
            createObjetosAnimation.draw(window_, crearObjetosSprites);
            if (createObjetosAnimation.canChange()) {
                currentState++;
            }
            break;
        case 2:
            crearObjetosBucleAnimation.draw(window_, crearObjetosbucleSprites);
            if (crearObjetosBucleAnimation.canChange()) {
                currentState++;
            }
            break;
        case 3:
            ataqueCabezaAnimation.draw(window_, InicioAtaqueSprites);
            if (ataqueCabezaAnimation.canChange()) {
                currentState++;
            }
            break;
        case 4:
            faseFinalAnimation.draw(window_, finalSprites);
            if (faseFinalAnimation.canChange()) {
                currentState++;
            }
            break;
        case 5:
            formaFinalAnimation.draw(window_, formaFinalSprites);
            if (formaFinalAnimation.canChange()) {
                currentState++;
            }
            break;
        case 6:
            bossFinalAnimation.draw(window_, bossFinalSprite);
            if (bossFinalAnimation.canChange()) {
                currentState++;
            }
            break;

        default:
            break;
        }
    }
    void draw() {
        // Lógica de dibujo existente...
        // ...

        // Dibujar las animaciones usando la subclase apropiada según el currentState
        if (currentState == 1) {
            normalAnimation.draw(window_, normalSprites);
        } else if (currentState == 2) {
            createObjetosAnimation.draw(window_, crearObjetosSprites);
        } else if (currentState == 3) {
            crearObjetosBucleAnimation.draw(window_, crearObjetosbucleSprites);
        } else if (currentState == 4) {
            ataqueCabezaAnimation.draw(window_, InicioAtaqueSprites);
        } else if (currentState == 5) {
            faseFinalAnimation.draw(window_, finalSprites);
        } else if (currentState == 6) {
            formaFinalAnimation.draw(window_, formaFinalSprites);
        } else if (currentState == 7) {
            bossFinalAnimation.draw(window_, bossFinalSprite);
        }
        // ...
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
        view_.update(deltaTime);
    }

    void draw() {
        view_.draw();
    }

    void setState(int state) {
        view_.setStateAndImageIndex(state, 0); // Cambiamos la llamada a setStateAndImageIndex
    }
    
    
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Flor Boss Animation");
    window.setFramerateLimit(60);

    BossController bossController(window);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();
        bossController.update(deltaTime);

        window.clear(sf::Color::White);
        bossController.draw();
        window.display();
    }

    return 0;
}