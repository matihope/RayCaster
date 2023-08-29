//
// Created by mateusz on 3/14/23.
//

#include "QuickSprite.hpp"

QuickSprite::QuickSprite(sf::Vertex *quad) {
  m_quad = quad;
}

void QuickSprite::setPosition(sf::Vector2f position) {
  sf::Vector2f size = getSize();
  m_quad[0].position = position;
  setSize(size);
}

void QuickSprite::setSize(sf::Vector2f newSize) {
  m_quad[1].position = sf::Vector2f(m_quad[0].position.x + newSize.x, m_quad[0].position.y);
  m_quad[2].position = sf::Vector2f(m_quad[0].position.x + newSize.x, m_quad[0].position.y + newSize.y);
  m_quad[3].position = sf::Vector2f(m_quad[0].position.x, m_quad[0].position.y + newSize.y);
}

sf::Vector2f QuickSprite::getPosition() const {
  return m_quad[0].position;
}

sf::Vector2f QuickSprite::getSize() const {
  float width = m_quad[1].position.x - m_quad[0].position.x;
  float height = m_quad[3].position.y - m_quad[0].position.y;
  return {width, height};
}

void QuickSprite::setTexSize(sf::Vector2f newSize) {
  newSize -= sf::Vector2f(2 * M_TEX_BUFFER, 2 * M_TEX_BUFFER);
  m_quad[1].texCoords = sf::Vector2f(m_quad[0].texCoords.x + newSize.x, m_quad[0].texCoords.y);
  m_quad[2].texCoords = sf::Vector2f(m_quad[0].texCoords.x + newSize.x, m_quad[0].texCoords.y + newSize.y);
  m_quad[3].texCoords = sf::Vector2f(m_quad[0].texCoords.x, m_quad[0].texCoords.y + newSize.y);
}

sf::Vector2f QuickSprite::getTexSize() const {
  float width = m_quad[1].texCoords.x - m_quad[0].texCoords.x;
  float height = m_quad[3].texCoords.y - m_quad[0].texCoords.y;
  return {width + 2 * M_TEX_BUFFER, height + 2 * M_TEX_BUFFER};
}

void QuickSprite::setTexPosition(sf::Vector2f position) {
  sf::Vector2f size = getTexSize();
  m_quad[0].texCoords = position + sf::Vector2f(M_TEX_BUFFER, M_TEX_BUFFER);
  setTexSize(size);
}

sf::Vector2f QuickSprite::getTexPosition() const {
  return m_quad[0].texCoords - sf::Vector2f(M_TEX_BUFFER, M_TEX_BUFFER);
}

void QuickSprite::clear() {
  setTexSize(sf::Vector2f(0, 0));
  setTexPosition({-1, -1});
}
