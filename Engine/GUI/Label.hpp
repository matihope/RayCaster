#pragma once
#include <SFML/Graphics.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <memory>

namespace GUI {
enum class HAlignment {
  LEFT,
  MIDDLE,
  RIGHT
};

enum class VAlignment {
  TOP,
  CENTER,
  BOTTOM
};

class Label : public WorldEntity {
  sf::Font *m_font{};
  HAlignment m_halignment = HAlignment::LEFT;
  VAlignment m_valignment = VAlignment::TOP;
  sf::Text m_text;

 public:
  Label();
  explicit Label(sf::Font *font);
  void setFont(sf::Font *font);
  void setText(const std::string &text);
  void setAlignment(HAlignment newHAlignment, VAlignment newVAlignment);
  void setTextSize(unsigned int newSize);
  void setColor(sf::Color newColor);
  void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
  sf::FloatRect getBounds() const;
};
}
