#include "../include/polygon.h"

Polygon::Polygon() : outline_color(BLACK), fill_color(LIGHTGRAY) {}

Polygon::Polygon(const Vector<Vector2> &_vertices,
				 const Transformation &_transform)
	: vertices(_vertices), transform(_transform), outline_color(BLACK),
	  fill_color(LIGHTGRAY)
{
}

/**
 * @brief Iterate over each adjacent point and draw a line between them
 */
void Polygon::draw() const
{
	int vertex_count = vertices.size();
	if (vertex_count < 2) return;

	Vector<Vector2> transformed_vertices;
	for (int i = 0; i < vertex_count; ++i)
	{
		transformed_vertices.push(transformVertex(vertices[i]));
	}

	// Draw lines between consecutive vertices
	for (int i = 0; i < vertex_count - 1; ++i)
		DrawLineV(transformed_vertices[i], transformed_vertices[i + 1],
				  outline_color);

	// If we have a complete polygon (3 or more transformed_vertices), close it
	if (vertex_count >= 3)
		DrawLineV(transformed_vertices[vertex_count - 1],
				  transformed_vertices[0], outline_color);

	// Vertices represented as circles
	for (int i = 0; i < vertex_count; i++)
		DrawCircleV(transformed_vertices[i], 3, outline_color);

	DrawCircleV(transform.position, 6, BLUE);
}

/**
 * @brief Change default outline color
 * @param color Raylib color object for setting the outline
 */
void Polygon::setOutlineColor(const Color color) { outline_color = color; }

/**
 * @brief Change default fill color
 * @param color Raylib color object for the polygon fill
 */
void Polygon::setFillColor(const Color color) { fill_color = color; }

/**
 * @brief Converts the relative position of vertices to absolute
 * @param vertex Vertex to convert
 * @return Transformed vertex
 */
Vector2 Polygon::transformVertex(const Vector2 &vertex) const
{
	// Apply scale
	Vector2 scaled = {vertex.x * transform.scale.x,
					  vertex.y * transform.scale.y};

	// Apply rotation around pivot
	float rad = transform.rotation * DEG2RAD;
	float cos_rot = cosf(rad);
	float sin_rot = sinf(rad);
	Vector2 rotated = {scaled.x * cos_rot - scaled.y * sin_rot,
					   scaled.x * sin_rot + scaled.y * cos_rot};

	// Move back from pivot space and apply position
	return Vector2{rotated.x + transform.position.x,
				   rotated.y + transform.position.y};
}

/**
 * @brief Invokes the force method for calculating the next transform and forces
 * @param delta_time Frame time for physics calculations
 * @param grav Gravity constant
 */
void Polygon::updatePhysics(float delta_time, Vector2 grav)
{
	Vector2 lowest_point = getLowestPoint();
	force.update(delta_time, grav, transform, lowest_point);
}

/**
 * @return Absolute position of the lowest vertex (closest to the floor)
 */
Vector2 Polygon::getLowestPoint() const
{
	float min = transformVertex(vertices[0]).y;
	int min_idx = 0;
	for (int i = 1; i < vertices.size(); ++i)
		if (float y = transformVertex(vertices[i]).y; y > min)
		{
			min = y;
			min_idx = i;
		}

	return transformVertex(vertices[min_idx]);
}

/**
 * @brief Uses the Separating Axis Theorem to check if two convex polygons are
 * overlapping or not by projecting them onto the normal of every edge and
 * looking for a separating axis
 * @param other Polygon to check collision with
 * @param mtv Minimum translation vector
 * @return True if Collision is detected
 */
bool Polygon::checkCollision(const Polygon &other, Vector2 &mtv) const
{
	float min_overlap = FLT_MAX;
	Vector2 smallest_axis = {0, 0};

	// Check axes from both polygons
	for (int cur_obj = 0; cur_obj < 2; ++cur_obj)
	{
		const Polygon *poly = (cur_obj == 0) ? this : &other;
		int vert_count = poly->vertices.size();

		for (int i = 0; i < vert_count; ++i)
		{
			// Edge converted to absolute
			Vector2 p1 = poly->transformVertex(poly->vertices[i]);
			Vector2 p2 =
					poly->transformVertex(poly->vertices[(i + 1) % vert_count]);
			Vector2 edge = {p2.x - p1.x, p2.y - p1.y};

			// Normal axis
			Vector2 normal = {-edge.y, edge.x};
			float length = sqrtf(normal.x * normal.x + normal.y * normal.y);
			if (length == 0) continue;
			normal.x /= length;
			normal.y /= length;

			// Project both polygons onto normal
			float minA = FLT_MAX, maxA = -FLT_MAX;

			for (int j = 0; j < this->vertices.size(); ++j)
			{
				Vector2 point = this->transformVertex(this->vertices[j]);
				float projection = point.x * normal.x + point.y * normal.y;
				if (projection < minA) minA = projection;
				if (projection > maxA) maxA = projection;
			}

			float minB = FLT_MAX, maxB = -FLT_MAX;

			for (int j = 0; j < other.vertices.size(); ++j)
			{
				Vector2 point = other.transformVertex(other.vertices[j]);
				float projection = point.x * normal.x + point.y * normal.y;
				if (projection < minB) minB = projection;
				if (projection > maxB) maxB = projection;
			}

			// Check for separating axis
			if (maxA < minB || maxB < minA) return false;

			// Find overlap
			float overlap = fminf(maxA, maxB) - fmaxf(minA, minB);

			if (overlap < min_overlap)
			{
				min_overlap = overlap;
				smallest_axis = normal;
				// Ensure axis points from this to other
				Vector2 d = {other.transform.position.x -
									 this->transform.position.x,
							 other.transform.position.y -
									 this->transform.position.y};

				if (d.x * normal.x + d.y * normal.y < 0)
				{
					smallest_axis.x = -smallest_axis.x;
					smallest_axis.y = -smallest_axis.y;
				}
			}
		}
	}

	// No separating axis found, aka there is a collision
	// Calculating the minimum translation vector ( To resolve collision )
	if (min_overlap < FLT_MAX)
	{
		mtv.x = smallest_axis.x * min_overlap;
		mtv.y = smallest_axis.y * min_overlap;
	}
	return true;
}
