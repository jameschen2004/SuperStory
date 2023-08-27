#pragma once

#include "Components.h"
#include "../TextureManager.h"
#include "SDL.h"


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	void setTexture(const char* path)
	{
		SDL_DestroyTexture(texture);
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 0;
		srcRect.h = 0;
		destRect.w = 200;
		destRect.h = 200;

	}

	void update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};