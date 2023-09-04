add_library(Rays Level/Level.cpp Level/Level.h
        Player.cpp
        Player.h
        RayGame.cpp
        RayGame.h
        Level/Wall.cpp
        Level/Wall.hpp)
target_include_directories(Rays PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
