#include "../include/force.h"

#include <cmath>

Force::Force()
	: velocity({0.0f, 0.0f}), accel({0.0f, 0.0f}), is_static(false), mass(1.0f),
	  angular_velocity(0.0f), angular_accel(0.0f)
{
}

void Force::update(float delta_time, Vector2 grav, Transformation &transform,
				   float lowest_point)
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

	transform.rotation += angular_velocity * delta_time;

	// Floor collision
	float floor = GetScreenHeight() - 10;
	float diff = floor - lowest_point;

	if (diff < 0)
	{
		transform.position.y += diff;
		velocity.y *= -0.5f;
		if (fabsf(velocity.y) < 10.0f) velocity.y = 0.0f;

		angular_velocity += velocity.x * 0.02f;
	}
}

void Force::toggleStatic() { is_static = !is_static; }

void Force::setMass(float _mass) { mass = _mass; }
