#include"game.h"
#include"SDL_image.h"
Game* game = nullptr;
int main(int argc, char* argv[]) {

	const int FPS = 60; //toc do di chuyen
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;



	game = new Game();
	game->init("hehe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0);
	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);

		}

	}
	game->clean();
	return 0;
}