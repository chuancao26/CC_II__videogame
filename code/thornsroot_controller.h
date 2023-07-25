#ifndef THORNSROOT_CONTROLLER_H
#define THORNSROOT_CONTROLLER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "thornsroot_model.h"
#include "thornsroot_view.h"

class ThornsRootController {
private:
    sf::RenderWindow& window;
    ThornsRootModel model;
    ThornsRootView view;
    sf::Clock clock;
    sf::Clock clock1;
    bool isShowingImages; // To control when to show images and when to show the animation

public:
    ThornsRootController(sf::RenderWindow& window) : window(window), view(window) {
        isShowingImages = true; // Start by showing the images
        
    }

    void update() {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Time elapsed1 = clock1.getElapsedTime();

        if (isShowingImages) {
            if (elapsed1.asSeconds() <= 2.5f) {
                if (elapsed1.asSeconds() < 0.5f) {
                    view.drawImage(view.getfinalTexture1());
                } else if (elapsed1.asSeconds() < 1.f) {
                    view.drawImage(view.getfinalTexture2());
                } else if (elapsed1.asSeconds() < 1.5f) {
                    view.drawImage(view.getfinalTexture3());
                } else if (elapsed1.asSeconds() < 2.f) {
                    view.drawImage(view.getfinalTexture4());
                } else {
                    view.drawImage(view.getfinalTexture());
                }
            } else {
                isShowingImages = false; // Done showing images, switch to animation
                //clock1.restart(); // Reset the animation timer
            }
        } else {
            if ((elapsed.asSeconds() <= 5.f) && (elapsed.asSeconds() > 3.f)) {
                view.drawRaiz(view.getraizEnganchadaTexture(), model.getR1(), model.getR2(), window.getSize().y * 5 / 10);
            } else if ((elapsed.asSeconds() <= 8.f) && (elapsed.asSeconds() > 5.f)) {
                view.drawRaiz(view.getraizEnganchadaTexture2(), model.getR1(), model.getR2(), window.getSize().y * 1 / 5 - 5);
            } else if (elapsed.asSeconds() > 8.f) {
                isShowingImages = true; // Done with animation, switch back to showing images
                clock.restart(); // Reset the image timer
                window.clear();
            }
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void draw() {
        view.draw();
    }
};

#endif
