#pragma once
#include"Components.h"
#include"../Vector2D.h"
class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D velocity;

	int width = 50;
	int height = 48;
	int scale = 3;
	int speed = 2;
    bool onGround=false ;


	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	/*
	* hàm khơỉ tạo vị trí và kích thước của nhân vật
	* @param x vị trí x
	* @param y vị trí y
	* @param w chiều rộng
	* @param h chiều cao
	*/
	TransformComponent(float x, float y, int w, int h) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		onGround = false;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		
		if (position.y + height * scale >= 700) {
			position.y = 700 - height * scale;  
			velocity.y = 0;
			onGround = true; 
		}
		else {
			velocity.y += 0.5; 
			onGround = false;
		}
		if (position.x < 0) {
			position.x = 0; 
		}
		if (position.x + width * scale > 1400) { 
			position.x = 1400 - width * scale; 
		}
	}
	
};