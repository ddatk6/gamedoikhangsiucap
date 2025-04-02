
#include"AnimationComponent.h"
#include"../Collision.h"

Uint32 damageEffectTimePlayer1 = 0;
Uint32 damageEffectTimePlayer2 = 0;

const Uint32 DAMAGE_EFFECT_DURATION = 600;
void AnimationComponent::init()
{
	sprite = &entity->getComponent<SpriteComponent>();
	transform = &entity->getComponent<TransformComponent>();
	currentAction = 4;
	currentFrame = 0;
	lastFrameTime = SDL_GetTicks();
	skillPhase = -1;
	hitStunTime = 0;

	for (int i = 0; i < MAX_ACTIONS; ++i) {
		actionCooldowns[i] = 0; 
	}
	
	
}

void AnimationComponent::update() {




	bool isPlayer1 = entity->hasComponent<Player1Controller>();
	int actionIndex = 4;
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	Uint32 currentTime = SDL_GetTicks();



	for (int i = 0; i < MAX_ACTIONS; ++i) {
		if (actionCooldowns[i] > 0 && currentTime - 1000 < actionCooldowns[i]) {


		}
	}
	if (isPlayer1) {
		if (isPlayer1 && keyState[SDL_SCANCODE_SPACE] && skillPhase == -1 &&
			currentTime >= actionCooldowns[7] &&
			entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player1Constants::ENERGY_COST)) {
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
				else if (keyState[SDL_SCANCODE_J] && (currentTime >= actionCooldowns[3]) &&
					entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player1Constants::ENERGY_COST)) {
					actionIndex = 3;

				}
				else if (keyState[SDL_SCANCODE_K] && (currentTime >= actionCooldowns[5]) &&
					entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player1Constants::ENERGY_COST)) {
					actionIndex = 5;

				}
				else if (keyState[SDL_SCANCODE_L] && (currentTime >= actionCooldowns[6]) &&
					entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player1Constants::ENERGY_COST)) {
					actionIndex = 6;

				}


			}
		}
		if (currentFrame == Player1Constants::CHARACTER_1_SPRITES[currentAction][Player1Constants::FRAME_COUNT] - 1) {
			// Animation kết thúc, đặt thời gian hồi chiêu
			actionCooldowns[currentAction] = currentTime + Player1Constants::CHARACTER_1_SPRITES[currentAction][Player1Constants::COOLDOWN];
		}
	}
	else if (entity->hasComponent<Player2Controller>()) {
		Player2Controller& p2Controller = entity->getComponent<Player2Controller>();

		// Nếu chưa thực hiện chiêu đặc biệt, kiểm tra kích hoạt bằng KP_0
		if (skillPhase == -1) {
			if (keyState[SDL_SCANCODE_KP_0] && (currentTime >= actionCooldowns[7]) &&
				entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player2Constants::ENERGY_COST)) {
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
				else if (keyState[SDL_SCANCODE_KP_1] && (currentTime >= actionCooldowns[3]) &&
					entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player2Constants::ENERGY_COST))
					actionIndex = 3;
				else if (keyState[SDL_SCANCODE_KP_2] && (currentTime >= actionCooldowns[5]) &&
					entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player1Constants::ENERGY_COST))
					actionIndex = 5;
				else if (keyState[SDL_SCANCODE_KP_3] && (currentTime >= actionCooldowns[6]) &&
					entity->getComponent<HealthEnergyComponent>().hasEnoughEnergy(Player2Constants::ENERGY_COST)) {
					actionIndex = 6;
					int dashSpeed = 6;
					if (sprite->Flip == SDL_FLIP_NONE)
						transform->velocity.x = dashSpeed / 2;
					else
						transform->velocity.x = -dashSpeed / 2;
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
		if (currentFrame == Player2Constants::CHARACTER_1_SPRITES[currentAction][Player2Constants::FRAME_COUNT] - 1) {
			// Animation kết thúc, đặt thời gian hồi chiêu
			actionCooldowns[currentAction] = currentTime + Player2Constants::CHARACTER_1_SPRITES[currentAction][Player2Constants::COOLDOWN];
		}
	}


	currentAction = actionIndex;
	const int (*spriteData)[9] = nullptr;
	int frameCount = 1, srcX = 0, srcY = 0, frameW = 0, frameH = 0, spriteSpeed = 0, timedelay = 0;
	double damage = 0, energy = 0;

	if (isPlayer1) {
		spriteData = Player1Constants::CHARACTER_1_SPRITES;
		frameCount = spriteData[currentAction][Player1Constants::FRAME_COUNT];
		srcX = spriteData[currentAction][Player1Constants::SRC_X];
		srcY = spriteData[currentAction][Player1Constants::SRC_Y];
		frameW = spriteData[currentAction][Player1Constants::FRAME_WIDTH];
		frameH = spriteData[currentAction][Player1Constants::FRAME_HEIGHT];
		spriteSpeed = spriteData[currentAction][Player1Constants::SPEED];
		damage = spriteData[currentAction][Player1Constants::DAMAGE];
		energy = spriteData[currentAction][Player1Constants::ENERGY_COST];
		timedelay = spriteData[currentAction][Player1Constants::COOLDOWN];

	}
	else {
		spriteData = Player2Constants::CHARACTER_1_SPRITES;
		frameCount = spriteData[currentAction][Player2Constants::FRAME_COUNT];
		srcX = spriteData[currentAction][Player2Constants::SRC_X];
		srcY = spriteData[currentAction][Player2Constants::SRC_Y];
		frameW = spriteData[currentAction][Player2Constants::FRAME_WIDTH];
		frameH = spriteData[currentAction][Player2Constants::FRAME_HEIGHT];
		spriteSpeed = spriteData[currentAction][Player2Constants::SPEED];
		damage = spriteData[currentAction][Player2Constants::DAMAGE];
		energy = spriteData[currentAction][Player2Constants::ENERGY_COST];
		timedelay = spriteData[currentAction][Player2Constants::COOLDOWN];
	}

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
	if (player1.getComponent<HealthEnergyComponent>().hasEnoughEnergy(energy)) {
		if (entity->hasComponent<Player1Controller>()) {
			// Kiểm tra va chạm: nếu player1 tấn công trúng player2
			if (Collision::AABB(player1.getComponent<SpriteComponent>().destRect,
				player2.getComponent<SpriteComponent>().destRect)) {
				if (damage > 0) {
					// Gọi giảm máu cho player2
					player2.getComponent<HealthEnergyComponent>().tryDecreaseHealth(damage);
					damageEffectTimePlayer2 = currentTime;
					player1.getComponent<HealthEnergyComponent>().increaseEnergy(1);
				}
			}
			player1.getComponent<HealthEnergyComponent>().decreaseEnergy(energy / frameCount);
		}
	}
	if (player2.getComponent<HealthEnergyComponent>().hasEnoughEnergy(energy)) {
		if (entity->hasComponent<Player2Controller>()) {
			if (Collision::AABB(player2.getComponent<SpriteComponent>().destRect,
				player1.getComponent<SpriteComponent>().destRect)) {
				if (damage > 0 && entity->hasComponent<Player2Controller>()) {
					// Gọi hàm decreaseHealth với chỉ số damage lấy từ constants
					player1.getComponent<HealthEnergyComponent>().tryDecreaseHealth(damage);
					damageEffectTimePlayer1 = currentTime;
					player2.getComponent<HealthEnergyComponent>().increaseEnergy(1);

				}

			}
			player2.getComponent<HealthEnergyComponent>().decreaseEnergy(energy / frameCount);


		}



		if (entity->hasComponent<Player1Controller>()) {
			
			if (damageEffectTimePlayer1 > 0 && currentTime - damageEffectTimePlayer1 <= DAMAGE_EFFECT_DURATION) {
				SDL_SetTextureColorMod(sprite->getTexture(), 255, 0, 0); // Đổi màu đỏ
				actionIndex =11;
			}
			else {
				SDL_SetTextureColorMod(sprite->getTexture(), 255, 255, 255); // Khôi phục màu ban đầu
			}
			if (actionIndex == 11) {
				// Khung ảnh của trạng thái bị sát thương
				srcX = spriteData[11][Player1Constants::SRC_X];
				srcY = spriteData[11][Player1Constants::SRC_Y];
			}
		}

		// Áp dụng hiệu ứng đỏ chỉ cho Player2 nếu họ nhận sát thương
		if (entity->hasComponent<Player2Controller>()) {
			if (damageEffectTimePlayer2 > 0 && currentTime - damageEffectTimePlayer2 <= DAMAGE_EFFECT_DURATION) {
				SDL_SetTextureColorMod(sprite->getTexture(), 255, 0, 0); // Đổi màu đỏ
				actionIndex = 9;
			}
			else {
				SDL_SetTextureColorMod(sprite->getTexture(), 255, 255, 255); // Khôi phục màu ban đầu
			}
			if (actionIndex == 9) {
				// Khung ảnh của trạng thái bị sát thương
				srcX = spriteData[9][Player2Constants::SRC_X];
				srcY = spriteData[9][Player2Constants::SRC_Y];
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
}
