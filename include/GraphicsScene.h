#pragma once
#include <vector>
#include <algorithm>

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
	GraphicsScene(const GraphicsScene& copy) = delete;
	GraphicsScene(const GraphicsScene&& move) = delete;
	GraphicsScene operator=(const GraphicsScene& copy) = delete;
	virtual ~GraphicsScene() = default;
	const std::vector<GraphicsObject*> getObjects() const;
	void addObject(GraphicsObject* object);
	void addObjects(GraphicsObject** toadd, size_t number);
	void addObjects(const std::vector<GraphicsObject*>& toadd);
	void removeObject(GraphicsObject* toremove);
	void removeObject(int index);
	void clearObjects();
	void draw(uint32_t time) override;
private:
	std::vector<GraphicsObject*> objects;
};

