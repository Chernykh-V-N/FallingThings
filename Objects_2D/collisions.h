#pragma once
#include "object.h"


bool AABBvsAABB(const AABB& lhs, const AABB& rhs);
bool CircleVsAABB(Circle s_circle, AABB s_AABB);