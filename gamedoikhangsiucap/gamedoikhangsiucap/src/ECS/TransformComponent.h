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
	int speed = 1;
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

		// Kiểm tra nếu nhân vật chạm đất
		if (position.y + height * scale >= 600) {
			position.y = 600 - height * scale; // Đặt nhân vật đúng trên mặt đất  
			velocity.y = 0;
			onGround = true; // Cho phép nhảy lại
		}
		else {
			velocity.y += 0.5; // Áp dụng trọng lực
			onGround = false;  // Không cho phép nhảy khi đang trên không
		}
		if (position.x < 0) {
			position.x = 0; // Không đi ra ngoài bên trái
		}
		if (position.x + width * scale > 1600) { // 800 là chiều rộng màn hình
			position.x = 1600 - width * scale; // Không đi ra ngoài bên phải
		}
	}
	
};