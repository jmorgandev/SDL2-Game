#ifndef GAMESTATE_MACHINE_H
#define GAMESTATE_MACHINE_H

#include "GameState.h"

#include <vector>

//Class to handle the engine's current game state
class GameStateMachine {
public:
	static GameStateMachine* instance();

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	std::string getCurrentID();

	void update();
	void render();
	void clean();

private:
	GameStateMachine(){}
	std::vector<GameState*> m_gameStates;
};

#endif