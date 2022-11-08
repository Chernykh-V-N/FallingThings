#include "collisions.h"

float squareLengthOfVector(const Vector2f& s_vector)
{
	return ((s_vector.x * s_vector.x) + (s_vector.y * s_vector.y));
}

float clamp(const float& s_value, const float& s_min, const float& s_max)
{
	return std::max(s_min, std::min(s_max, s_value));
}

Vector2f clamp(const Vector2f& s_value, const Vector2f& s_min, const Vector2f& s_max)
{
	return Vector2f(clamp(s_value.x, s_min.x, s_max.x), clamp(s_value.y, s_min.y, s_max.y));
}

bool AABBvsAABB(const AABB& lhs, const AABB& rhs)
{
	// ¬ыходим без пересечени€, потому что найдена раздел€юща€ ось
	if (lhs.max.x < rhs.min.x || lhs.min.x > rhs.max.x)
	{
		return false;
	}
	if (lhs.max.y < rhs.min.y || lhs.min.y > rhs.max.y)
	{
		return false;
	}
	// –аздел€юща€ ось не найдена, поэтому существует по крайней мере одна пересекающа€ ось
	return true;
}

// AABB to Circle Collision without Resolution
bool CircleVsAABB(const Circle& s_circle, const AABB& s_aabb) {
	// Calculate AABB info (center, half-extents)
	Vector2f aabb_half_extents((s_aabb.max.x - s_aabb.min.x) / 2, (s_aabb.max.y - s_aabb.min.y) / 2);
	Vector2f aabb_center(s_aabb.min.x + aabb_half_extents.x, s_aabb.min.y + aabb_half_extents.y);
	// Get difference vector between both centers
	Vector2f difference = s_circle.center - aabb_center;
	Vector2f clamped = clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Add clamped value to AABB_center and we get the value of box closest to circle
	Vector2f closest = aabb_center + clamped;
	// Retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - s_circle.center;

	return squareLengthOfVector(difference) < (s_circle.radius * s_circle.radius);
}

bool isOverlap(const AABB& lhs, const AABB& rhs);
bool isOverlap(const Circle& s_circle, const AABB& s_AABB);
