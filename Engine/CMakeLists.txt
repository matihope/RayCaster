set(ENGINE_SOURCES
        AnimatedSprite/AnimatedSprite.cpp
        Game/Game.cpp
        GUI/Label.cpp
        GUI/Button.cpp
        JsonBridge/JsonBridge.cpp
        TileMap/TileMap.cpp
        TileMap/TileMapLayer.cpp
        CollisionComponent/CollisionComponent.cpp
        CollisionShape/CollisionShape.cpp
        Math/Math.cpp
        Tile/Tile.cpp
        ResourceManager/ResourceManager.cpp
        WorldEntity/WorldEntity.cpp
        Clickable/Clickable.cpp
        SpriteBatch/SpriteBatch.cpp SpriteBatch/SpriteBatch.hpp SpriteBatch/QuickSprite.cpp SpriteBatch/QuickSprite.hpp
        Nodes/RectShape.cpp
        Nodes/RectShape.hpp
        Nodes/CircleShape.cpp
        Nodes/CircleShape.hpp
        Nodes/RayShape.cpp
        Nodes/RayShape.hpp
        WorldEntity/BoxyWorldEntity.cpp
        WorldEntity/BoxyWorldEntity.hpp
)

add_library(Engine ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
