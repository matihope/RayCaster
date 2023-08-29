#pragma once
#include <SFML/Graphics.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <map>

class TileMapLayer : public WorldEntity {
  const sf::Texture* m_texture;
  sf::VertexArray m_vertex_array;

 public:
  TileMapLayer(const std::string& texturePath);
  bool createLayer(const std::vector<int>& ids, const unsigned int tileSize,
                   const unsigned int gridWidth);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
