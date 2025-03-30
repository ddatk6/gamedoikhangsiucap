#pragma once
#include "ECS.h"
#include "HealthEnergyComponent.h"
#include "SDL.h"

// Hàm áp d?ng khi entity b? dính ð?n (skill hit)
// damage: lý?ng máu b? tr?
// energyCost: nãng lý?ng tiêu hao c?a chiêu
// delay: th?i gian delay (ms) mà entity s? b? stun
inline void applySkillHit(Entity* target, int damage, int energyCost, int delay) {
    if (target->hasComponent<HealthEnergyComponent>()) {
        auto& he = target->getComponent<HealthEnergyComponent>();
        he.decreaseHealth(damage);
        he.decreaseEnergy(energyCost);
        he.stunned = true;
        he.stunStartTime = SDL_GetTicks();
        he.stunDelay = delay;
    }
}
