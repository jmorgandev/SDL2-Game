#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include "Layer.h"
#include <vector>
#include "GameObject.h"


//Layer of gameobjects to be stored in a level
class ObjectLayer : public Layer {
public:
	virtual void update();
	virtual void render();
	virtual void clean();

	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:
	std::vector<GameObject*> m_gameObjects;
};

#endif