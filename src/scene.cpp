#include "../include/scene.h"

Scene::Scene() {}

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
