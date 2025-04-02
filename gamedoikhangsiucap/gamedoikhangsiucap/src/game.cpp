#include "game.h"
#include "TextureManager.h"
#include "mapend.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"



Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
auto& player1(manager.addEntity());
auto& player2(manager.addEntity());

auto& uiPlayer1(manager.addEntity());
auto& uiPlayer2(manager.addEntity());

SDL_Event Game::event;
using namespace std;
Game::Game()
{}
Game::~Game()
{}
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
	player1.addComponent<TransformComponent>(100, 100 , 50, 64);
	player1.addComponent<SpriteComponent>("assest/naruto.png", 0, 250, 8,200 );
	player1.addComponent<Player1Controller>();
	player1.addComponent<GravityComponent>();
	player1.addComponent<AnimationComponent>();
	player1.addComponent<HealthEnergyComponent>();


	player2.addComponent<TransformComponent>(1500, 100, 34, 64);
	player2.addComponent<SpriteComponent>("assest/sasuke.png", 0, 50, 12, 200 );
	player2.addComponent<Player2Controller>();
	player2.addComponent<GravityComponent>();
	player2.addComponent<AnimationComponent>();
	player2.addComponent<HealthEnergyComponent>();



	uiPlayer1.addComponent<StatusBarUIComponent>(LEFT);
	// Liên kết UI của Player1 với entity player1
	uiPlayer1.getComponent<StatusBarUIComponent>().linkedEntity = &player1;
	// Bạn cũng có thể cập nhật currentHP, currentMana ở đây nếu cần

	// Tạo UI cho Player2: thanh hiển thị ở bên phải
	uiPlayer2.addComponent<StatusBarUIComponent>(RIGHT);
	uiPlayer2.getComponent<StatusBarUIComponent>().linkedEntity = &player2;
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
	/*if (Collision::AABB(player1.getComponent<SpriteComponent>().destRect,
		player2.getComponent<SpriteComponent>().destRect)) {
		player2.getComponent<HealthEnergyComponent>().decreaseHealth();
	}*/

	
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}