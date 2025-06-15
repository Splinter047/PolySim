#include "../include/force.h"

Force::Force()
	: velocity({0.0f, 0.0f}), accel({0.0f, 0.0f}), is_static(false), mass(1.0f)
{
}

void Force::update(float delta_time, Vector2 grav, Transformation &transform)
{
	if (is_static) return;

	// Apply gravity to acceleration
	accel = grav;

	// Update velocity using acceleration
	velocity.x += accel.x * delta_time;
	velocity.y += accel.y * delta_time;

	// Update position using velocity
	transform.position.x += velocity.x * delta_time;
	transform.position.y += velocity.y * delta_time;

	// Simple floor collision
	if (transform.position.y > GetScreenHeight() - 10) {  // 10 pixels from bottom
		transform.position.y = GetScreenHeight() - 10;
		velocity.y = 0;  // Stop vertical movement
		// Could add bounce here later
	}
}

void Force::setStatic(bool static_state) { is_static = static_state; }

void Force::setMass(float _mass) { mass = _mass; }
