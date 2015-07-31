#include <SFML/Graphics.hpp>
#include <iostream>
#include "tmxparse.h"

int main()
{
    tmxparse tmxMap;
    tmxMap.loadtmx("assets/big.tmx");

    sf::Sprite background(tmxMap.bgTexture);

    sf::RenderWindow window(sf::VideoMode(400,300), "GameWindow");
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(400,300,400,300));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { view.move(-1,0); }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { view.move(1,0); }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { view.move(0,-1); }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { view.move(0,1); }

        window.setView(view);
        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}
