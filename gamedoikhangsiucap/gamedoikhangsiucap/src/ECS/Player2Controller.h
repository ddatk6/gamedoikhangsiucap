#pragma once
#include "../game.h"
#include "ECS.h"
#include "Components.h"

class Player2Controller : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

     void update() override {
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_RIGHT]) { 
            transform->velocity.x = 3;
        }
        else if (state[SDL_SCANCODE_LEFT]) {
            transform->velocity.x = -3;
        }
        else {
            transform->velocity.x = 0; // Không nhấn gì → Đứng yên
        }

        if (state[SDL_SCANCODE_UP] && transform->onGround) {
            transform->velocity.y = -20;
            transform->onGround = false;
        }
    
    }
};