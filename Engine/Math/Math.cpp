#include <Math/Math.hpp>
#include <cmath>
#include <iostream>
#include <cassert>

namespace Math {

Vector2f normalizeVector(const Vector2f vector) {
	if (vector.x == 0 || vector.y == 0)
		return vector;
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);
	return {vector.x / length, vector.y / length};
}

// here vectors are points
float determinant(const Vector2f &tail, const Vector2f &head1, const Vector2f &head2) {
	return (head1.x - tail.x) * (head2.y - tail.y) - (head2.x - tail.x) * (head1.y - tail.y);
}

bool isPointInsideConvex(const std::vector<Vector2f> &convex, const Vector2f &point) {
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
Vector2f getPerpendicular(const Vector2f &vec) {
	return {-vec.y, vec.x};
}

// here vectors are math vectors
float dotProduct(const Vector2f &vec1, const Vector2f &vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

bool doShapesIntersect(const std::vector<Vector2f> &shape1, const std::vector<Vector2f> &shape2) {
	const std::vector<Vector2f> *s1 = &shape1;
	const std::vector<Vector2f> *s2 = &shape2;
	for (size_t t = 0; t < 2; ++t) {
		if (t == 1) {
			s1 = &shape2;
			s2 = &shape1;
		}
		for (size_t i = 0; i < s1->size(); i++) {
			Vector2f perpendicular = getPerpendicular(Vector2f((*s1)[(i + 1) % s1->size()].x - (*s1)[i].x,
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

float radiansToDegrees(float radians) {
	auto circle = 2 * M_PI;
	return (float) (makeInRange(radians, circle) / circle * 360);
}

float makeInRange(float value, float range) {
	if (value < 0)
		value = range - makeInRange(-value, range);
	int timesInside = value / range;
	value -= timesInside * range;
	return value;
}

float degreesToRadians(float degrees) {
	auto circle = 360.0;
	return (float) (makeInRange(degrees, circle) / circle * 2 * M_PI);
}

Vector2f rotateVector(Vector2f vector, float angleRads) {
	return Vector2f(cos(angleRads) * vector.x - sin(angleRads) * vector.y,
	                sin(angleRads) * vector.x + cos(angleRads) * vector.y);
}

// Line intersection helper functions
float _det(Vector2f A, Vector2f B, Vector2f C) {
	// determinant
	// Point AB = { B.x - A.x, B.y - A.y };
	// Point AC = { C.x - A.x, C.y - A.y };
	// return AB.x * AC.y - AB.y * AC.x;
	return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}
bool _onSegment(Vector2f A, Vector2f B, Vector2f C) {
	return std::min(A.x, B.x) <= C.x && C.x <= std::max(A.x, B.x) &&
		std::min(A.y, B.y) <= C.y && C.y <= std::max(A.y, B.y);
}
bool doLinesIntersect(Vector2f lineAStart, Vector2f lineAEnd, Vector2f LineBStart, Vector2f LineBEnd) {
	int det1 = sign(_det(lineAStart, lineAEnd, LineBStart));
	int det2 = sign(_det(lineAStart, lineAEnd, LineBEnd));
	int det3 = sign(_det(LineBStart, LineBEnd, lineAStart));
	int det4 = sign(_det(LineBStart, LineBEnd, lineAEnd));

	// General case
	if (det1 != det2 && det3 != det4)
		return true;

	// Edge cases
	if ((det1 == 0 && _onSegment(lineAStart, lineAEnd, LineBStart)) ||
		(det2 == 0 && _onSegment(lineAStart, lineAEnd, LineBEnd)) ||
		(det3 == 0 && _onSegment(LineBStart, LineBEnd, lineAStart)) ||
		(det4 == 0 && _onSegment(LineBStart, LineBEnd, lineAEnd)))
		return true;

	return false;
}
Vector2f findLineIntersection(Vector2f p1, Vector2f p2, Vector2f p3, Vector2f p4) {
	float px = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) /
		((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));

	float py = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) /
		((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));

	return {px, py};
}

}
