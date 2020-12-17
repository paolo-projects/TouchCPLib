#pragma once
#include <vector>
#include <algorithm>
#include <random>

#include "GraphicsObject.h"

class SceneManager;

/**
 * @brief The Scene object is a base class to construct a Scene upon.
 * The scene is basically a view that can be swapped at runtime with other scenes. It is supposed
 * to contain other Graphic Objects inside of it, since it won't draw anything on its own.
 * The draw method is simply calling the draw method for each child object.
*/
class GraphicsScene : public GraphicsObject
{
public:
	GraphicsScene();
	GraphicsScene(const GraphicsScene &copy) = delete;
	GraphicsScene(const GraphicsScene &&move) = delete;
	GraphicsScene operator=(const GraphicsScene &copy) = delete;
	virtual ~GraphicsScene();
	const std::vector<GraphicsObject *> getObjects() const;
	/**
	 * @brief Add an object to the scene. *** Once added, the object is bound to the scene
	 * and it will take care of deleting the object when destroyed ***
	 * @param object The object to add
	*/
	void addObject(GraphicsObject *object);
	/**
	 * @brief Add an array of objects to the scene
	 * @param toadd The array of objects
	 * @param number The number of objects
	*/
	void addObjects(GraphicsObject **toadd, size_t number);
	/**
	 * @brief Add a vector of objects
	 * @param toadd The vector of objects
	*/
	void addObjects(const std::vector<GraphicsObject *> &toadd);
	/**
	 * @brief Removes an object from the scene. *** You take ownership of the object
	 * back, so the scene won't delete it anymore ***
	 * @param toremove The object to remove
	*/
	void removeObject(GraphicsObject *toremove);
	/**
	 * @brief Removes an object at the given index
	 * @param index The inner index of the object
	*/
	void removeObject(int index);
	/**
	 * @brief Removes all the objects from the scene, taking ownership back on them.
	*/
	void clearObjects();
	void draw(uint32_t time) override;
	void show();

private:
	static std::string unsafeRandomHash(size_t length);
	const std::string classHash = GraphicsScene::unsafeRandomHash(32);
	std::vector<GraphicsObject *> objects;
};
