#ifndef SCENE_H
#define SCENE_H

#include "polygon.h"
#include "vector.h"

/**
 * @brief Container for all active polygons and managing that list
 */
class Scene {
private:
    Vector<Polygon*> objects;

public:
    Scene();
    ~Scene();
    
    void addObject(Polygon* object);
    void removeObject(int index);
    void draw() const;
    void clear();
};

#endif