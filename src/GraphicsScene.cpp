#include "TouchCP/GraphicsScene.h"
#include "TouchCP/Application.h"

GraphicsScene::GraphicsScene()
{
	Application::getCurrentSceneManager()->registerScene(classHash, this);
}

GraphicsScene::~GraphicsScene()
{
	Application::getCurrentSceneManager()->unregisterScene(classHash);
	for (GraphicsObject *object : objects)
	{
		delete object;
	}
}

const std::vector<GraphicsObject *> GraphicsScene::getObjects() const
{
	return objects;
}

void GraphicsScene::addObject(GraphicsObject *toadd)
{
	objects.emplace_back(toadd);
}

void GraphicsScene::addObjects(GraphicsObject **toadd, size_t number)
{
	objects.insert(objects.end(), toadd, toadd + number * sizeof(GraphicsObject *));
}

void GraphicsScene::addObjects(const std::vector<GraphicsObject *> &toadd)
{
	objects.insert(objects.end(), toadd.cbegin(), toadd.cend());
}

void GraphicsScene::removeObject(GraphicsObject *toremove)
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
	for (GraphicsObject *object : objects)
	{
		if (object->isVisible())
			object->draw(time);
	}
}

void GraphicsScene::show()
{
	Application::getCurrent()->getSceneManager()->setCurrentScene(classHash);
}

std::string GraphicsScene::unsafeRandomHash(size_t length)
{
	const std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<unsigned char> distr(0, str.length() - 1);

	std::string result = "";
	for (size_t i = 0; i < length; i++)
		result += str[distr(generator)];
	return result;
}