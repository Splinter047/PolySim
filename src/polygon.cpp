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
	int vertexCount = vertices.size();
	if (vertexCount < 2) return;

	// Draw lines between consecutive vertices
	for (int i = 0; i < vertexCount - 1; ++i)
		DrawLineV(vertices[i], vertices[i + 1], outline_color);

	// If we have a complete polygon (3 or more vertices), close it
	if (vertexCount >= 3)
		DrawLineV(vertices[vertexCount - 1], vertices[0], outline_color);

	// Vertices represented as circles
	for (int i = 0; i < vertexCount; i++)
		DrawCircleV(vertices[i], 3, outline_color);
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
