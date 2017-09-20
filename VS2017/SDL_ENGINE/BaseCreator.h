#ifndef BASE_CREATOR_H
#define BASE_CREATOR_H

#include "GameObject.h"

//Base Creator class for GameObject Factory
class BaseCreator {
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator(){}
};

#endif