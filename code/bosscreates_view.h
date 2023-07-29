
#ifndef BOSSCREATES_VIEW_H
#define BOSSCREATES_VIEW_H
#include "bosscreates_model.h"
#include <iostream> 


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

public:
    FlorBossView(sf::RenderWindow& window, BossModel& model) : 
    window_(window), model_(model), currentState(1), 
    currentImageIndex(0), numNormalStates(22), numCrearObjetosStates(20),
    numCrearObjetosBucle(16), numInicioAtaque(19),
    numFinalStates(28),numformaFinalStates(19)  {
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
        // Cargamos las texturas para la FORMA final
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

        // Cargamos la textura bossFinal
        if (!bossFinalTexture.loadFromFile("img\\nivel_flor\\faseFinal\\Final_Intro_28.png")) {
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
        imageChangeInterval = 0.042f; 
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
            if (currentImageIndex < numInicioAtaque) {
                window_.draw(InicioAtaqueSprites[currentImageIndex]);
                if (timeSinceLastImageChange >= imageChangeInterval*10) {
                    currentImageIndex++;
                    timeSinceLastImageChange = 0.0f; // Reiniciamos el contador
                }
            } else {
                currentState = 1; // Cambiamos al siguiente estado
                currentImageIndex = 0; // Reiniciamos el índice de imagen
            }
        } else if (currentState == 5) {
            if (currentImageIndex < numFinalStates) {
                window_.draw(finalSprites[currentImageIndex]);
                if (timeSinceLastImageChange >= imageChangeInterval*5) {
                    currentImageIndex++;
                    timeSinceLastImageChange = 0.0f; // Reiniciamos el contador
                }
            } else {
                currentState = 6; // Cambiamos al siguiente estado
                currentImageIndex = 0;
            }
        } else if (currentState == 6) {
            if (currentImageIndex < numformaFinalStates) {
                window_.draw(formaFinalSprites[currentImageIndex]);
                if (timeSinceLastImageChange >= imageChangeInterval) {
                    currentImageIndex++;
                    timeSinceLastImageChange = 0.0f; // Reiniciamos el contador
                }
            } else {
                //currentState = 7; // Cambiamos al siguiente estado
                currentImageIndex = 0;
            }
        } else if (currentState == 7) {
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

#endif