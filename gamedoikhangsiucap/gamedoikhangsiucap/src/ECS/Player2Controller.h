#pragma once
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
             he.updateStun();  // Cập nhật trạng thái stun trước
             if (he.stunned) {
                 // Có thể bạn muốn dừng mọi chuyển động khi bị stun
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
            transform->velocity.x = 0; // Không nhấn gì → Đứng yên
        }

        if (state[SDL_SCANCODE_UP] && transform->onGround) {
            transform->velocity.y = -20;
            transform->onGround = false;
        }
    
    }
};