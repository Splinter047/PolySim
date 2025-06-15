#ifndef FORCE_H
#define FORCE_H

#include "raylib.h"
#include "transformation.h"
#include "vector.h"

/**
 * @brief Holds current velocity and acceleration values and handles the physics
 * solving for each new frame
 */
class Force
{
private:
	Vector2 velocity;
	Vector2 accel;
	float angular_velocity;
	float angular_accel;
	bool is_static;
	float mass;

public:
	Force();

	void update(float delta_time, Vector2 grav, Transformation &transform,
				Vector2 lowest_point);
	void toggleStatic();
	void setMass(float _mass);
};

#endif
