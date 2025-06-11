#ifndef POLYGON_H
#define POLYGON_H

#include "raylib.h"
#include "vector.h"
#include "transformation.h"
#include "force.h"

class Polygon {
private:
	Vector<Vector2> vertices;
	Transformation transform;
	Force phys;

	float mass;
	float friction;
	float bounce;

	Color outline_color;
	Color fill_color;

public:
	Polygon();
	Polygon(Vector<Vector2> _vertices, Transformation _transform);
};


#endif
