#include "../include/force.h"

#include <cmath>

Force::Force()
	: velocity({0.0f, 0.0f}), accel({0.0f, 0.0f}), is_static(false), mass(1.0f),
	  angular_velocity(0.0f), angular_accel(0.0f)
{
}

/**
 * @brief Currently only applies gravity to the object
 * @param delta_time Frame time for physics solving
 * @param grav Gravity constant
 * @param transform Transform object for the polygon we are solving
 * @param lowest_point Bottom of the object
 */
void Force::update(float delta_time, Vector2 grav, Transformation &transform,
				   Vector2 lowest_point)
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

	// Floor collision
	float floor = GetScreenHeight() - 10;
	float diff = floor - lowest_point.y;

	if (diff < 0 && velocity.y > 0)
	{
		transform.position.y += diff;
		velocity.y *= -0.5f;

		float com_x = transform.position.x;
		float torque = (com_x - lowest_point.x) * 0.2f;
		angular_velocity += torque;
	}

	transform.rotation += angular_velocity * delta_time;
	angular_velocity *= 0.95f;
}

/**
 * @brief Switches between static and not static
 */
void Force::toggleStatic() { is_static = !is_static; }

/**
 * @param _mass New value to set for mass
 */
void Force::setMass(float _mass) { mass = _mass; }
