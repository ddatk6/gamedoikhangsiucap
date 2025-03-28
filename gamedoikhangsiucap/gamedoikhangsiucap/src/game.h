#pragma once
#include<iostream>
#include"SDL.h"
#include"SDL_image.h"

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	static SDL_Renderer* renderer;
	static SDL_Event event;


	bool running() { return isRunning; }
private:
	int cnt = 0;
	bool isRunning=0;
	SDL_Window* window;

};
