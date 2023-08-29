#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Debug {
void setDebugCollisionDraw(bool draw);
}

enum class CollisionType {
  STATIC,
  DYNAMIC
};

class WorldEntity;

class CollisionComponent : public sf::Drawable, public sf::Transformable {
 protected:
  bool m_draw = false;

  sf::Color m_outline_color = sf::Color(200.f, 100.f, 125.f, 175.f);
  sf::Color m_fill_color = sf::Color(50.f, 175.f, 255.f, 100.f);

  WorldEntity *m_parent;

 public:
  explicit CollisionComponent(WorldEntity *parent);
  CollisionComponent(const CollisionComponent &c) = default;

  ~CollisionComponent() override = default;
  virtual bool contains(const sf::Vector2f &point) const = 0;

  bool shouldDraw() const;
  void setDraw(bool draw);
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
