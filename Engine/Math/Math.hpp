#pragma once
#include <vector>
#include <cmath>

#define FLOAT_INFINITY 1000000000.f
#define INT_INFINITY 1000000000I
#define LL_INFINITY 1000000000000000000LL
#define EPS_ZERO 1e-12

namespace Math {

template<typename T>
int sign(T val) {
  return (0 < val) - (val < 0);
}
template<typename T>
class Vector2 {
 public:
  T x = 0, y = 0;

  Vector2<T> &operator+=(const Vector2<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vector2<T> &operator-=(const Vector2<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  Vector2<T> &operator*=(const Vector2<T> &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  Vector2<T> &operator/=(const Vector2<T> &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  template<class X>
  Vector2<T> &operator*=(const X &rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  template<class X>
  Vector2<T> &operator/=(const X &rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  Vector2<T> operator+(const Vector2<T> &rhs) const {
    return {x + rhs.x, y + rhs.y};
  }

  Vector2<T> operator-(const Vector2<T> &rhs) const {
    return {x - rhs.x, y - rhs.y};
  }

  Vector2<T> operator*(const Vector2<T> &rhs) const {
    return {x * rhs.x, y * rhs.y};
  }

  Vector2<T> operator/(const Vector2<T> &rhs) const {
    return {x / rhs.x, y / rhs.y};
  }

  template<class X>
  Vector2<T> operator*(const X &rhs) const {
    return {x * rhs, y * rhs};
  }

  template<class X>
  Vector2<T> operator/(const X &rhs) const {
    return {x / rhs, y / rhs};
  }

  T length() const {
    return std::sqrt(x * x + y * y);
  }

  template<class X>
  Vector2<X> type() {
    return {(X) x, (X) y};
  }

  template<class X>
  X as() {
    return X(x, y);
  }

};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;

Vector2f normalizeVector(Vector2f vector);

Vector2f rotateVector(Vector2f vector, float angleRads);

bool isPointInsideConvex(const std::vector<Vector2f> &convex, const Vector2f &point);
bool doShapesIntersect(const std::vector<Vector2f> &shape1, const std::vector<Vector2f> &shape2);

float radiansToDegrees(float radians);
float degreesToRadians(float degrees);

// makes while(value > range) value -= range
// in an optimal way.
float makeInRange(float value, float range);

bool doLinesIntersect(Vector2f lineAStart, Vector2f lineAEnd, Vector2f LineBStart, Vector2f LineBEnd);
Vector2f findLineIntersection(Vector2f lineAStart, Vector2f lineAEnd, Vector2f LineBStart, Vector2f LineBEnd);

template<typename T>
bool isZero(T value, T EPSILON = EPS_ZERO) {
  return std::abs(value) <= EPSILON;
}

}
