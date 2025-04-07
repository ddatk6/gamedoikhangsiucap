
#include "game.h"
#include "TextureManager.h"
#include "mapend.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include"SDL_mixer.h"




Map * map;

Manager manager;
SDL_Renderer* Game::renderer = nullptr;
auto& player1(manager.addEntity());
auto& player2(manager.addEntity());

auto& uiPlayer1(manager.addEntity());
auto& uiPlayer2(manager.addEntity());

enum GameState {
	PLAYING,    // Trạng thái đang chơi
	GAME_OVER   // Trạng thái kết thúc
};

// Enum lý do kết thúc
enum EndReason {
	PLAYER1_DEFEATED,
	PLAYER2_DEFEATED
};

// Khởi tạo biến toàn cục
GameState gameState = PLAYING; // Trạng thái mặc định
EndReason endReason;

SDL_Event Game::event;
using namespace std;

Game::Game()
{
}
Game::~Game()
{
}

void Game::showOpeningImage() {
	// Tải texture của hình ảnh mở đầu
	SDL_Texture* openingTexture = TextureManager::LoadTexture("assest/start.png");
	if (!openingTexture) {
		std::cout << "Không thể tải hình ảnh mở đầu!" << std::endl;
		return;
	}

	// Lấy kích thước của viewport để render toàn màn hình
	SDL_Rect destRect;
	SDL_RenderGetViewport(renderer, &destRect);

	bool splashRunning = true;
	SDL_Event event;

	// Vòng lặp hiển thị splash screen cho đến khi người dùng bấm phím hoặc click chuột
	while (splashRunning) {
		// Kiểm tra các sự kiện
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				splashRunning = false;
				isRunning = false;  // Nếu muốn thoát game luôn
			}
			if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
				splashRunning = false;  // Khi có input, thoát khỏi splash screen
			}
		}
		// Render splash screen
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, openingTexture, NULL, &destRect);
		SDL_RenderPresent(renderer);
	}

	// Giải phóng texture sau khi hiển thị xong
	SDL_DestroyTexture(openingTexture);

}
void Game::checkEndGame() {
	if (player1.getComponent<HealthEnergyComponent>().currentHP <= 0) {
		gameState = GAME_OVER;
		endReason = PLAYER1_DEFEATED;
	}
	else if (player2.getComponent<HealthEnergyComponent>().currentHP <= 0) {
		gameState = GAME_OVER;
		endReason = PLAYER2_DEFEATED;
	}
}

void Game::showEndingImage(SDL_Renderer* renderer, const std::string& filePath) {
	SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
	if (!tempSurface) {
		std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
		return;
	}

	// Chuyển đổi Surface thành Texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface); // Giải phóng Surface sau khi tạo Texture

	if (!texture) {
		std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
		return;
	}

	// Định vị và kíc

	// Đặt vị trí và kích thước cho hình ảnh
	SDL_Rect destRect = { 0, 0, 1600, 800 };
	SDL_RenderCopy(Game::renderer, texture, NULL, &destRect);


	SDL_RenderPresent(Game::renderer);

	// Giải phóng texture (nếu không sử dụng lại)
	SDL_DestroyTexture(texture);
}
void Game::resetGame() {
	player1.getComponent<HealthEnergyComponent>().currentHP = 1000;
	player2.getComponent<HealthEnergyComponent>().currentHP = 1000;
	player1.getComponent<HealthEnergyComponent>().currentEnergy = 1000;
	player2.getComponent<HealthEnergyComponent>().currentEnergy = 1000;

	player1.getComponent<TransformComponent>().position = { 100, 100 };
	player2.getComponent<TransformComponent>().position = { 1400, 100 };

	gameState = PLAYING;
	koSoundPlayed = false;
	std::cout << "Game đã được reset!" << std::endl;
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			isRunning = true;

		}
	}
	showOpeningImage();
	map = new Map(renderer, "assest/mapend.png");
	player1.addComponent<TransformComponent>(100, 100, 50, 64);
	player1.addComponent<SpriteComponent>("assest/naruto.png", 0, 250, 8, 200);
	player1.addComponent<Player1Controller>();
	player1.addComponent<GravityComponent>();
	player1.addComponent<AnimationComponent>();
	player1.addComponent<HealthEnergyComponent>();


	player2.addComponent<TransformComponent>(1400, 100, 34, 64);
	player2.addComponent<SpriteComponent>("assest/sasuke.png", 0, 50, 12, 200);
	player2.addComponent<Player2Controller>();
	player2.addComponent<GravityComponent>();
	player2.addComponent<AnimationComponent>();
	player2.addComponent<HealthEnergyComponent>();



	uiPlayer1.addComponent<StatusBarUIComponent>(LEFT);
	uiPlayer1.getComponent<StatusBarUIComponent>().linkedEntity = &player1;



	uiPlayer2.addComponent<StatusBarUIComponent>(RIGHT);
	uiPlayer2.getComponent<StatusBarUIComponent>().linkedEntity = &player2;
	initAudio();
}
void Game::initAudio() {
	// Khởi tạo SDL_mixer với tần số 44100Hz, định dạng mặc định, 2 kênh và chunk size 2048
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer không khởi tạo được! Lỗi: " << Mix_GetError() << std::endl;
	}
	else {
		std::cout << "SDL_mixer khởi tạo thành công!" << std::endl;
	}

	// Load nhạc nền từ file (đảm bảo file tồn tại tại đường dẫn này)
	bgMusic = Mix_LoadMUS("assest/naruto.mp3");
	if (bgMusic == nullptr) {
		std::cout << "Không load được nhạc nền! Lỗi: " << Mix_GetError() << std::endl;
	}
	else {
		// Phát nhạc nền, lặp vô hạn (-1)
		Mix_PlayMusic(bgMusic, -1);
	}
}

void Game::cleanAudio() {
	Mix_FreeMusic(bgMusic);
	bgMusic = nullptr;
	Mix_CloseAudio();
}

void Game::handleEvents()
{


	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;

	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	checkEndGame();

	if (gameState == GAME_OVER) {


		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (gameState == GAME_OVER && event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
					resetGame();
					gameState = PLAYING;
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
			}
			// Các xử lý sự kiện khác cho trạng thái PLAYING
		}

		return; // Dừng các hoạt động khác khi game kết thúc
	}

	// Logic bình thường




}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();


	if (gameState == GAME_OVER) {
		if (!koSoundPlayed) {
			auto& animationComponent = player1.getComponent<AnimationComponent>();
			Mix_PlayChannel(-1, animationComponent.K_O, 0);
			koSoundPlayed = true;
		}

		if (endReason == PLAYER1_DEFEATED) {
			showEndingImage(renderer, "assest/player2win.png");
		}
		else if (endReason == PLAYER2_DEFEATED) {
			showEndingImage(renderer, "assest/player1win.png");
		}
	}
	else {
		map->DrawMap();
		manager.draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}