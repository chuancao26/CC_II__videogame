#ifndef BOSSCREATES_VIEW_H
#define BOSSCREATES_VIEW_H
#include "bosscreates_model.h"
#include <SFML/Graphics.hpp>
#include <iostream> 

class BossViewAnimation {
private:
    bool change;

public:
    BossViewAnimation() : change(false) {}

    // Método plantilla para dibujar la animación
    void drawAnimation(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites, int numStates, float imageChangeInterval) {
        float timeSinceLastImageChange = 0.0f;
        int currentImageIndex = 0;
        sf::Clock timerClock;

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
    
    bool canChange() {
        return change;
    }
};

class NormalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numNormalStates = sprites.size();
        float imageChangeInterval = 0.042f; // Ajustar este valor según sea necesario

        drawAnimation(window, sprites, numNormalStates, imageChangeInterval);
    }
    //~NormalAnimation() {}
};

class CreateObjetosAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numCrearObjetosStates = sprites.size();
        float imageChangeInterval = 0.042f; // Ajustar este valor según sea necesario

        drawAnimation(window, sprites, numCrearObjetosStates, imageChangeInterval);
    }
};

class AtaqueCabezaAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numAtaqueCabezaStates = sprites.size();
        float imageChangeInterval = 0.1f; // Ajustar este valor según sea necesario

        drawAnimation(window, sprites, numAtaqueCabezaStates, imageChangeInterval);
    }
};

class FaseFinalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numFaseFinalStates = sprites.size();
        float imageChangeInterval = 0.05f; // Ajustar este valor según sea necesario

        drawAnimation(window, sprites, numFaseFinalStates, imageChangeInterval);
    }
};

class FormaFinalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numFormaFinalStates = sprites.size();
        float imageChangeInterval = 0.042f; // Ajustar este valor según sea necesario

        drawAnimation(window, sprites, numFormaFinalStates, imageChangeInterval);
    }
};

class BossFinalAnimation : public BossViewAnimation {
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numBossFinalStates = sprites.size();
        float imageChangeInterval = 0.1f; // Ajustar este valor según sea necesario

        drawAnimation(window, sprites, numBossFinalStates, imageChangeInterval);
    }
};

class CrearObjetosBucleAnimation : public BossViewAnimation { // Fix the class name here
public:
    void draw(sf::RenderWindow& window, const std::vector<sf::Sprite>& sprites) {
        int numCrearObjetosBucle = sprites.size();
        float imageChangeInterval = 0.042f; // Ajustar este valor según sea necesario

        drawAnimation(window, sprites, numCrearObjetosBucle, imageChangeInterval);
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

    float timeSinceLastImageChange; // Variable para rastrear el tiempo transcurrido desde el último cambio de imagen
    float imageChangeInterval; // Intervalo deseado para cambiar de imagen (en segundos)
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


        // Cargar las texturas para el ataque de cabeza
        for (int i = 0; i < numInicioAtaque; ++i) {
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

        // Cargar la textura para bossFinal
        if (!bossFinalTexture.loadFromFile("img\\nivel_flor\\faseFinal\\Final_Intro_28.png")) {
            std::cerr << "Error al cargar la textura bossFinal." << std::endl;
        }
        bossFinalSprite.setTexture(bossFinalTexture);
        bossFinalSprite.setScale(window.getSize().x / 3 / bossFinalSprite.getLocalBounds().width,
            ((window.getSize().y * 4) / 5) / bossFinalSprite.getLocalBounds().height);
        bossFinalSprite.setPosition(window_.getSize().x - (bossFinalSprite.getLocalBounds().width) / 1.1,
            window.getSize().y / 12);
        bossFinalTexture.setSmooth(true);


        // Inicializar las animaciones
        NormalAnimation normalAnimation;
        CreateObjetosAnimation createObjetosAnimation;
        CrearObjetosBucleAnimation crearObjetosBucleAnimation;
        AtaqueCabezaAnimation ataqueCabezaAnimation;
        FaseFinalAnimation faseFinalAnimation;
        FormaFinalAnimation formaFinalAnimation;
        BossFinalAnimation bossFinalAnimation;


        // Configurar valores iniciales del temporizador y el intervalo de cambio de imagen
        timerClock.restart();
        timeSinceLastImageChange = 0.0f;
        imageChangeInterval = 0.042f; // Intervalo predeterminado, ajustar según sea necesario
    }

    void draw() {
        // Lógica de dibujo existente...
        // ...

        // Dibujar las animaciones usando la subclase apropiada según el currentState
        if (currentState == 1) {
            normalAnimation.draw(window_, normalSprites);
        } else if (currentState == 2) {
            createObjetosAnimation.draw(window_, crearObjetosSprites);
            if(createObjetosAnimation.canChange()){
                currentState=3;
            }
        } else if (currentState == 3) {
            crearObjetosBucleAnimation.draw(window_, crearObjetosbucleSprites);
        } else if (currentState == 4) {
            ataqueCabezaAnimation.draw(window_, InicioAtaqueSprites);
        } else if (currentState == 5) {
            faseFinalAnimation.draw(window_, finalSprites);
        } else if (currentState == 6) {
            formaFinalAnimation.draw(window_, formaFinalSprites);
        } else if (currentState == 7) {
            //bossFinalAnimation.draw(window_, bossFinalSprite);
        }
        // ...
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
    int getcurrentState() const { // <-- Add 'const' here
        return currentState;
    }
};

#endif
