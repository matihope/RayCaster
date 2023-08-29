#include <GUI/Button.hpp>
#include <Updatable/Updatable.hpp>
#include <Game/Game.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GUI {
Button::Button() {
  m_label.setAlignment(HAlignment::MIDDLE, VAlignment::CENTER);
}

Button::Button(sf::Font *font, const std::string &text) : Button() {
  setFont(font);
  setText(text);
}

void Button::setAlignment(HAlignment newHAlignment, VAlignment newVAlignment) {
  m_label.setAlignment(newHAlignment, newVAlignment);
}

void Button::setFont(sf::Font *newFont) {
  m_label.setFont(newFont);
  updateDefaultCollisionShape();
}

void Button::setText(const std::string &newText) {
  m_label.setText(newText);
  updateDefaultCollisionShape();
}

void Button::setTextSize(unsigned int newSize) {
  m_label.setTextSize(newSize);
  updateDefaultCollisionShape();
}

void Button::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_label, states);

#if(DEBUG)
  // debugs:
  target.draw(*m_collision_shape, states);
#endif
}

void Button::onHover() { m_label.setColor(m_color_hover); }

void Button::onNotHover() { m_label.setColor(m_color_normal); }

void Button::onHold() { m_label.setColor(m_color_highlight); }

void Button::update(const float dt) { Clickable::update(dt); }

void Button::updateDefaultCollisionShape() {
  if (m_has_custom_collision_shape)
    return;

  sf::FloatRect bounds = getBounds();
  m_collision_shape = std::make_unique<RectCollision>(this, bounds.width, bounds.height);
  setClickCollisionShape(m_collision_shape.get());
  m_collision_shape->setPosition(bounds.left, bounds.top);
  // m_collision_shape->move(getPosition()); // used to be here, idk why tho ;D
}

void Button::setCollisionShape(std::unique_ptr<RectCollision> shape) {
  m_has_custom_collision_shape = true;
  setClickCollisionShape(shape.get());
  m_collision_shape = std::move(shape);
}

sf::FloatRect Button::getBounds() const {
  // override this when inheriting from Button
  return m_label.getBounds();
}
}
