#ifndef POLYGON_H
#define POLYGON_H

#include "raylib.h"
#include "vector.h"
#include "transformation.h"

/**
 * @brief Polygon container, stores vertices such that the edges are drawn
 * on the adjacent vertex.
 * Encapsulates the transformation and other properties.
 */
class Polygon {
private:
    Vector<Vector2> vertices;
    Transformation transform;

    Color outline_color;
    Color fill_color;

public:
    Polygon();
    Polygon(const Vector<Vector2>& _vertices, const Transformation &_transform);

    void draw() const;
    void setOutlineColor(Color color);
    void setFillColor(Color color);
};

#endif