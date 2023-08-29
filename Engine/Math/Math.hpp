#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define FLOAT_INFINITY 1000000000.f
#define INT_INFINITY 1000000000I
#define LL_INFINITY 1000000000000000000LL
namespace Math {
// template<typename T>
int sign(float val);
sf::Vector2f normalizeVector(sf::Vector2f vector);
bool isPointInsideConvex(const std::vector<sf::Vector2f> &convex, const sf::Vector2f &point);
bool doShapesIntersect(const std::vector<sf::Vector2f> &shape1, const std::vector<sf::Vector2f> &shape2);
}
