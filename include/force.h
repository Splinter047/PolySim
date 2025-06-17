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
	float angular_accel;
	bool is_static;
	float mass;

public:
	Force();
	float angular_velocity;

	Vector2 getVelocity() { return velocity; }

	void update(float delta_time, Vector2 grav, Transformation &transform,
				Vector2 lowest_point);
	void setStatic(bool static_state);
	void setMass(float _mass);
	void setVelocity(Vector2 _velo) { velocity = _velo; }
};

#endif
