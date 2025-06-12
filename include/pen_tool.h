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

public:
    Pen_Tool();

    void tryAddVertex(Vector2 mouse_pos);
    void startNewPolygon(Vector2 start_pos);
    Polygon* completePolygon();
    void cancel();

    void drawPreview() const;
    bool hasVertices() const;
};

#endif