#include <CollisionShape/CollisionShape.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <iostream>

CircleCollision::CircleCollision(WorldEntity* parent) : CollisionComponent(parent) {
    setRadius(5.f);
}

CircleCollision::CircleCollision(WorldEntity* parent, const float radius)
    : CollisionComponent(parent) {
    setRadius(radius);
}

void CircleCollision::setRadius(const float radius) { m_radius = radius; }

float CircleCollision::getRadius() const { return m_radius; }

void CircleCollision::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    CollisionComponent::draw(target, states);

    sf::CircleShape shape(m_radius);
    shape.setFillColor(m_fill_color);
    shape.setOutlineColor(m_outline_color);
    target.draw(shape, states);
}

bool CircleCollision::contains(const sf::Vector2f& point) const {
    float a = getPosition().x - point.x;
    float b = getPosition().y - point.y;
    return a * a + b * b <= m_radius * m_radius;
}

// RECT

RectCollision::RectCollision(WorldEntity* parent) : CollisionComponent(parent) {
    m_parent = parent;
    setSize(5.f, 5.f);
}

RectCollision::RectCollision(WorldEntity* parent, const float width, const float height)
    : CollisionComponent(parent) {
    setSize(width, height);
}

void RectCollision::setSize(const float width, const float height) {
    m_size.x = width;
    m_size.y = height;
}

const sf::Vector2f& RectCollision::getSize() const {
    return m_size;
}

void RectCollision::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(!shouldDraw()) return;
    states.transform *= getTransform();
    sf::RectangleShape shape(m_size);
    shape.setFillColor(m_fill_color);
    shape.setOutlineColor(m_outline_color);
    target.draw(shape, states);
}

bool RectCollision::contains(const sf::Vector2f& point) const {
    auto pos = m_parent->getTransform().transformPoint(getPosition());
    if(point.x < pos.x)
        return false;
    if(point.x > pos.x + m_size.x)
        return false;
    if(point.y < pos.y)
        return false;
    if(point.y > pos.y + m_size.y)
        return false;
    return true;
}
