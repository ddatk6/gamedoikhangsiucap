#pragma once
#include"Game.h"

class Gameobject {

public:
	Gameobject(const char* texturesheet,int x, int y);
	~Gameobject();
	void Update();
	void Render();
	int xpos,ypos;


private:

	SDL_Texture* objTexture;
	SDL_Rect scrRect, destRect;




};