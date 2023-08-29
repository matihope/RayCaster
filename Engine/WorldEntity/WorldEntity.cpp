#include "WorldEntity.hpp"

#include <WorldEntity/WorldEntity.hpp>
#include <iostream>

EntityID WorldEntity::id_counter = 0;

WorldEntity::WorldEntity() : m_entityId(id_counter++) {
  m_parent = nullptr;
  m_show = true;
}

EntityID WorldEntity::getId() const { return m_entityId; }

void WorldEntity::queueFree() { m_toKill = true; }

const bool &WorldEntity::isDying() const { return m_toKill; }

void WorldEntity::cleanEntities() {
  for (auto &layer : m_entity_pool) {
    for (auto it = layer.second.begin(); it != layer.second.end(); it++) {
      WorldEntity *entity = it->get();
      if (entity->isDying()) {
        it = layer.second.erase(it);
      }
    }
  }
}

void WorldEntity::physicsUpdate(const float dt) {
  onPhysicsUpdate(dt);
  for (const auto &layer : m_entity_pool) {
    for (auto &entity : layer.second) entity->physicsUpdate(dt);
  }
}

void WorldEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if(not m_show) return;
  sf::RenderStates copied_states(states);
  copied_states.transform *= getTransform();
  onDraw(target, states);

  for (const auto &layer : m_entity_pool) {
    for (auto &entity : layer.second) target.draw(*entity, copied_states);
  }
}

void WorldEntity::addChild(std::unique_ptr<WorldEntity> child, unsigned int drawOrder) {
  child->addParent(this);
  child->ready();
  m_entity_pool[drawOrder].push_back(std::move(child));
}

void WorldEntity::addParent(WorldEntity *parent) { m_parent = parent; }

WorldEntity *WorldEntity::getParent() { return m_parent; }

void WorldEntity::update(float dt) {
  cleanEntities();
  onUpdate(dt);
  for (const auto &layer : m_entity_pool) {
    for (auto &entity : layer.second) entity->update(dt);
  }
}

void WorldEntity::show() {
  m_show = true;
}

void WorldEntity::hide() {
  m_show = false;
}
