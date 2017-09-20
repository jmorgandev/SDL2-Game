#ifndef RELIC_H
#define RELIC_H

#include "SDLGameObject.h"
#include "BaseCreator.h"
#include <vector>


//Game Win item
class Relic : public SDLGameObject {
public:
	Relic();
	virtual ~Relic(){}

	virtual void load(const LoadParameters parameters);

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void collision(std::string tag);
	virtual std::string getTag(){ return "RELIC"; }
	virtual bool toRemove(){ return m_taken; }

	SDL_Rect getCollisionBox() { return m_collider; }

private:
	SDL_Rect m_collider;
	bool m_taken;
};

class RelicCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new Relic(); }
};

#endif