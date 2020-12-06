#include "GraphicsScene.h"

GraphicsScene::GraphicsScene()
{
}

const std::vector<GraphicsObject*> GraphicsScene::getObjects() const
{
	return objects;
}

void GraphicsScene::addObject(GraphicsObject* toadd)
{
	objects.emplace_back(toadd);
}

void GraphicsScene::addObjects(GraphicsObject** toadd, size_t number)
{
	objects.insert(objects.end(), toadd, toadd + number * sizeof(GraphicsObject*));
}

void GraphicsScene::addObjects(const std::vector<GraphicsObject*>& toadd)
{
	objects.insert(objects.end(), toadd.cbegin(), toadd.cend());
}

void GraphicsScene::removeObject(GraphicsObject* toremove)
{
	objects.erase(std::remove(objects.begin(), objects.end(), toremove));
}

void GraphicsScene::removeObject(int index)
{
	objects.erase(objects.begin() + index);
}

void GraphicsScene::clearObjects()
{
	objects.clear();
}

void GraphicsScene::draw(uint32_t time)
{
	for (GraphicsObject* object : objects) {
		object->draw(time);
	}
}
