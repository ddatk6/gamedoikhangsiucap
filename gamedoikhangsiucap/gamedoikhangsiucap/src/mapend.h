#pragma once
#include "game.h"
#include <string>

class Map {
public:
    Map(SDL_Renderer* renderer, const std::string& backgroundPath);
    ~Map();
    void DrawMap() ;

private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    std::string backgroundPath;
};
