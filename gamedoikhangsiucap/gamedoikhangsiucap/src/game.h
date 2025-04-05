#pragma once
#include<iostream>
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void initAudio();
	void cleanAudio();
	void handleEvents();
	void update();
	void render();
	void clean();
	void showOpeningImage();
	void showEndingImage(SDL_Renderer* renderer, const std::string& filePath);
	void resetGame();
	static SDL_Renderer* renderer;
	static SDL_Event event;
	enum EndReason {
		PLAYER1_DEFEATED,
		PLAYER2_DEFEATED
	};

	EndReason endReason; // Thu?c tính lýu l? do k?t thúc tr? chõi

	void checkEndGame();


	bool running() { return isRunning; }
	

private:
	int cnt = 0;
	bool isRunning=0;
	SDL_Window* window;
	Mix_Music* bgMusic;
	bool koSoundPlayed = false;
	

};
