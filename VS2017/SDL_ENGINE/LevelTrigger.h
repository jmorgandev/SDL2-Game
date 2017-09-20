#ifndef TRIGGER_H
#define TRIGGER_H

#include "SDLGameObject.h"
#include "BaseCreator.h"
#include <vector>

//Invisible Level loading trigger
class LevelTrigger : public SDLGameObject {
public:
	LevelTrigger();
	virtual ~LevelTrigger(){}

	virtual void load(const LoadParameters parameters);

	virtual void draw(){}
	virtual void update(){}
	virtual void clean(){}

	void setNewX(int x) { m_newX = x; }
	void setNewY(int y) { m_newY = y; }
	void setLevelID(std::string ID) { levelID = ID; }

	virtual void collision(std::string tag);
	virtual std::string getTag(){ return "TRIGGER"; }
	virtual bool toRemove(){ return false; }

	SDL_Rect getCollisionBox() { return m_collider; }

private:
	SDL_Rect m_collider;

	int m_newX;
	int m_newY;
	std::string levelID;
};

class LevelTriggerCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new LevelTrigger(); }
};

#endif