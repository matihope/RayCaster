add_library(Rays Level.cpp Level.h
        Player.cpp
        Player.h
        RayGame.cpp
        RayGame.h)
target_include_directories(Rays PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
