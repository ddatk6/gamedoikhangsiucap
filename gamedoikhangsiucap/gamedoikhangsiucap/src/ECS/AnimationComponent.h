#pragma once

#include "Components.h"
#include "SDL.h"
#include "Constants.h"     
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Player1Controller.h"
#include "Player2Controller.h"
extern Entity& player1;
extern Entity& player2;

class AnimationComponent : public Component
{
public:
	void init() override;
	void update() override;

private:
	SpriteComponent* sprite;
	TransformComponent* transform;
	int currentAction;
	int currentFrame;
	Uint32 lastFrameTime;
	int skillPhase;
	Uint32 skillStartTime;
	Uint32 lastSkillTimes[11];
	bool hitRegistered = false;
	static const int MAX_ACTIONS = 11;
	Uint32 actionCooldowns[MAX_ACTIONS];
	Uint32 hitStunTime;
	const int HIT_STUN_DELAY = 1000; 
	SDL_Texture* hitTexture; // Texture cho ?nh hi?u ?ng hit
	
	
};
