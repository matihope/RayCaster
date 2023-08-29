cmake_minimum_required(VERSION 3.25)

project(RayCaster)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# SFML
find_package(SFML 2.6 REQUIRED COMPONENTS window audio graphics system network)
link_libraries(sfml-graphics sfml-window sfml-system sfml-audio)

# Nlohmann json
find_package(nlohmann_json 3.11.2 REQUIRED)
link_libraries(nlohmann_json::nlohmann_json)

# Engine
add_subdirectory(Engine)
link_libraries(Engine)

# Game source code
add_subdirectory(src)
link_libraries(Game)

add_executable(${PROJECT_NAME} main.cpp)
