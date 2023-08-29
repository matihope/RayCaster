#pragma once
#include <CollisionComponent/CollisionComponent.hpp>

class CircleCollision : public CollisionComponent {
 private:
  float m_radius;

 public:
  explicit CircleCollision(WorldEntity *parent);
  CircleCollision(WorldEntity *parent, float radius);

  ~CircleCollision() override = default;
  void setRadius(float radius);
  float getRadius() const;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  bool contains(const sf::Vector2f &point) const override;

};

class RectCollision : public CollisionComponent {
 private:
  sf::Vector2f m_size;

 public:
  explicit RectCollision(WorldEntity *parent);
  RectCollision(WorldEntity *parent, float width, float height);

  ~RectCollision() override = default;
  void setSize(float width, float height);
  const sf::Vector2f &getSize() const;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  bool contains(const sf::Vector2f &point) const override;
};
