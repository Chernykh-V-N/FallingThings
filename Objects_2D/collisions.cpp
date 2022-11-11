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

Vector2f normalize(const Vector2f& s_vector)
{
	float length = sqrt(squareLengthOfVector(s_vector));

	return Vector2f(s_vector.x * (1 / length), s_vector.y * (1 / length));
}

float dot(const Vector2f& lhs, const Vector2f& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}


Direction VectorDirection(Vector2f s_target)
{
	Vector2f compass[] = {
		Vector2f(0.0f, 1.0f),	// вверх
		Vector2f(1.0f, 0.0f),	// вправо
		Vector2f(0.0f, -1.0f), // вниз
		Vector2f(-1.0f, 0.0f)	// влево
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = dot(normalize(s_target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
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
Collision CircleVsAABB(const Circle& s_circle, const AABB& s_aabb) 
{
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
	
	if (squareLengthOfVector(difference) <= s_circle.radius * s_circle.radius)
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, Vector2f(0.0f, 0.0f));
		
	//return squareLengthOfVector(difference) < (s_circle.radius * s_circle.radius);
}

bool isOverlap(const AABB& lhs, const AABB& rhs)
{
	return AABBvsAABB(lhs, rhs);
}

/*
bool isOverlap(const Circle& s_circle, const AABB& s_AABB)
{
	return CircleVsAABB(s_circle, s_AABB);
}
*/


/*
void ResolveCollision (Object& lhs, Object& rhs)
{
	// ¬ычисл€ем относительную скорость
	Vector2f rv = rhs.getSpeed() - lhs.getSpeed();

		// ¬ычисл€ем относительную скорость относительно направлени€ нормали
	float velAlongNormal = dot(rv, normal);

		// Ќе выполн€ем вычислений, если скорости разделены
	if (velAlongNormal > 0)
	{
		return;
	}

	// ¬ычисл€ем упругость
		float e = min(lhs.getElasticity(), rhs.getElasticity());

		// ¬ычисл€ем скал€р импульса силы
		float j = -(1 + e) * velAlongNormal;
		j /= 1 / lhs.getMass() + 1 / rhs.getMass();

		// ѕрикладываем импульс силы
		Vector2f impulse = j * normal;
		//A.velocity -= 1 / A.mass * impulse
		//B.velocity += 1 / B.mass * impulse
		lhs.useImpulse(impulse);
		rhs.useImpulse(impulse);
}
*/



void collision(Object& lhs, Object& rhs)
{
	if (isOverlap(lhs.getAABB(), rhs.getAABB()))
	{
		Vector2f lhs_impulse(lhs.getImpulse());
		Vector2f rhs_impulse(rhs.getImpulse());



		//lhs.useImpulse(rhs_impulse);
		//rhs.useImpulse(lhs_impulse);
	}
}

void collision(Player& lhs, Object& rhs)
{
	/*
	if (isOverlap(lhs.getCircle(), rhs.getAABB()))
	{
		Vector2f lhs_impulse(lhs.getImpulse());
		Vector2f rhs_impulse(rhs.getImpulse());

		lhs.useImpulse(rhs_impulse);
		rhs.useImpulse(lhs_impulse);
	}
	*/

	Collision collision = CircleVsAABB(lhs.getCircle(), rhs.getAABB());
	if (std::get<0>(collision)) // если столкновение произошло (collision == true)
	{
		/*
		// –азрушаем кирпич (если он не €вл€етс€ твердым)
		if (!box.IsSolid)
			box.Destroyed = true;
*/
		// ќбработка столкновени€
		Direction dir = std::get<1>(collision);
		Vector2f diff_vector = std::get<2>(collision);
		if (dir == LEFT || dir == RIGHT) // горизонтальное столкновение
		{
			//lhs.setSpeed(- lhs.getSpeed().x); // обращаем горизонтальную скорость

			// ѕеремещение
			float penetration = lhs.getCircle().radius - std::abs(diff_vector.x);
			if (dir == LEFT)
				lhs.move(Vector2f(penetration, 0)); //+= penetration; // двигаем м€ч обратно вправо
			else
				lhs.move(Vector2f(-penetration, 0)); // -= penetration; // двигаем м€ч обратно влево
		}
		else // вертикальное столкновение
		{

			//Ball->Velocity.y = -Ball->Velocity.y; // обращаем вертикальную скорость

			// ѕеремещение
			float penetration = lhs.getCircle().radius - std::abs(diff_vector.y);
			if (dir == UP)
				lhs.move(Vector2f(0, -penetration));// -= penetration; // двигаем м€ч обратно вверх
			else
				lhs.move(Vector2f(0, penetration));// += penetration; // двигаем м€ч обратно вниз
		}

		Vector2f lhs_impulse(lhs.getImpulse());
		Vector2f rhs_impulse(rhs.getImpulse());

		Vector2f delta_speed = lhs.getSpeed() - rhs.getSpeed();
		
		Object* obj_ref;

		if (squareLengthOfVector(lhs.getSpeed()) > squareLengthOfVector(rhs.getSpeed()))
		{
			obj_ref = &lhs;
		}
		else
		{
			obj_ref = &rhs;
		}
		
		float delta_elasticity;
		float lhs_elasticity_coef;
		float rhs_elasticity_coef;
		if (lhs.getElasticity() > rhs.getElasticity())
		{
			delta_elasticity = lhs.getElasticity() / rhs.getElasticity();
			lhs_elasticity_coef = 1 / (1 + (lhs.getElasticity() + rhs.getElasticity()));
			rhs_elasticity_coef = 1 - lhs_elasticity_coef;
		}
		else
		{
			delta_elasticity = rhs.getElasticity() / lhs.getElasticity();
			rhs_elasticity_coef = 1 / (1 + (lhs.getElasticity() + rhs.getElasticity()));
			lhs_elasticity_coef = 1 - rhs_elasticity_coef;
		}
		
		Vector2f delta_impulse_lhs = (delta_speed * lhs.getMass()) * lhs_elasticity_coef;
		Vector2f delta_impulse_rhs = -delta_speed * lhs.getMass() * lhs_elasticity_coef;

		lhs.useImpulse(delta_impulse_rhs);
		rhs.useImpulse(delta_impulse_lhs);

		if (dir == 0 || dir == 2)
		{
			obj_ref->invertSpeedY();
		}
		else
		{
			obj_ref->invertSpeedX();
		}


		//Vector2f impulse_tmp = lhs.getImpulse() + rhs.getImpulse();

		//float mass_difference = lhs.getMass() / rhs.getMass();


		//lhs.useImpulse(rhs_impulse);
		//rhs.useImpulse(lhs_impulse);

		//lhs.setSpeed(((lhs.getMass() - rhs.getMass()) / (lhs.getMass() + rhs.getMass())) * lhs.getSpeed());
		//rhs.setSpeed(((rhs.getMass() - lhs.getMass()) / (rhs.getMass() + lhs.getMass())) * rhs.getSpeed());


	}
}