﻿#pragma once
#include "../game.h"
#include "ECS.h"
#include "Components.h"
#include "HealthEnergyComponent.h"

class Player2Controller : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    HealthEnergyComponent* healthEnergy;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        if (entity->hasComponent<HealthEnergyComponent>()) {
            healthEnergy = &entity->getComponent<HealthEnergyComponent>();
        }
        else {
            healthEnergy = nullptr; // Xử lý trường hợp không có HealthEnergyComponent
        }
    }

     void update() override {
         if (entity->hasComponent<HealthEnergyComponent>()) {
             auto& he = entity->getComponent<HealthEnergyComponent>();
             he.updateStun();  
             if (he.stunned) {
                 transform->velocity.x = 0;
                 transform->velocity.y = 0;
                 return;
             }
         }

        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_RIGHT]) { 
            transform->velocity.x = 3;
        }
        else if (state[SDL_SCANCODE_LEFT]) {
            transform->velocity.x = -3;
        }
        else {
            transform->velocity.x = 0;
        }

        if (state[SDL_SCANCODE_UP] && transform->onGround) {
            transform->velocity.y = -15;
            transform->onGround = false;
        }
    
    }
};