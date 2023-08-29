#pragma once
#include <Clickable/Clickable.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <GUI/Label.hpp>
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <memory>

namespace GUI {
class Button : public WorldEntity, public Clickable {
  Label m_label;
  sf::Color m_fill_color = sf::Color::Transparent;
  sf::Color m_color_normal = sf::Color(255, 255, 255), m_color_hover = sf::Color(200, 200, 200),
      m_color_highlight = sf::Color(125, 125, 125);
  std::unique_ptr<RectCollision> m_collision_shape;
  bool m_has_custom_collision_shape = false;
  void onNotHover() override;
  void onHover() override;
  void onHold() override;

 public:
  Button();
  Button(sf::Font *font, const std::string &text);
  void setFont(sf::Font *font);
  void setText(const std::string &newText);
  void setTextSize(unsigned int newSize);
  void update(float dt) override;
  void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void updateDefaultCollisionShape();
  void setCollisionShape(std::unique_ptr<RectCollision> shape);
  sf::FloatRect getBounds() const;
  void setAlignment(HAlignment newHAlignment, VAlignment newVAlignment);
};
}
