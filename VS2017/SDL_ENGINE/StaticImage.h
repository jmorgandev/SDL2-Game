#ifndef STATIC_IMAGE_H
#define STATIC_IMAGE_H

#include "SDLGameObject.h"
#include "BaseCreator.h"

//A static gameobject that is only rendered
class StaticImage : public SDLGameObject {
public:
	StaticImage(){}
	virtual ~StaticImage(){}

	virtual void load(const LoadParameters parameters){ SDLGameObject::load(parameters);}

	virtual void draw() { SDLGameObject::draw(); }
	virtual void update(){}
	virtual void clean(){}
};

class StaticImageCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new StaticImage(); }
};

#endif