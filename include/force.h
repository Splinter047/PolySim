#ifndef FORCE_H
#define FORCE_H

#include "raylib.h"

class Force {
private:
	Vector2 velocity;
	Vector2 accel;
	bool is_fixed;
};


#endif
