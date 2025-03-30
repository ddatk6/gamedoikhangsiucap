
#include"AnimationComponent.h"


void AnimationComponent::init()
{
	sprite = &entity->getComponent<SpriteComponent>();
	transform = &entity->getComponent<TransformComponent>();
	currentAction = 4;
	currentFrame = 0;
	lastFrameTime = SDL_GetTicks();
	skillPhase = -1;
}

void AnimationComponent::update() {
	if (entity->hasComponent<HealthEnergyComponent>()) {
		auto& he = entity->getComponent<HealthEnergyComponent>();
		if (he.stunned) {
			// Nếu chưa hết thời gian stun, bỏ qua xử lý animation
			if (SDL_GetTicks() - he.stunStartTime < he.stunDelay)
				return;
			else
				he.stunned = false; // Hết stun, cho phép xử lý
		}
	}

	
	// ... tiếp tục phần xử lý animation như code cũ ...

	bool isPlayer1 = entity->hasComponent<Player1Controller>();
	int actionIndex = 4;
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (isPlayer1) {
		if (isPlayer1 && keyState[SDL_SCANCODE_SPACE] && skillPhase == -1) {
			skillPhase = 0;
			currentFrame = 0;
			lastFrameTime = SDL_GetTicks();
		}
		if (skillPhase != -1) {
			if (skillPhase == 0) actionIndex = 7;

			else if (skillPhase == 1) {
				actionIndex = 8;

			}
			else if (skillPhase == 2) {
				actionIndex = 9;

			}
			else {
				actionIndex = 10;
				int dashSpeed = 8;
				if (sprite->Flip == SDL_FLIP_NONE)
					transform->velocity.x = dashSpeed;
				else
					transform->velocity.x = -dashSpeed;
			}


		}
		else {
			if (isPlayer1) {
				Player1Controller& p1Controller = entity->getComponent<Player1Controller>();
				if (!transform->onGround) {
					actionIndex = 1;
				}
				else if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D]) {
					actionIndex = 0;
				}
				else if (keyState[SDL_SCANCODE_S]) {
					actionIndex = 2;
				}
				else if (keyState[SDL_SCANCODE_F]) {
					actionIndex = 3;
				}
				else if (keyState[SDL_SCANCODE_G]) {
					actionIndex = 5;
				}
				else if (keyState[SDL_SCANCODE_H]) {
					actionIndex = 6;
				}
				else {
					actionIndex = 4;
				}

			}
		}
	}
		else if (entity->hasComponent<Player2Controller>()) {
			Player2Controller& p2Controller = entity->getComponent<Player2Controller>();

			// Nếu chưa thực hiện chiêu đặc biệt, kiểm tra kích hoạt bằng KP_0
			if (skillPhase == -1) {
				if (keyState[SDL_SCANCODE_KP_0]) {
					skillPhase = 0;    // Bắt đầu chiêu đặc biệt, giai đoạn 0
					currentFrame = 0;
					lastFrameTime = SDL_GetTicks();
				}
				else {
					// Xử lý input bình thường khi không thực hiện chiêu
					if (!transform->onGround)
						actionIndex = 1;
					else if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_RIGHT])
						actionIndex = 0;
					else if (keyState[SDL_SCANCODE_DOWN])
						actionIndex = 2;
					else if (keyState[SDL_SCANCODE_KP_1])
						actionIndex = 3;
					else if (keyState[SDL_SCANCODE_KP_2])
						actionIndex = 5;
					else if (keyState[SDL_SCANCODE_KP_3]) {
						actionIndex = 6;
						int dashSpeed = 6;
						if (sprite->Flip == SDL_FLIP_NONE)
							transform->velocity.x = dashSpeed/2;
						else
							transform->velocity.x = -dashSpeed/2;
					}
					
				}
			}
			else {
				// Nếu đang thực hiện chiêu đặc biệt, xử lý theo skillPhase
				if (skillPhase == 0)
					actionIndex = 7;
				else if (skillPhase == 1) {
					actionIndex = 8;
					// Bạn có thể bổ sung nếu có thêm giai đoạn ở đây,
					// và sau khi đạt đến số giai đoạn mong muốn, reset skillPhase về -1
					int dashSpeed = 8;
					if (sprite->Flip == SDL_FLIP_NONE)
						transform->velocity.x = dashSpeed;
					else
						transform->velocity.x = -dashSpeed;
				}
			}
		}
	

	currentAction = actionIndex;
	const int (*spriteData)[9] = nullptr;
	int frameCount = 1, srcX = 0, srcY = 0, frameW = 0, frameH = 0, spriteSpeed = 0;

	if (isPlayer1) {
		spriteData = Player1Constants::CHARACTER_1_SPRITES;
		frameCount = spriteData[currentAction][Player1Constants::FRAME_COUNT];
		srcX = spriteData[currentAction][Player1Constants::SRC_X];
		srcY = spriteData[currentAction][Player1Constants::SRC_Y];
		frameW = spriteData[currentAction][Player1Constants::FRAME_WIDTH];
		frameH = spriteData[currentAction][Player1Constants::FRAME_HEIGHT];
		spriteSpeed = spriteData[currentAction][Player1Constants::SPEED];

	}
	else {
		spriteData = Player2Constants::CHARACTER_1_SPRITES;
		frameCount = spriteData[currentAction][Player2Constants::FRAME_COUNT];
		srcX = spriteData[currentAction][Player2Constants::SRC_X];
		srcY = spriteData[currentAction][Player2Constants::SRC_Y];
		frameW = spriteData[currentAction][Player2Constants::FRAME_WIDTH];
		frameH = spriteData[currentAction][Player2Constants::FRAME_HEIGHT];
		spriteSpeed = spriteData[currentAction][Player2Constants::SPEED];
	}
	Uint32 currentTime = SDL_GetTicks();

	if (currentTime - lastFrameTime >= static_cast<Uint32>(spriteSpeed)) {
		// Tăng currentFrame rồi lấy modulo để vòng lặp animation
		currentFrame = (currentFrame + 1) % frameCount;
		// Ghi nhận thời điểm cập nhật frame

		lastFrameTime = currentTime;


		if (skillPhase != -1 && currentFrame == 0) {
			skillPhase++;  // Chuyển sang giai đoạn kế tiếp
			if (skillPhase > 3) {  // Đã hoàn thành 4 giai đoạn của RASENGAN
				skillPhase = -1;  // Reset chiêu thức
				currentAction = 4; // Reset về trạng thái mặc định (ĐỨNG)
			}
		}
	}



	sprite->srcRect.x = srcX + currentFrame * frameW;
	sprite->srcRect.y = srcY;
	sprite->srcRect.w = frameW;
	sprite->srcRect.h = frameH;
	sprite->destRect.h = frameH * transform->scale;
	sprite->destRect.w = frameW * transform->scale;
	transform->height = frameH;
	transform->width = frameW;
	if (transform->velocity.x < 0)
		sprite->Flip = SDL_FLIP_HORIZONTAL;
	else if (transform->velocity.x > 0)
		sprite->Flip = SDL_FLIP_NONE;
	
}
