#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "raylib.h"

/**
 * @brief Holds the position co-ordinates, rotation angle and scale factor.
 */
class Transformation {
public:
    Vector2 position;
    float rotation;
	Vector2 pivot;
    Vector2 scale;

	Transformation() : position({0, 0}), rotation(0), scale({1, 1}) {}
};

#endif