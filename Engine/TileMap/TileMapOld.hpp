#pragma once
#include <SFML/Graphics.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <Updatable/Updatable.hpp>
#include <AnimatedSprite/AnimatedSprite.hpp>
#include <CollisionComponent/CollisionComponent.hpp>
#include <Tile/Tile.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <map>

class TileMap : public WorldEntity {
    std::string m_tilemap_path;
    JsonBridge m_map_data;
    // DrawLayers m_layers;
    std::map<unsigned int, Tile> m_tile_templates;
    std::vector<std::shared_ptr<Updatable>> m_updatables;
    std::vector<std::shared_ptr<Tile>> m_collidable_tiles;
    std::vector<std::shared_ptr<Tile>> m_ysort_layer;

    public:
        bool load(const std::string& mapFile);
        bool loadTiled(const std::string& mapFile);
        bool reload();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Tile getTileTemplate(unsigned int id) const;
        void update(const float dt) override;
        std::vector<std::shared_ptr<Tile>>& getCollidableTiles();
        std::vector<std::shared_ptr<Tile>>& getYSortLayerTiles();
};
