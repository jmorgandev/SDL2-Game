#ifndef GAMESTATE_H
#define GAMESTATE_H

#define STATE_EXIT 0
#define STATE_CLEAN 1
#define STATE_ERROR 2

#include <string>
#include <vector>
#include "GameObject.h"

//GameState abstract base class
class GameState {
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual int onEnter() = 0;
	virtual void onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:
	std::vector<GameObject*> m_gameObjects;
	std::vector<std::string> m_textureIDs;
};

#endif