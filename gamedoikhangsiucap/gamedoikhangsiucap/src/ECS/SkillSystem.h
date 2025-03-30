#pragma once
#include "ECS.h"
#include "HealthEnergyComponent.h"
#include "SDL.h"

// H�m �p d?ng khi entity b? d�nh �?n (skill hit)
// damage: l�?ng m�u b? tr?
// energyCost: n�ng l�?ng ti�u hao c?a chi�u
// delay: th?i gian delay (ms) m� entity s? b? stun
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
