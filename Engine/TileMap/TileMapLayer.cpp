#include <TileMap/TileMapLayer.hpp>
#include <ResourceManager/ResourceManager.hpp>

TileMapLayer::TileMapLayer(const std::string& texturePath) {
    m_texture = &ResourceManager::get().getTexture(texturePath);
}

bool TileMapLayer::createLayer(const std::vector<int>& ids, const unsigned int tileSize, const unsigned int gridWidth){
    m_vertex_array.setPrimitiveType(sf::Quads);
    m_vertex_array.resize(ids.size() * 4);

    for(size_t i = 0; i < ids.size(); ++i) {
        int x = i % gridWidth;
        int y = i / gridWidth;
        sf::Vertex* quad = &m_vertex_array[i * 4];
        quad[0].position = sf::Vector2f(x * tileSize, y * tileSize);
        quad[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
        quad[2].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
        quad[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);

        quad[0].texCoords = sf::Vector2f(0, 0);
        quad[1].texCoords = sf::Vector2f(tileSize, 0);
        quad[2].texCoords = sf::Vector2f(tileSize, tileSize);
        quad[3].texCoords = sf::Vector2f(0, tileSize);
    }

    return true;
}

void TileMapLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = m_texture;
    target.draw(m_vertex_array, states);
}
