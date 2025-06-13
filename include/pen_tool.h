#ifndef PEN_TOOL_H
#define PEN_TOOL_H

#include "raylib.h"
#include "vector.h"
#include "polygon.h"
#include "raymath.h"

/**
 * @brief A tool responsible for creating and managing polygons through user
 * interactions such as mouse inputs.
 */
class Pen_Tool {
private:
    Vector<Vector2> current_vertices;
    Color preview_color;
    float min_vert_dist;
	float min_area;

	bool lineIntersects(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4) const;
	bool selfIntersects(Vector2 new_vert) const;
	float calcArea(const Vector<Vector2>& vertices) const;
	bool isVertexValid(Vector2 pos) const;

public:
    Pen_Tool();

    void tryAddVertex(Vector2 mouse_pos);
    void startNewPolygon(Vector2 start_pos);
	bool removeLastVertex();
    Polygon* completePolygon();
    void cancel();

    void drawPreview() const;
};

#endif