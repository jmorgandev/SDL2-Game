#ifndef PAUSEMENU_STATE_H
#define PAUSEMENU_STATE_H

#include "MenuState.h"

//Pause menu state
class PauseMenuState : public MenuState {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:
	static const std::string s_stateID;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_resumeGame();
	static void s_exitToMenu();
};

#endif