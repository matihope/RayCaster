#pragma once
#include <vector>

#define FLOAT_INFINITY 1000000000.f
#define INT_INFINITY 1000000000I
#define LL_INFINITY 1000000000000000000LL
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

};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;

Vector2f normalizeVector(Vector2f vector);
bool isPointInsideConvex(const std::vector<Vector2f> &convex, const Vector2f &point);
bool doShapesIntersect(const std::vector<Vector2f> &shape1, const std::vector<Vector2f> &shape2);

}
