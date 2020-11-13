#include <SFML/Graphics.hpp>
#include <iostream>
#include "VideoHelpers.h"
#include "MenuSelector.h"
#include "TextComponent.h"
#include "MainMenu.h"

int main()
{
    sf::VideoMode fullscreenVideoMode;
    if (!VideoHelpers::getFullscreenVideoMode(fullscreenVideoMode))
    {
        std::cout << "Failed to get fullscreen video mode." << std::endl;
        return EXIT_FAILURE;
    }

    sf::RenderWindow window(fullscreenVideoMode, "PA8", sf::Style::Fullscreen);

    MainMenu mainMenu(fullscreenVideoMode);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            mainMenu.moveSelectorDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            mainMenu.moveSelectorUp();
        }

        window.clear();
        mainMenu.drawTo(window);
        window.display();
    }

    return 0;
}