#include "tmxparse.h"
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "pugixml.hpp"

tmxparse::tmxparse()
{

}

void tmxparse::loadtmx(const char* tmxfilename)
{
  pugi::xml_document mapDoc;
  mapDoc.load_file(tmxfilename);

  this->nodeMap = mapDoc.child("map");
  this->nodeTileset = this->nodeMap.child("tileset");
  this->nodeData = this->nodeMap.child("layer").child("data");

  this->fnTileset = this->nodeTileset.child("image").attribute("source").as_string();

  this->tileSize.x = this->nodeTileset.attribute("tilewidth").as_int();
  this->tileSize.y = this->nodeTileset.attribute("tileheight").as_int();

  this->gridSize.x = this->nodeMap.attribute("width").as_int();
  this->gridSize.y = this->nodeMap.attribute("height").as_int();

  this->mapSize.x = this->gridSize.x * this->tileSize.x;
  this->mapSize.y = this->gridSize.y * this->tileSize.y;

  this->generateTexture();

}

sf::Vector2i tmxparse::getTileSize()
{
  return this->tileSize;
}

sf::Vector2i tmxparse::getMapSize()
{
  return this->mapSize;
}

sf::Texture tmxparse::getTexture()
{
  return this->bgTexture;
}

void tmxparse::generateTexture()
{
  sf::Image imgTileset;
  imgTileset.loadFromFile("assets/" + this->fnTileset);

  this->bgTexture.create(this->gridSize.x * this->tileSize.x, this->gridSize.y * this->tileSize.y);

  sf::Vector2i gridPos(1,1);
  sf::Vector2i tsGridSize((imgTileset.getSize().x / this->tileSize.x), (imgTileset.getSize().y / this->tileSize.y));

  std::string rawstring = this->nodeData.child_value();
  std::string mapString = rawstring.c_str();
  std::istringstream ss(mapString);
  std::string tile;

  while (std::getline(ss, tile, ','))
    {
      sf::Image imgTile;
      imgTile.create(this->tileSize.x, this->tileSize.y);

      int startX = ((std::stoi(tile)-1) % tsGridSize.x) * this->tileSize.x;
      int startY = ((std::stoi(tile)-1) / tsGridSize.x) * this->tileSize.y;

      imgTile.copy(imgTileset, 0, 0, sf::IntRect(startX, startY, this->tileSize.x, this->tileSize.y), false);
      this->bgTexture.update(imgTile, (gridPos.x * this->tileSize.x) - this->tileSize.x, (gridPos.y * this->tileSize.y) - this->tileSize.y);

      if (gridPos.x == this->gridSize.x) { gridPos.y++; gridPos.x = 0; }
      gridPos.x++;
    }
}

