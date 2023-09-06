#pragma once
#include <CollisionComponent/CollisionComponent.hpp>
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <list>
#include <map>
#include <memory>

typedef unsigned long long EntityID;

class WorldEntity : public sf::Drawable, public sf::Transformable, public Updatable {
 private:
	static EntityID id_counter;
	EntityID m_entityId;

	bool m_toKill = false;
	WorldEntity *m_parent;

	bool m_show;

	void cleanEntities();

 public:
	friend class BoxyWorldEntity;

	WorldEntity();
	~WorldEntity() override = default;

	EntityID getId() const;

	void queueFree();
	const bool &isDying() const;

	std::map<uint, std::list<std::unique_ptr<WorldEntity>>> m_entity_pool;

	void addParent(WorldEntity *parent);
	WorldEntity *getParent();

	void addChild(std::unique_ptr<WorldEntity> entity, unsigned int drawOrder = 0);

	// ugly, but this function has to be in .hpp file, otherwise it's unusable
	template<class T, unsigned int drawOrder = 0, class... Args>
	T *addChild(Args &&... args) {
		auto new_child = std::make_unique<T>(std::forward<Args>(args)...);
		auto new_child_ptr = new_child.get();
		addChild(std::move(new_child), drawOrder);
		return new_child_ptr;
	}

	void update(float dt) override;
	void physicsUpdate(float dt) override;
	void renderOnto(sf::RenderTarget &target, sf::RenderStates states) const;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	virtual void onUpdate(float dt) {};

	virtual void onPhysicsUpdate(float dt) {};

	virtual void onDraw(sf::RenderTarget &target, sf::RenderStates states) const {};

	virtual void handleEvent(const sf::Event &event) {};

	void show();
	void hide();

	sf::Vector2f getGlobalPosition() const;
};
