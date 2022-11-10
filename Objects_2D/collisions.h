#pragma once
#include "object.h"
#include <tuple>

typedef std::tuple<bool, Direction, Vector2f> Collision;

bool AABBvsAABB(const AABB& lhs, const AABB& rhs);
Collision CircleVsAABB(const Circle& s_circle, const AABB& s_AABB);

bool isOverlap(const AABB& lhs, const AABB& rhs);
bool isOverlap(const Circle& s_circle, const AABB& s_AABB);

void collision(Object& lhs, Object& rhs);
void collision(Player& lhs, Object& rhs);


