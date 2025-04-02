#pragma once
#include "Components.h"
#include "SDL.h"
#include "../game.h"
#include "HealthEnergyComponent.h"
#include"Constants.h"

enum BarPosition {
    LEFT,
    RIGHT
};

class StatusBarUIComponent : public Component {
public:
    int maxHP = 1000;
    int currentHP = 1000;
    int maxEnergy = 1000;
    int currentEnergy = 1000;

    SDL_Rect hpBar;
    SDL_Rect energyBar; // dùng energyBar để hiển thị năng lượng

    BarPosition barPos;
    Entity* linkedEntity = nullptr; // liên kết với entity chứa HealthEnergyComponent

    StatusBarUIComponent(BarPosition pos) : barPos(pos) {}

    void init() override {
        hpBar.h = 15;
        energyBar.h = 15;
        if (barPos == LEFT) {
            hpBar.x = 20;
            energyBar.x = 20;
        }
        else {
            hpBar.x = GlobalConstants::SCREEN_WIDTH - 320;
            energyBar.x = GlobalConstants::SCREEN_WIDTH - 320;
        }
        hpBar.y = 20;
        energyBar.y = 40;
        hpBar.w = 300;
        energyBar.w = 300;
    }

    void update() override {
        if (linkedEntity && linkedEntity->hasComponent<HealthEnergyComponent>()) {
            auto& he = linkedEntity->getComponent<HealthEnergyComponent>();
            maxHP = he.maxHP;
            currentHP = he.currentHP;
            maxEnergy = he.maxEnergy;
            currentEnergy = he.currentEnergy;
        }
        hpBar.w = (currentHP * 300) / maxHP;
        energyBar.w = (currentEnergy * 300) / maxEnergy;
    }

    void draw() override {
        SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Game::renderer, &hpBar);
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(Game::renderer, &energyBar);
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    }
};
