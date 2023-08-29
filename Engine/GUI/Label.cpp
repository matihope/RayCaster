#include <GUI/Label.hpp>
#include <iostream>

namespace GUI {
Label::Label() {
  // default size
  m_text.setCharacterSize(32);
}

Label::Label(sf::Font *font) : Label() {
  setFont(font);
}

void Label::setFont(sf::Font *font) {
  m_text.setFont(*font);
  m_font = font;
  setTextSize(m_text.getCharacterSize());
}

void Label::setText(const std::string &newText) {
  m_text.setString(newText);
  setAlignment(m_halignment, m_valignment);
}

void Label::setAlignment(HAlignment newHAlignment, VAlignment newVAlignment) {
  m_halignment = newHAlignment;
  m_valignment = newVAlignment;
  int textWidth = (int) m_text.getGlobalBounds().width;
  int textHeight = (int) m_text.getGlobalBounds().height;
  sf::Vector2f newPos(-m_text.getLocalBounds().left, -m_text.getLocalBounds().top);
  switch (m_halignment) {
    case HAlignment::LEFT:
      // nothing to do
      break;
    case HAlignment::MIDDLE:newPos.x -= (float) textWidth / 2;
      break;
    case HAlignment::RIGHT:newPos.x -= (float) textWidth;
      break;
  }
  switch (m_valignment) {
    case VAlignment::TOP:
      // nothing to do
      break;
    case VAlignment::CENTER:newPos.y -= (float) textHeight / 2;
      break;
    case VAlignment::BOTTOM:newPos.y -= (float) textHeight;
      break;
  }
  m_text.setPosition((int) newPos.x, (int) newPos.y);
}

void Label::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (m_text.getString() == "") return;
  states.transform *= getTransform();
  // debugs:
  // sf::RectangleShape test;
  // test.setFillColor(sf::Color::Transparent);
  // test.setOutlineThickness(1.f);
  // test.setOutlineColor(sf::Color::Red);
  // test.setSize(sf::Vector2f(m_text.getGlobalBounds().width,
  // m_text.getGlobalBounds().height)); test.setPosition(m_text.getGlobalBounds().left,
  // m_text.getGlobalBounds().top); target.draw(test, states);
  target.draw(m_text, states);
}

void Label::setTextSize(const unsigned int newSize) {
#if (SFML_VERSION_MINOR <= 5)
  // weird hack to turn off font smoothing...
  auto &texture = const_cast<sf::Texture &>(m_font->getTexture(newSize));
  texture.setSmooth(false);
#else
  m_font->setSmooth(false);
#endif
  m_text.setCharacterSize(newSize);
  setAlignment(m_halignment, m_valignment);
}

void Label::setColor(const sf::Color newColor) {
  m_text.setFillColor(newColor);
}

sf::FloatRect Label::getBounds() const {
  return m_text.getGlobalBounds();
}

}
