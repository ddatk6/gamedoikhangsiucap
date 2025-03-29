#pragma once
#include"ECS.h"
#include"TransformComponent.h"
class GravityComponent : public Component {
public:
	float gravity = 0.5f;
	float terminalVelocity = 10.0f;
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}
private:
	TransformComponent* transform;

	void initialize() {
		init();  // G?i init() thông qua m?t hàm public
	}
	void update() override {
		if (transform->velocity.y < terminalVelocity) {
			transform->velocity.y += gravity;
		}
		transform->position.y += transform->velocity.y;
	}
	friend class ECS;

};