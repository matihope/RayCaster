#include <Math/Math.hpp>
#include <cmath>
#include <iostream>

namespace Math {
int sign(float val) {
  return (0 < val) - (val < 0);
}

sf::Vector2f normalizeVector(const sf::Vector2f vector) {
  if (vector.x == 0 || vector.y == 0)
    return vector;
  float length = sqrt(vector.x * vector.x + vector.y * vector.y);
  return {vector.x / length, vector.y / length};
}

// here vectors are points
float determinant(const sf::Vector2f &tail, const ::sf::Vector2f &head1, const ::sf::Vector2f &head2) {
  return (head1.x - tail.x) * (head2.y - tail.y) - (head2.x - tail.x) * (head1.y - tail.y);
}

bool isPointInsideConvex(const std::vector<sf::Vector2f> &convex, const sf::Vector2f &point) {
  if (convex.size() < 3) return false;

  bool has_neg = false;
  bool has_pos = false;
  for (size_t i = 0; i < convex.size(); i++) {
    int now_sign = sign(determinant(point, convex[i], convex[(i + 1) % convex.size()]));
    if (now_sign == -1) has_neg = true;
    if (now_sign == 1) has_pos = true;
    if (has_neg && has_pos)
      return false;
  }

  return true;
}

// here vectors are math vectors
sf::Vector2f getPerpendicular(const sf::Vector2f &vec) {
  return {-vec.y, vec.x};
}

// here vectors are math vectors
float dotProduct(const sf::Vector2f &vec1, const sf::Vector2f &vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

bool doShapesIntersect(const std::vector<sf::Vector2f> &shape1, const std::vector<sf::Vector2f> &shape2) {
  const std::vector<sf::Vector2f> *s1 = &shape1;
  const std::vector<sf::Vector2f> *s2 = &shape2;
  for (size_t t = 0; t < 2; ++t) {
    if (t == 1) {
      s1 = &shape2;
      s2 = &shape1;
    }
    for (size_t i = 0; i < s1->size(); i++) {
      sf::Vector2f perpendicular = getPerpendicular(sf::Vector2f((*s1)[(i + 1) % s1->size()].x - (*s1)[i].x,
                                                                 (*s1)[(i + 1) % s1->size()].y - (*s1)[i].y));
      float min1 = FLOAT_INFINITY;
      float max1 = -FLOAT_INFINITY;
      for (auto j : *s1) {
        float dp = dotProduct(perpendicular, j);
        min1 = std::min(min1, dp);
        max1 = std::max(max1, dp);
      }
      float min2 = FLOAT_INFINITY;
      float max2 = -FLOAT_INFINITY;
      for (auto j : *s2) {
        float dp = dotProduct(perpendicular, j);
        min2 = std::min(min2, dp);
        max2 = std::max(max2, dp);
      }
      if (max2 < min1 || min2 > max1)
        return false;
    }
  }
  return true;
}
}
