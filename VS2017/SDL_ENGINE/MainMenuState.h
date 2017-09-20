#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include "MenuState.h"


//Main menu state
class MainMenuState : public MenuState {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:
	static const std::string s_stateID;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_startGame();
	static void s_exitProgram();
};

#endif