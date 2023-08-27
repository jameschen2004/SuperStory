#pragma once

#include "../SuperStory.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (SuperStory::event.type == SDL_KEYDOWN)
		{
			switch (SuperStory::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
			default:
				break;
			}
		}

		if (SuperStory::event.type == SDL_KEYUP)
		{
			switch (SuperStory::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			// I will replace this with gravity in the future
			case SDLK_s:
				transform->velocity.y = 0;
			default:
				break;
			}
		}
	}

};