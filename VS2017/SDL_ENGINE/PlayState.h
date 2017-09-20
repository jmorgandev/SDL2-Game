#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "EventHandler.h"
#include "Level.h"

//Gamestate that updates and renders the current level

class PlayState : public GameState, public EventHandler {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:

	Level* m_currentLevel;

	static const std::string s_stateID;
	void OnKeyboardEvent(const SDL_KeyboardEvent& e);
};

#endif