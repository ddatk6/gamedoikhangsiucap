#pragma once

#include "Components.h"
#include "SDL.h"
#include "Constants.h"     
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Player1Controller.h"
#include "Player2Controller.h"

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
};
