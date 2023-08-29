#include <AnimatedSprite/AnimatedSprite.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <iostream>

void AnimatedSprite::setTexture(const std::string &texture) {
  m_sprite.setTexture(ResourceManager::get().getTexture(texture));
}

void AnimatedSprite::setTextureRect(const sf::IntRect &rect) {
  m_sprite.setTextureRect(rect);
}

const sf::Texture *AnimatedSprite::getTexture() const {
  return m_sprite.getTexture();
}

const sf::IntRect &AnimatedSprite::getTextureRect() const {
  return m_sprite.getTextureRect();
}

void AnimatedSprite::addAnimation(const Animation &newAnimation, const std::string &name) {
  m_animation_names.push_back(name);
  m_animations[name] = newAnimation;
}

std::vector<std::string> AnimatedSprite::getAnimationNames() const {
  return m_animation_names;
}

void AnimatedSprite::onUpdate(const float dt) {
  if (m_is_paused || m_animation_names.empty() || (*m_current_animation_ptr).frames.size() == 1)
    return;

  if (!m_is_paused)
    m_frame_time += dt * 1000;

  if (m_frame_time >= (*m_current_animation_ptr).frames[m_current_frame].frameTime) {
    m_frame_time -= (*m_current_animation_ptr).frames[m_current_frame].frameTime;
    m_current_frame = (m_current_frame + 1) % (*m_current_animation_ptr).frames.size();
    setTextureRect((*m_current_animation_ptr).frames[m_current_frame].frameRect);
  }
}

void AnimatedSprite::play(const std::string &animationName) {
  m_is_paused = false;
  if (m_current_animation_name == animationName)
    return;

  m_current_frame = 0;
  m_frame_time = 0.f;
  m_current_animation_name = animationName;
  m_current_animation_ptr = &m_animations[animationName];
  setTexture(m_current_animation_ptr->texture);
  setTextureRect((*m_current_animation_ptr).frames[m_current_frame].frameRect);
}

void AnimatedSprite::pause() {
  m_is_paused = true;
}

void AnimatedSprite::resume() {
  m_is_paused = false;
}

std::string AnimatedSprite::getCurrentAnimationName() const {
  return m_current_animation_name;
}

void AnimatedSprite::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_sprite, states);
}
