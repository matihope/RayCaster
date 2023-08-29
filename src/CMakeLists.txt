add_library(Game Scenes/RunScene.cpp Scenes/RunScene.h
        Scenes/World.cpp
        Scenes/World.h)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
