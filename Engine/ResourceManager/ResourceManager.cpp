#include <ResourceManager/ResourceManager.hpp>

ResourceManager &ResourceManager::get() {
  static ResourceManager instance;
  return instance;
}

sf::Texture &ResourceManager::getMutTexture(const std::string &path) {
  if (!m_textures.contains(path)) {
    m_textures[path] = sf::Texture();
    m_textures[path].loadFromFile(path);
  }
  return m_textures[path];
}

const sf::Texture &ResourceManager::getTexture(const std::string &path) {
  return getMutTexture(path);
}

void ResourceManager::setTextureSmooth(const std::string &path, bool smooth) {
  getMutTexture(path).setSmooth(smooth);
}

const sf::Cursor &ResourceManager::getSystemCursor(sf::Cursor::Type type) {
  if (!m_system_cursors.contains(type)) {
    m_system_cursors[type].loadFromSystem(type);
  }
  return m_system_cursors[type];
}

const sf::SoundBuffer &ResourceManager::getSoundBuffer(const std::string &path) {
  if (!m_sound_buffers.contains(path)) {
    m_sound_buffers[path].loadFromFile(path);
  }
  return m_sound_buffers[path];
}
