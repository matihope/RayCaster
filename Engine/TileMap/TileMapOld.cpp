#include <AnimatedSprite/AnimatedSprite.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <TileMap/TileMap.hpp>
#include <Tile/Tile.hpp>
#include <iostream>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // target.draw(m_layers, states);
}

bool TileMap::load(const std::string& mapFile){

}

bool TileMap::loadTiled(const std::string& mapFile){
    m_tilemap_path = mapFile;
    if(!m_map_data.load(mapFile)){
        std::cout << "Error loading map: " << mapFile << std::endl;
        return false;
    }

    unsigned int tileW = m_map_data.data["tilewidth"];
    unsigned int tileH = m_map_data.data["tileheight"];
    for(size_t i = 0; i < m_map_data.data["tilesets"].size(); i++) {

        // get texture
        const std::string& texture = m_map_data.data["tilesets"][i]["image"];

        // create presets
        unsigned int firstTileId = m_map_data.data["tilesets"][i]["firstgid"];
        unsigned int tilesX = m_map_data.data["tilesets"][i]["columns"];
        unsigned int tilesY = int(m_map_data.data["tilesets"][i]["tilecount"]) / tilesX;
        for(size_t y = 0; y < tilesY; ++y){
            for(size_t x = 0; x < tilesX; ++x){
                Tile tile_template;
                tile_template.setTexture(texture);
                tile_template.setTextureRect(sf::IntRect(x * tileW, y * tileH, tileW, tileH));
                m_tile_templates[firstTileId + x + y * tilesX] = tile_template;
            }
        }

        // add special features
        if(m_map_data.data["tilesets"][i].contains("tiles")){
            // create all animated sprites
            for(auto tile: m_map_data.data["tilesets"][i]["tiles"]){
                if(!tile.contains("animation"))
                    continue;

                Animation animation;
                animation.texture = m_map_data.data["tilesets"][i]["image"];
                for(auto& frame: tile["animation"]){
                    animation.frames.push_back(
                        {
                            (unsigned int)frame["duration"],
                            m_tile_templates[int(frame["tileid"]) + firstTileId].getTextureRect()
                        }
                    );
                }
                m_tile_templates[int(tile["id"]) + firstTileId].addAnimation(animation);
            }
            // add collisions to tiles
            for(auto tile: m_map_data.data["tilesets"][i]["tiles"]){
                if(!tile.contains("objectgroup"))
                    continue;

                // iterate through all collision shapes
                if(tile["objectgroup"]["objects"].size() != 1){
                    std::cout << "ERROR: Tile has many collision shapes..." << std::endl;
                    continue;
                }

                auto& cs_data = tile["objectgroup"]["objects"][0]; // collision_shape_data
                CollisionComponent shape;
                std::vector<sf::Vector2f> points;
                float x = roundf(cs_data["x"]);
                float y = roundf(cs_data["y"]);
                if(cs_data.contains("polygon")){
                    for(auto& point : cs_data["polygon"]){
                        points.push_back({
                            roundf(point["x"]) + x,
                            roundf(point["y"]) + y
                        });
                    }
                } else {
                    // rectangle
                    float width = roundf(cs_data["width"]);
                    float height = roundf(cs_data["height"]);
                    points.push_back({x, y});
                    points.push_back({x + width, y});
                    points.push_back({x + width, y + height});
                    points.push_back({x, y + height});
                }
                shape.setShape(points);
                m_tile_templates[int(tile["id"]) + firstTileId].setCollisionShape(shape);

            }
        }
    }
    // layers
    for(size_t i = 0; i < m_map_data.data["layers"].size(); ++i){
        if(m_map_data.data["layers"][i]["type"] != "tilelayer" || m_map_data.data["layers"][i]["visible"] == false)
            continue;
        int layerWidth = m_map_data.data["layers"][i]["width"];

        // individual tiles
        for(size_t j = 0; j < m_map_data.data["layers"][i]["data"].size(); ++j){
            int tileId = m_map_data.data["layers"][i]["data"][j];

            // skip if empty
            if(tileId == 0)
                continue;

            // copy tile from template and locate it correctly
            auto tile = std::make_shared<Tile>(getTileTemplate(tileId));
            tile->setPosition( (j % layerWidth) * tileW, (j / layerWidth) * tileH );
            if(tile->isAnimated())
                m_updatables.push_back(tile);
            if(tile->hasCollision())
                m_collidable_tiles.push_back(tile);

            if(m_map_data.data["layers"][i]["name"] == "Obstacles")
                m_ysort_layer.push_back(tile);
            else
                {}
                // m_layers.addSprite(tile, i);

        }
    }
    return true;
}

Tile TileMap::getTileTemplate(unsigned int id) const {
    return m_tile_templates.at(id);
}

void TileMap::update(const float dt) {
    for(auto& updatable: m_updatables)
        updatable->update(dt);
}

bool TileMap::reload(){
    m_map_data.data.clear();
    // m_layers = DrawLayers();
    m_tile_templates.clear();
    m_updatables.clear();
    m_ysort_layer.clear();
    return load(m_tilemap_path);
}


std::vector<std::shared_ptr<Tile>>& TileMap::getCollidableTiles() {
    return m_collidable_tiles;
}

std::vector<std::shared_ptr<Tile>>& TileMap::getYSortLayerTiles() {
    return m_ysort_layer;
}
