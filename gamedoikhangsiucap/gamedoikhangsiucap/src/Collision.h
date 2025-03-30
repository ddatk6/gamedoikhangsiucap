#pragma once
#include "SDL.h"
#include"ECS/ECS.h"
#include"ECS/ColliderComponent.h"

class Collision {
public:
    // Ki?m tra va ch?m AABB gi?a 2 SDL_Rect
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
        return !(recA.x + recA.w < recB.x ||
            recB.x + recB.w < recA.x ||
            recA.y + recA.h < recB.y ||
            recB.y + recB.h < recA.y);
    }

    // X? l? va ch?m gi?a 2 entity
    static void onCollision(Entity* a, Entity* b) {
        // B?n có th? m? r?ng logic x? l? va ch?m ? ðây (ví d?: g?i applySkillHit)
        printf("Collision detected between entity %p and entity %p\n", a, b);
    }

    // Ki?m tra va ch?m gi?a các entity có ColliderComponent trong Manager
    static void checkCollisions(const Manager& manager) {
        const auto& entities = manager.getEntities();
        for (size_t i = 0; i < entities.size(); i++) {
            Entity* entityA = entities[i].get();
            if (!entityA->hasComponent<ColliderComponent>())
                continue;
            SDL_Rect colliderA = entityA->getComponent<ColliderComponent>().getCollider();
            for (size_t j = i + 1; j < entities.size(); j++) {
                Entity* entityB = entities[j].get();
                if (!entityB->hasComponent<ColliderComponent>())
                    continue;
                SDL_Rect colliderB = entityB->getComponent<ColliderComponent>().getCollider();
                if (AABB(colliderA, colliderB)) {
                    onCollision(entityA, entityB);
                }
            }
        }
    }
};