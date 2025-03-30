#include "mapend.h"
#include "TextureManager.h"

Map::Map(SDL_Renderer* renderer, const std::string& backgroundPath)
    : renderer(renderer), backgroundPath(backgroundPath) {
    backgroundTexture = TextureManager::LoadTexture(backgroundPath.c_str());
}

Map::~Map() {
    SDL_DestroyTexture(backgroundTexture);
}

void Map::DrawMap() {
    SDL_Rect destRect = {0, 0, 1200, 600};
    SDL_RenderGetViewport(renderer, &destRect);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);
}