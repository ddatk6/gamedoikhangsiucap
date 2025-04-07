#pragma once
#include "Components.h"
//#include"SkillSystem.h"

class HealthEnergyComponent : public Component {
public:
    int maxHP, currentHP;
    int maxEnergy, currentEnergy;
    bool stunned;
    Uint32 stunStartTime;
    Uint32 stunDelay;
    Uint32 lastHitTime;
    Uint32 hitDelay; 

    HealthEnergyComponent()
        : maxHP(1000), currentHP(1000),
        maxEnergy(1000), currentEnergy(1000),
        stunned(false), stunStartTime(0), stunDelay(600), lastHitTime(0), hitDelay(600)
    {
    }

    void decreaseHealth(double amount) {
        currentHP -= amount;
        if (currentHP < 0) currentHP = 0;
    }
    void tryDecreaseHealth(int damage) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastHitTime >= hitDelay) {
            decreaseHealth(damage);
            lastHitTime = currentTime;
       
            stunned = true;
            stunStartTime = currentTime;
        }
    }

    void updateStun() {
        if (stunned) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - stunStartTime >= stunDelay) {
                stunned = false;
            }
        }
    }
     void decreaseEnergy(double amount) {
        currentEnergy -= amount;
        if (currentEnergy < 0) currentEnergy = 0;
    }
     void increaseEnergy(double amount) {
         currentEnergy += amount;
         if (currentEnergy >= maxEnergy) currentEnergy = maxEnergy;
     }
     bool hasEnoughEnergy(double energyCost) const {
         return currentEnergy >= energyCost; 
     }

     

};
