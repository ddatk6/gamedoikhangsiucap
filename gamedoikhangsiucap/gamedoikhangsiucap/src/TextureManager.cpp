#include "TextureManager.h"  
#include <SDL.h>  

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {  
   SDL_Surface* tempSurface = IMG_Load(fileName);  
   SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);  
   SDL_FreeSurface(tempSurface);  
   return tex;  
}  

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip Flip) {
   SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, Flip);  
}
