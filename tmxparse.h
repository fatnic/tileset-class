#ifndef TMXPARSE_H
#define TMXPARSE_H

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

class tmxparse
{
public:
  tmxparse();
  void loadtmx(const char *tmxfilename);
  sf::Vector2i getTileSize();
  sf::Vector2i getMapSize();
  sf::Texture getTexture();
private:
  void generateTexture();
  pugi::xml_node nodeMap;
  pugi::xml_node nodeTileset;
  pugi::xml_node nodeData;

  sf::Vector2i tileSize;
  sf::Vector2i gridSize;
  sf::Vector2i mapSize;
  std::string fnTileset;

  sf::Texture bgTexture;

  std::string mapString;
};

#endif // TMXPARSE_H
