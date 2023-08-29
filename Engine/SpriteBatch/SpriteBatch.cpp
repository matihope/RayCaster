//
// Created by mateusz on 3/14/23.
//

#include "SpriteBatch.hpp"

SpriteBatch::SpriteBatch() : WorldEntity() {
  m_vertex_array.setPrimitiveType(sf::Quads);
}

SpriteBatch::SpriteBatch(const sf::Texture *texture) : SpriteBatch() {
  setTexture(texture);
}

SpriteBatch::SpriteBatch(std::size_t size, const sf::Texture *texture) : SpriteBatch() {
  setTexture(texture);
  setSize(size);
}

void SpriteBatch::setSize(std::size_t size) {
  m_vertex_array.resize(size * 4);
  for (size_t i = 0; i < size; i++) {
    getSprite(i).clear();
  }
}

QuickSprite SpriteBatch::getSprite(unsigned int id) {
  return QuickSprite(&m_vertex_array[id * 4]);
}

void SpriteBatch::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (m_texture == nullptr)
    return;

  states.transform *= getTransform();
  states.texture = m_texture;
  target.draw(m_vertex_array, states);
}

void SpriteBatch::setTexture(const sf::Texture *newTexture) {
  m_texture = newTexture;
}

const sf::Texture *SpriteBatch::getTexture() {
  return m_texture;
}

void SpriteBatch::makeGrid(sf::Vector2i grid_size, sf::Vector2f tile_size) {
  setSize(grid_size.x * grid_size.y);
  for (int x = 0; x < grid_size.x; x++) {
    for (int y = 0; y < grid_size.y; y++) {
      QuickSprite sprite = getSprite(y * grid_size.x + x);
      sprite.setPosition(sf::Vector2f(tile_size.x * x, tile_size.y * y));
      sprite.setSize(tile_size);
    }
  }
}
