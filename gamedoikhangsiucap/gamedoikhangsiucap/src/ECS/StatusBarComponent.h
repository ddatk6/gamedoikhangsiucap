#pragma once

#include "Components.h"
#include "SDL.h"
#include "../game.h"

// Kiểu vị trí thanh UI
enum BarPosition {
    LEFT,
    RIGHT
};

class StatusBarUIComponent : public Component {
public:
    // Các giá trị HP và Mana cho nhân vật liên kết
    int maxHP = 100;
    int currentHP = 100;
    int maxMana = 100;
    int currentMana = 100;

    SDL_Rect hpBar;
    SDL_Rect manaBar;

    BarPosition barPos;

    
    Entity* linkedEntity = nullptr;

    
    StatusBarUIComponent(BarPosition pos) : barPos(pos) {}

    void init() override {
        
        hpBar.h = 15;
        manaBar.h = 15;
        // Vị trí x cố định dựa trên barPos
        if (barPos == LEFT) {
            hpBar.x = 20;
            manaBar.x = 20;
        }
        else { // RIGHT
            // Lấy chiều rộng màn hình từ GlobalConstants
            hpBar.x = 1600 - 320; // 200 + margin
            manaBar.x = 1600 - 220;
        }
        // Vị trí y cố định (có thể tùy chỉnh)
        hpBar.y = 20;
        manaBar.y = 40;
        // Giá trị width đầy đủ của thanh
        hpBar.w = 300;
        manaBar.w = 200;
    }

    void update() override {
        // Nếu có entity liên kết, cập nhật currentHP và currentMana từ entity đó.
        // Ví dụ: giả sử entity có các trường hp và mana (hoặc bạn có thể thêm một component riêng để lưu trạng thái)
        if (linkedEntity) {
            // Ví dụ: nếu bạn đã thêm trường hp và mana trực tiếp vào entity:
            // currentHP = linkedEntity->hp;
            // currentMana = linkedEntity->mana;
            // Nếu chưa, bạn có thể lấy từ một component Status (nếu có)
            // Ở đây, ta giả sử giá trị đã được cập nhật bên ngoài.
        }
        // Cập nhật chiều rộng thanh dựa trên phần trăm HP và Mana
        hpBar.w = (currentHP * 300) / maxHP;
        manaBar.w = (currentMana * 200) / maxMana;
    }

    void draw() override {
        // Vẽ thanh HP (màu đỏ)
        SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Game::renderer, &hpBar);

        // Vẽ thanh Mana (màu xanh dương)
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(Game::renderer, &manaBar);

        // Reset màu vẽ về trắng (mặc định)
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    }
};

