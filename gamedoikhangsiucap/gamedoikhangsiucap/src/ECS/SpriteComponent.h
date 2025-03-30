#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;

	bool animated = false;
	int frames = 10;
	int speed = 100;

public:
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path); 
	}
	SpriteComponent(const char* path, int x, int y, int nFranes, int mSpeed )
	{
		animated = true;
		frames = nFranes;
		speed = mSpeed;
		srcRect.x = x;
		srcRect.y = y;

		setTex(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		/*srcRect.x = 0;
		srcRect.y = 0;*/
		/*srcRect.w = transform->width;
		srcRect.h = transform->height;*/
		
	}
	void update() override
	{

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		destRect.x =(int) transform->position.x;
		destRect.y =(int) transform->position.y;
		/*destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;*/
		if (transform->velocity.x < 0)
			Flip = SDL_FLIP_HORIZONTAL;
		else if (transform->velocity.x > 0)
			Flip = SDL_FLIP_NONE;
	}

	
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, Flip );
	}

};