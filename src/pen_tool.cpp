#include "../include/pen_tool.h"

Pen_Tool::Pen_Tool()
	: preview_color(DARKGRAY), min_vert_dist(10.0f), min_area{100.0f}
{
}

/**
 * @brief Checks provided vector in the context of the active polygon
 * @param pos Position to check as vector
 * @return Whether the vertex should be allowed
 */
bool Pen_Tool::isVertexValid(Vector2 pos) const
{
	if (current_vertices.empty()) return true;

	Vector2 last_vert = current_vertices.back();
	if (Vector2Distance(last_vert, pos) < min_vert_dist) return false;

	return !selfIntersects(pos);
}

/**
 * @brief Ensures a minimum distance between last vertex and newly drawn vertex
 * before adding it to the polygon.
 * @param mouse_pos Current mouse cursor position
 */
void Pen_Tool::tryAddVertex(Vector2 mouse_pos)
{
	if (isVertexValid(mouse_pos)) current_vertices.push(mouse_pos);
}

/**
 * @brief Deletes the last placed vertex
 * @return If all vertices have been removed
 */
bool Pen_Tool::removeLastVertex()
{
	if (!current_vertices.empty())
	{
		current_vertices.pop();
		return current_vertices.empty();
	}
	return true;
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
	if (calcArea(current_vertices) < min_area) return nullptr;

	Vector2 reference_pos = current_vertices[0];

	Vector2 centroid = {0, 0};
	for (int i = 0; i < current_vertices.size(); ++i)
	{
		centroid.x += current_vertices[i].x;
		centroid.y += current_vertices[i].y;
	}
	centroid.x /= current_vertices.size();
	centroid.y /= current_vertices.size();

	Transformation transform;
	transform.position = reference_pos;
	transform.pivot = {centroid.x - reference_pos.x,
					   centroid.y - reference_pos.y};

	Vector<Vector2> relative_vertices;
	for (int i = 0; i < current_vertices.size(); ++i)
		relative_vertices.push({current_vertices[i].x - reference_pos.x,
								current_vertices[i].y - reference_pos.y});

	Polygon *new_poly = new Polygon(relative_vertices, transform);
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

	Vector2 mouse_pos = GetMousePosition();
	Color cur_color = isVertexValid(mouse_pos) ? preview_color : RED;

	// Draw lines between existing vertices
	for (int i = 0; i < vert_count - 1; i++)
		DrawLineV(current_vertices[i], current_vertices[i + 1], cur_color);

	// Draw line to mouse position
	if (vert_count > 0)
		DrawLineV(current_vertices[vert_count - 1], GetMousePosition(),
				  cur_color);

	// Vertices represented as circles
	for (int i = 0; i < vert_count; i++)
		DrawCircleV(current_vertices[i], 3, cur_color);
	DrawCircleV(mouse_pos, 3, cur_color);
}

/**
 * @brief Determines whether two lines intersect
 * @param p1 Start point of the first line
 * @param p2 End point of the first line
 * @param p3 Start point of the second line
 * @param p4 End point of the second line
 * @return True if the lines intersect
 */
bool Pen_Tool::lineIntersects(Vector2 p1, Vector2 p2, Vector2 p3,
							  Vector2 p4) const
{
	float denom = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);

	if (fabs(denom) < 0.0001f) return false;

	float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) /
			   denom;
	float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) /
			   denom;

	return (ua > 0.0001f && ua < 0.9999f) && (ub > 0.0001f && ub < 0.9999f);
}

/**
 * @brief Checks if adding the provided vertex causes self-intersection
 * @param new_vert Vertex to test the addition of
 * @return True if the adding vertex causes self-intersection
 */
bool Pen_Tool::selfIntersects(Vector2 new_vert) const
{
	if (current_vertices.size() < 3) return false;

	Vector2 last_vert = current_vertices.back();

	// Check non-adjacent segments
	for (int i = 0; i < current_vertices.size() - 2; i++)
	{
		if (lineIntersects(last_vert, new_vert, current_vertices[i],
						   current_vertices[i + 1]))
			return true;
	}

	// Check closing segment
	for (int i = 1; i < current_vertices.size() - 1; i++)
	{
		if (lineIntersects(new_vert, current_vertices[0], current_vertices[i],
						   current_vertices[i + 1]))
			return true;
	}

	return false;
}

/**
 * @brief Calculates the total area of the provided polygon
 * @param vertices Polygon to calculate the area of
 * @return Area
 */
float Pen_Tool::calcArea(const Vector<Vector2> &vertices) const
{
	if (vertices.size() < 3) return 0.0f;

	float area = 0.0f;
	for (int i = 0; i < vertices.size(); i++)
	{
		Vector2 cur = vertices[i];
		Vector2 next = vertices[(i + 1) % vertices.size()];
		area += (cur.x * next.y - next.x * cur.y);
	}
	return fabs(area) * 0.5f;
}
