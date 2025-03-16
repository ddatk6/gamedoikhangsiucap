#include"Map.h"
#include"TextureManager.h"
#include<fstream>

using namespace std;
const int BLOCK_SIZE = 32;
const int FILE_COL = 27;
const int FILE_ROW = 9;


Map::Map() {

}

void Map::LoadMap() {
	ifstream file("assest/map.txt");
	SDL_Texture* block = TextureManager::LoadTexture("assest/map.png");
	int ID;
	if (file.is_open()) {
		for (int i = 0; i < FILE_ROW; i++) {
			for (int j = 0; j < FILE_COL; j++) {
				file >> ID;
				cout << ID << " ";
				int tileX = (ID % FILE_COL) * BLOCK_SIZE; //tính toán vị trí x của block
				int tileY = (ID / FILE_ROW) * BLOCK_SIZE; //tính toán vị trí y của block
			    SDL_Rect src, dest;
				src.x = tileX;
				src.y = tileY;
				src.w = src.h = BLOCK_SIZE;
				dest.x = j * BLOCK_SIZE;
				dest.y = i * BLOCK_SIZE;
				dest.w = dest.h = BLOCK_SIZE;
				SDL_RenderCopy(Game::renderer, block, &src, &dest);
				


			}
			cout << endl;
		}
		file.close(); 
	}



}
void Map::DrawMap() {

}
