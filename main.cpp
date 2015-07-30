#include <SFML/Graphics.hpp>
#include <iostream>
#include "tmxparse.h"

int main()
{
    tmxparse tmxMap;
    tmxMap.loadtmx("assets/map.tmx");

    sf::Texture bg(tmxMap.getTexture());
    sf::Sprite background(bg);

    sf::RenderWindow window(sf::VideoMode(tmxMap.getMapSize().x, tmxMap.getMapSize().y), "GameWindow");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}
