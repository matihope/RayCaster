add_subdirectory(Rays)

add_library(Game Scenes/MenuScene.cpp Scenes/MenuScene.h
        Scenes/World.cpp
        Scenes/World.h
        Scenes/Level2D/Level2D.cpp
        Scenes/Level2D/Level2D.h
        Scenes/Level3D/Level3D.cpp
        Scenes/Level3D/Level3D.hpp
        Scenes/Level2D/ViewArea.cpp
        Scenes/Level2D/ViewArea.hpp
)
target_link_libraries(Game PRIVATE Rays)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
