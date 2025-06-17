#ifndef POLYGON_H
#define POLYGON_H

#include <cfloat>
#include <cmath>
#include "force.h"
#include "raylib.h"
#include "transformation.h"
#include "vector.h"

/**
 * @brief Polygon container, stores vertices such that the edges are drawn
 * on the adjacent vertex.
 * Encapsulates the transformation and other properties.
 */
class Polygon
{
private:
	Vector<Vector2> vertices;

	Color outline_color;
	Color fill_color;

public:
	Transformation transform;
	Force force;

	Polygon();
	Polygon(const Vector<Vector2> &_vertices, const Transformation &_transform);

	void draw() const;
	Vector2 transformVertex(const Vector2 &vertex) const;
	void updatePhysics(float delta_time, Vector2 grav);

	Vector2 getLowestPoint() const;
	bool checkCollision(const Polygon &other, Vector2 &mtv) const;
	const Vector<Vector2> &getVertices() const { return vertices; }

	void setOutlineColor(Color color);
	void setFillColor(Color color);
};

#endif
