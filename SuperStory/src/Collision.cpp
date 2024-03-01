#include "Collision.h"
#include "ECS/ColliderComponent.h"
 
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y)
	{
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::AABB_Y(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.y + recA.h >= recB.y && recB.y + recB.h >= recA.y)
	{
		return true;
	}

	return false;
}

bool Collision::AABB_Y(const ColliderComponent& colA, const ColliderComponent& colB)
{
	return AABB_Y(colA.collider, colB.collider);
}

bool Collision::AABB_X(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.h >= recB.x && recB.x + recB.h >= recA.x)
	{
		return true;
	}

	return false;
}

bool Collision::AABB_X(const ColliderComponent& colA, const ColliderComponent& colB)
{
	return AABB_X(colA.collider, colB.collider);
}
