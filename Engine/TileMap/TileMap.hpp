#pragma once

#include <SFML/Graphics.hpp>
#include <WorldEntity/WorldEntity.hpp>

#include <map>

class TileMap : public WorldEntity {
    private:
        // std::map<uns
    public:
        bool loadLDtkMap(const std::string& filename);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
