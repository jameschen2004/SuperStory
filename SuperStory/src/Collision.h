#pragma once

#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABB_Y(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB_Y(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool AABB_X(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB_X(const ColliderComponent& colA, const ColliderComponent& colB);
};