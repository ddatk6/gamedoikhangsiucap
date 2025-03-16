﻿#include "game.h"
#include "TextureManager.h"
#include "gameobject.h"
#include"Map.h"
#include"ECS.h"
#include"Components.h"

Gameobject* player1 ;
Gameobject* player2;

Map* map;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

SDL_Event Game::event;
using namespace std;
Game::Game()
{
}
Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << " Subsystems Initialised!..." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
			isRunning = true;

		}
		else {
			isRunning = false;

		}
	}
	map->LoadMap();
	player1 = new Gameobject("assest/sasukerun.png",0,0);
	player2 = new Gameobject("assest/kakashirun.png", 50, 50);
	//map = new Map();
	//newPlayer.addComponent<PositionComponent>();
	//newPlayer.getComponent<PositionComponent>().setPos(500, 500);

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
	player1->Update();
	player2->Update();
	//manager.update();
	//cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << endl;

}

void Game::render()
{
	SDL_RenderClear(renderer);
	player1->Render();
	player2->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned" << endl;



}