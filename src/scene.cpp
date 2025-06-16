#include "../include/scene.h"

Scene::Scene() : gravity({0.0f, 500.0f}), physics_enabled(false) {}

Scene::~Scene() { clear(); }

/**
 * @brief Transfers ownership of object to the scene
 * @param object Polygon to add
 */
void Scene::addObject(Polygon *object)
{
	if (object != nullptr) objects.push(object);
}

/**
 * @brief Deletes object at provided index
 * @param index Index of polygon to delete
 */
void Scene::removeObject(int index)
{
	if (index >= 0 && index < objects.size())
	{
		delete objects[index];
		objects.delete_at(index);
	}
}

/**
 * @brief Invokes the aggregate force calculation and collision resolution
 * @param delta_time Frame time for physics calculation
 */
void Scene::update(float delta_time)
{
	if (!physics_enabled) return;

	for (int i = 0; i < objects.size(); ++i)
		objects[i]->updatePhysics(delta_time, gravity);

	// Iterate over each possible pair and check for collision
	for (int i = 0; i < objects.size(); ++i)
		for (int j = i + 1; j < objects.size(); ++j)
		{
			Vector2 mtv;

			if (objects[i]->checkCollision(*objects[j], mtv))
			{
				// Move both objects by half of the MTV
				objects[i]->transform.position.x -= mtv.x * 0.5f;
				objects[i]->transform.position.y -= mtv.y * 0.5f;
				objects[j]->transform.position.x += mtv.x * 0.5f;
				objects[j]->transform.position.y += mtv.y * 0.5f;
			}
		}
}

/**
 * @brief Calls the draw for each polygon
 */
void Scene::draw() const
{
	for (int i = 0; i < objects.size(); i++) objects[i]->draw();
}

/**
 * Safely deallocates memory and empties scene
 */
void Scene::clear()
{
	for (int i = 0; i < objects.size(); i++) delete objects[i];

	objects.clear();
}

/**
 * @brief Does what it says
 */
void Scene::togglePhysics() { physics_enabled = !physics_enabled; }

Vector<Polygon*> Scene::getObjects() const { return objects; }