#pragma once
#include "Components.h"

class HealthEnergyComponent : public Component {
public:
    int maxHP, currentHP;
    int maxEnergy, currentEnergy;
    bool stunned;
    Uint32 stunStartTime;
    Uint32 stunDelay; // thời gian bị stun (ms)

    HealthEnergyComponent()
        : maxHP(1000), currentHP(1000),
        maxEnergy(100), currentEnergy(100),
        stunned(false), stunStartTime(0), stunDelay(1000)
    {
    }

    void decreaseHealth(int amount) {
        currentHP -= amount;
        if (currentHP < 0) currentHP = 0;
    }
    void decreaseEnergy(int amount) {
        currentEnergy -= amount;
        if (currentEnergy < 0) currentEnergy = 0;
    }
};
