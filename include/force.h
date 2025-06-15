#ifndef FORCE_H
#define FORCE_H

#include "raylib.h"
#include "transformation.h"
#include "vector.h"

class Force {
private:
	Vector2 velocity;
	Vector2 accel;
	bool is_static;
	float mass;

	public:

	Force();

	void update(float delta_time, Vector2 grav, Transformation &transform);
	void setStatic(bool static_state);
	void setMass(float _mass);
};

#endif
