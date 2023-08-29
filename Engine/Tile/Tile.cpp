#include <Tile/Tile.hpp>
#include <iostream>

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
    // #if(DEBUG)
    //     target.draw(m_collision_shape, states);
    // #endif
}

void Tile::update(const float dt) {
    if(m_is_animated)
        m_sprite.update(dt);
}

void Tile::addAnimation(const Animation& animation) {
    m_is_animated = true;
    m_sprite.addAnimation(animation, "base");
    m_sprite.play("base");
}

void Tile::setTexture(const std::string& texture) {
    m_sprite.setTexture(texture);
}

const sf::Texture* Tile::getTexture() const {
    return m_sprite.getTexture();
}

void Tile::setTextureRect(const sf::IntRect& rect) {
    m_sprite.setTextureRect(rect);
}

const sf::IntRect& Tile::getTextureRect() const {
    return m_sprite.getTextureRect();
}

// void Tile::setCollisionShape(const CollisionComponent& shape) {
//     m_has_collision = true;
//     m_collision_shape = shape;
// }

bool Tile::isAnimated() const {
    return m_is_animated;
}

bool Tile::hasCollision() const {
    return m_has_collision;
}

// bool Tile::intersects(const std::vector<sf::Vector2f>& shape) const {
//     return m_collision_shape.intersects(getTransform(), shape);
// }
