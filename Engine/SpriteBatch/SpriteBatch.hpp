//
// Created by mateusz on 3/14/23.
//

#pragma once
#include "WorldEntity/WorldEntity.hpp"
#include "QuickSprite.hpp"

class SpriteBatch : public WorldEntity {
 public:
  SpriteBatch();
  explicit SpriteBatch(const sf::Texture *texture);
  explicit SpriteBatch(std::size_t size, const sf::Texture *texture);
  void setSize(std::size_t size);
  void setTexture(const sf::Texture *newTexture);
  const sf::Texture *getTexture();
  QuickSprite getSprite(unsigned int id);
  void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;

  // sets all vertices in grid
  // top left's id is 0 and increments horizontally first
  void makeGrid(sf::Vector2i grid_size, sf::Vector2f tile_size);
 private:
  sf::VertexArray m_vertex_array;
  const sf::Texture *m_texture;
};
