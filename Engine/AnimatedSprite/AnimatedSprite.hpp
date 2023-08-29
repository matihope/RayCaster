#pragma once
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <vector>
#include <map>
#include <memory>

struct Frame {
  unsigned int frameTime{};
  sf::IntRect frameRect;
};

struct Animation {
  std::string texture;
  std::vector<Frame> frames;
};

class AnimatedSprite : public WorldEntity {
  // variables
  float m_frame_time = 0.f;
  unsigned int m_current_frame = 0;
  bool m_is_paused = true;
  std::string m_current_animation_name;

  // objects
  sf::Sprite m_sprite;
  std::map<std::string, Animation> m_animations;
  Animation *m_current_animation_ptr;
  std::vector<std::string> m_animation_names;

 public:
  void setTextureRect(const sf::IntRect &rect);
  void setTexture(const std::string &texture);
  const sf::Texture *getTexture() const;
  const sf::IntRect &getTextureRect() const;
  void onUpdate(float dt) override;
  void addAnimation(const Animation &newAnimation, const std::string &animationName);
  void play(const std::string &animationName);
  void pause();
  void resume();
  std::vector<std::string> getAnimationNames() const;
  std::string getCurrentAnimationName() const;
  void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
