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
	Vector2 gravity;
	bool physics_enabled;

public:
    Scene();
    ~Scene();
    
    void addObject(Polygon* object);
    void removeObject(int index);
	void update(float delta_time);

	void togglePhysics();
    void draw() const;
    void clear();

	Vector<Polygon*> getObjects() const;
};

#endif