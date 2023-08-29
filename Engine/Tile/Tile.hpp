#pragma once
#include <SFML/Graphics.hpp>
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <CollisionComponent/CollisionComponent.hpp>
#include <Updatable/Updatable.hpp>
#include <WorldEntity/WorldEntity.hpp>

class Tile : public WorldEntity {
    bool m_is_animated = false;
    bool m_has_collision = false;
    AnimatedSprite m_sprite;
    // CollisionComponent m_collision_shape;

    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update(const float dt);
        void setTexture(const std::string& texture);
        const sf::Texture* getTexture() const;
        void setTextureRect(const sf::IntRect& rectangle);
        const sf::IntRect& getTextureRect() const;
        void setCollisionShape(const CollisionComponent& shape);
        void addAnimation(const Animation& animation);
        bool isAnimated() const;
        bool hasCollision() const;
        bool intersects(const std::vector<sf::Vector2f>& shape) const;
};
