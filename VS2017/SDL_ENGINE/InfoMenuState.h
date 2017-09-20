#ifndef INFO_MENU_STATE_H
#define INFO_MENU_STATE_H

#include "MenuState.h"

//Instruction menu state
class InfoMenuState : public MenuState {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:
	static const std::string s_stateID;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_playGame();
};

#endif