#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <map>

class ResourceManager {
 private:
  ResourceManager() = default;
  sf::Texture &getMutTexture(const std::string &path);
  std::map<std::string, sf::Texture> m_textures;
  std::map<sf::Cursor::Type, sf::Cursor> m_system_cursors;
  std::map<std::string, sf::SoundBuffer> m_sound_buffers;

 public:
  // singleton stuff
  ResourceManager(const ResourceManager &) = delete;
  void operator=(const ResourceManager &) = delete;
  static ResourceManager &get();

  const sf::Texture &getTexture(const std::string &path);
  const sf::SoundBuffer &getSoundBuffer(const std::string &path);
  const sf::Cursor &getSystemCursor(sf::Cursor::Type type);
  void setTextureSmooth(const std::string &path, bool smooth);
};
