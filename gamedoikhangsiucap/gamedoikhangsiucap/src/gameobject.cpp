#include"gameobject.h"
#include"TextureManager.h"

Gameobject::Gameobject(const char* texturesheet, int x, int y) {


	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
}

void Gameobject::Update() {
	xpos++;
	ypos++;
	

	scrRect.h = 64;//chiều cao
	scrRect.w = 64;//độ rộng
	scrRect.x = 0;
	scrRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = scrRect.w;
	destRect.h = scrRect.h;


}
void Gameobject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &scrRect, &destRect);

}
