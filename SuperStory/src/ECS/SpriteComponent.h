#pragma once

#include <map>

#include "Components.h"
#include "../TextureManager.h"
#include "SDL.h"
#include "Animation.h"


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animationIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	// Modify the constructor to accept animation information
	SpriteComponent(const char* path, bool isAnimated = false)
	{
		animated = isAnimated;

		if (animated)
		{
			Animation idle = Animation(0, 24, 100);
			Animation walk = Animation(1, 24, 100);

			animations.emplace("Idle", idle);
			animations.emplace("Walk", walk);

			Play("Idle");
		}

		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animationIndex * transform->height;

		// Store the previous position for collision response
		Vector2D prevPosition = transform->position;

		// Update the destination rectangle as before
		destRect.x = static_cast<int>(transform->position.x) - SuperStory::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - SuperStory::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

		// Determine screen boundaries based on camera dimensions
		int screenWidth = SuperStory::camera.w;
		int screenHeight = SuperStory::camera.h;

		// Calculate the boundaries for player movement
		int minX = 0;
		int minY = 0;
		int maxX = screenWidth - destRect.w;
		int maxY = screenHeight - destRect.h;

		// Check if the player's position exceeds the boundaries
		if (destRect.x < minX)
		{
			destRect.x = minX;
			transform->position.x = SuperStory::camera.x + destRect.x;
		}
		else if (destRect.x > maxX)
		{
			destRect.x = maxX;
			transform->position.x = SuperStory::camera.x + destRect.x;
		}

		if (destRect.y < minY)
		{
			destRect.y = minY;
			transform->position.y = SuperStory::camera.y + destRect.y;
		}
		else if (destRect.y > maxY)
		{
			destRect.y = maxY;
			transform->position.y = SuperStory::camera.y + destRect.y;
		}
	}


	void draw() override
	{
		if (animated)
		{
			TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
		}
	}

	void Play(const char* animationName)
	{
		if (animated)
		{
			frames = animations[animationName].frames;
			animationIndex = animations[animationName].index;
			speed = animations[animationName].speed;
		}
	}
};
