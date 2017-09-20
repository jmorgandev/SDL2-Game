#ifndef SCROLLINGIMAGE_H
#define SCROLLINGIMAGE_H

#include "SDLGameObject.h"
#include "BaseCreator.h"

//Endlessly scrolling image
class ScrollingImage : public SDLGameObject {
public:
	ScrollingImage(){}
	virtual ~ScrollingImage(){}

	virtual void load(const LoadParameters parameters){ SDLGameObject::load(parameters); }

	virtual void draw();
	virtual void update();
	virtual void clean(){}

private:
	int scrollSpeed;
};

class ScrollingImageCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new ScrollingImage(); }
};


#endif