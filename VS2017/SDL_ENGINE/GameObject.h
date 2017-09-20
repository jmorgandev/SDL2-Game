#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "LoadParameters.h"
#include "Vector2.h"
#include "TileLayer.h"


//GameObject abstract base class
class GameObject {
public:
	GameObject(){}
	virtual ~GameObject(){}

	virtual void load(const LoadParameters parameters) = 0;

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void collision(std::string tag) = 0;
	virtual std::string getTag() = 0;
	virtual bool toRemove() = 0;

	virtual Vector2f& getPosition() = 0;
	virtual Vector2f& getScale() = 0;
	virtual Vector2f& getVelocity() = 0;

	virtual void setCollisionLayer(TileLayer* pLayer){ m_collisionLayer = pLayer; }
	virtual TileLayer* getCollisionLayer() { return m_collisionLayer; }

protected:
	TileLayer* m_collisionLayer;
};

#endif