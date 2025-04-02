#pragma once
#include "../game.h"
#include "ECS.h"
#include "Components.h"
#include "HealthEnergyComponent.h"

class Player1Controller : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        if (entity->hasComponent<HealthEnergyComponent>()) {
            auto& he = entity->getComponent<HealthEnergyComponent>();
            he.updateStun();  // Cập nhật trạng thái stun
            if (he.stunned) {
                // Không xử lý input khi bị stun
                transform->velocity.x = 0;
                transform->velocity.y = 0;
                return;
            }
        }


        const Uint8* state = SDL_GetKeyboardState(NULL);

        // Điều khiển di chuyển ngang
        if (state[SDL_SCANCODE_D]) { // Nhấn D → Chạy phải
            transform->velocity.x = 3;
        }
        else if (state[SDL_SCANCODE_A]) { // Nhấn A → Chạy trái
            transform->velocity.x = -3;
        }
        else {
            transform->velocity.x = 0; // Không nhấn gì → Đứng yên
        }

        // Nhảy khi nhấn W (chỉ khi đang ở trên mặt đất)
        if (state[SDL_SCANCODE_W] && transform->onGround) {
            transform->velocity.y = -20; // Điều chỉnh lực nhảy
            transform->onGround = false; // Không thể nhảy liên tục
        }
    
    }
};