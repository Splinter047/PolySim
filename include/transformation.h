#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "raylib.h"

/**
 * @brief Holds the position co-ordinates, rotation angle and scale factor.
 */
class Transformation {
private:
    Vector2 position;
    float rotation;
    Vector2 scale;

public:
	Transformation() : position({0, 0}), rotation(0), scale({1, 1}) {}
};

#endif