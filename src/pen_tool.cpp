#include "../include/pen_tool.h"

Pen_Tool::Pen_Tool() : preview_color(DARKGRAY), min_vert_dist(5.0f) {}

/**
 * @brief Ensures a minimum distance between last vertex and newly drawn vertex
 * before adding it to the polygon.
 * @param mouse_pos Current mouse cursor position
 */
void Pen_Tool::tryAddVertex(Vector2 mouse_pos)
{
	if (current_vertices.empty()) return;

	Vector2 last_vert = current_vertices[current_vertices.size() - 1];

	if (Vector2Distance(last_vert, mouse_pos) >= min_vert_dist)
		current_vertices.push(mouse_pos);
}

/**
 * @brief Start the creation of a new polygon
 * @param start_pos First vertex for our polygon
 */
void Pen_Tool::startNewPolygon(Vector2 start_pos)
{
	current_vertices.clear();
	current_vertices.push(start_pos);
}

/**
 * @brief Creates the completed polygon object
 * @return Newly created polygon
 */
Polygon *Pen_Tool::completePolygon()
{
	if (current_vertices.size() < 3) return nullptr;

	Transformation transform;
	Polygon *new_poly = new Polygon(current_vertices, transform);
	new_poly->setOutlineColor(BLACK);
	new_poly->setFillColor(LIGHTGRAY);

	current_vertices.clear();
	return new_poly;
}

/**
 * @brief Cancel polygon creation
 */
void Pen_Tool::cancel() { current_vertices.clear(); }

/**
 * @brief Draw preview as the user is creating the polygon in realtime
 */
void Pen_Tool::drawPreview() const
{
	int vert_count = current_vertices.size();
	if (vert_count == 0) return;

	// Draw lines between existing vertices
	for (int i = 0; i < vert_count - 1; i++)
		DrawLineV(current_vertices[i], current_vertices[i + 1], preview_color);

	// Draw line to mouse position
	if (vert_count > 0)
		DrawLineV(current_vertices[vert_count - 1], GetMousePosition(),
				  preview_color);

	// Vertices represented as circles
	for (int i = 0; i < vert_count; i++)
		DrawCircleV(current_vertices[i], 3, preview_color);
}

/**
 * @return True if any vertex are present
 */
bool Pen_Tool::hasVertices() const { return !current_vertices.empty(); }
