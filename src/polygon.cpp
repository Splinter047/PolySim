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
	for (int i = 0; i < vertex_count; ++i) {
		transformed_vertices.push(transformVertex(vertices[i]));
	}
	
	// Draw lines between consecutive vertices
	for (int i = 0; i < vertex_count - 1; ++i)
		DrawLineV(transformed_vertices[i], transformed_vertices[i + 1], outline_color);

	// If we have a complete polygon (3 or more transformed_vertices), close it
	if (vertex_count >= 3)
		DrawLineV(transformed_vertices[vertex_count - 1], transformed_vertices[0], outline_color);

	// Vertices represented as circles
	for (int i = 0; i < vertex_count; i++)
		DrawCircleV(transformed_vertices[i], 3, outline_color);
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
Vector2 Polygon::transformVertex(const Vector2& vertex) const {
	// Move to rotation pivot space
	Vector2 pivoted = {
		vertex.x - transform.pivot.x,
		vertex.y - transform.pivot.y
	};

	// Apply scale
	Vector2 scaled = {
		pivoted.x * transform.scale.x,
		pivoted.y * transform.scale.y
	};

	// Apply rotation around pivot
	float rad = transform.rotation * DEG2RAD;
	float cos_rot = cosf(rad);
	float sin_rot = sinf(rad);
	Vector2 rotated = {
		scaled.x * cos_rot - scaled.y * sin_rot,
		scaled.x * sin_rot + scaled.y * cos_rot
	};

	// Move back from pivot space and apply position
	return Vector2{
		rotated.x + transform.pivot.x + transform.position.x,
		rotated.y + transform.pivot.y + transform.position.y
	};
}

void Polygon::updatePhysics(float delta_time, Vector2 grav)
{
	force.update(delta_time, grav, transform);
}
